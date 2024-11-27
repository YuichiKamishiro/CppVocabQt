#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QFontDatabase>
#include <QDialog>
#include <QStandardPaths>
#include <QDir>

#include "CustomDialog.h"

#define PATH_TO_DB0 ":/resources/db/db0.csv"
#define PATH_TO_DB1 ":/resources/db/db1.csv"
#define PATH_TO_DB2 ":/resources/db/db2.csv"
#define PATH_TO_LEARNED_DB ":/resources/db/learnedDB.csv"

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

    void on_comboBoxSettings_currentIndexChanged(int index);

    void on_buttonSettings_clicked();

private:

    Ui::MainWindow *ui;
    CustomDialog *dialog;
    int indexDifficulty = 0;
    QString settingsPath;
};
#endif // MAINWINDOW_H
