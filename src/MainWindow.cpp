#include "MainWindow.h"
#include "../ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dialog(new CustomDialog(parent, this))
{
    ui->setupUi(this);

    settingsPath = "../settings/settings.json";


    // Reading setting.json to get difficulty level
    QFile loadFile(settingsPath);
    loadFile.open(QIODevice::ReadOnly);
    if (!loadFile.isOpen()) {
        qWarning("Failed to open settings1.json");
        exit(EXIT_FAILURE);
    }

    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    QJsonObject jsonObj = loadDoc.object();

    if(jsonObj.contains("difficulty")) {
        indexDifficulty = jsonObj["difficulty"].toInteger();
    }

    ui->comboBoxSettings->setCurrentIndex(indexDifficulty);
    QFontDatabase::addApplicationFont(":/resources/fonts/Rocklime.otf");

    loadFile.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getLinesCount(QString &pathToCurrentDB) {
    int linesCount = 0;

    QFile loadFile(pathToCurrentDB);
    qDebug() << pathToCurrentDB;
    loadFile.open(QIODevice::ReadOnly);
    if (!loadFile.isOpen()) {
        qWarning("Failed to open DB file");
        exit(EXIT_FAILURE);
    }

    QTextStream textStream(&loadFile);

    while(!textStream.atEnd()) {
        textStream.readLine();
        linesCount += 1;
    }

    return linesCount;
}

void MainWindow::on_buttonNext_clicked()
{
    QString pathToCurrentDB;

    switch(indexDifficulty) {
        case 0:
            pathToCurrentDB = PATH_TO_DB0;
            break;
        case 1:
            pathToCurrentDB = PATH_TO_DB1;
            break;
        case 2:
            pathToCurrentDB = PATH_TO_DB2;
            break;
    }
    int linesCount = getLinesCount(pathToCurrentDB);
    if (linesCount == 0) {
        ui->labelWord->setText("Gongrats!!");
        ui->labelDescription->setText("No more words for you");
        return;
    }

    int randLine = QRandomGenerator::global()->bounded(0, linesCount);

    int lineIndex = 0;
    QFile loadFile(pathToCurrentDB);
    loadFile.open(QIODevice::ReadWrite);

    QTextStream textStream(&loadFile);

    QString newFileDB;
    while(!textStream.atEnd()) {
        if (QString line = textStream.readLine(); lineIndex == randLine) {
            auto parts = line.split(',');
            ui->labelWord->setText(parts[0]);
            ui->labelDescription->setText(parts[1]);

            QFile loadLearnedDBFile(PATH_TO_LEARNED_DB);
            loadLearnedDBFile.open(QIODevice::WriteOnly | QIODevice::Append);
            if (!loadLearnedDBFile.isOpen()) {
                qWarning("Failed to open learned words db");
                exit(EXIT_FAILURE);
            }
            QTextStream textStreamLearned(&loadLearnedDBFile);

            textStreamLearned << line << "\n";
            loadLearnedDBFile.close();
        } else {
            newFileDB += line += "\n";
        }

        lineIndex += 1;
    }
    loadFile.resize(0);
    textStream << newFileDB;
}


void MainWindow::on_comboBoxSettings_currentIndexChanged(int index)
{
    indexDifficulty = index;

    // Getting Json
    QFile loadFile(settingsPath);
    loadFile.open(QIODevice::ReadOnly);
    if (!loadFile.isOpen()) {
        qWarning("Failed to open settings.json");
        exit(EXIT_FAILURE);
    }

    QByteArray loadData = loadFile.readAll();
    loadFile.close();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    QJsonObject jsonObj = loadDoc.object();

    if(jsonObj.contains("difficulty")) {
        jsonObj["difficulty"] = indexDifficulty;
    }

    // Writing Json
    QFile writeFile(settingsPath);
    writeFile.open(QIODevice::ReadWrite | QIODevice::Truncate);
    if (!writeFile.isOpen()) {
        qWarning("Failed to open settings.json");
        exit(EXIT_FAILURE);
    }

    QJsonDocument newDoc(jsonObj);
    QByteArray newBytes = newDoc.toJson(QJsonDocument::Indented);

    writeFile.write(newBytes);
}


void MainWindow::on_buttonSettings_clicked()
{
    dialog->exec();
}

