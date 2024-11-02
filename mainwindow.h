#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>

#define PATH_TO_SETTINGS "/home/yuichi/CppVocabQt/settings/settings.json"
#define PATH_TO_DB0 "home/yuichi/CppVocabQt/db/db0.csv"
#define PATH_TO_DB1 "home/yuichi/CppVocabQt/db/db1.csv"
#define PATH_TO_DB2 "home/yuichi/CppVocabQt/db/db2.csv"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getLinesCount(QString&);

private slots:
    void on_buttonNext_clicked();

private:

    Ui::MainWindow *ui;
    int indexDifficulty = -1;
};
#endif // MAINWINDOW_H
