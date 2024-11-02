#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Reading setting.json to get difficulty level
    QFile loadFile(PATH_TO_SETTINGS);
    loadFile.open(QIODevice::ReadOnly);
    if (!loadFile.isOpen()) {
        qWarning("Failed to open settings.json");
        exit(EXIT_FAILURE);
    }

    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    QJsonObject jsonObj = loadDoc.object();

    if(jsonObj.contains("difficulty")) {
        indexDifficulty = jsonObj["difficulty"].toInteger();
    }

    ui->comboBoxSettings->setCurrentIndex(indexDifficulty);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getLinesCount(QString &pathToCurrentDB) {
    int linesCount = 0;

    QFile loadFile(pathToCurrentDB);
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

    int randLine = QRandomGenerator::global()->bounded(0, linesCount);

    // display
    // delete x line
    // add to learned words

}

