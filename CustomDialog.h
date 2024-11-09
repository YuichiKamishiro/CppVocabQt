#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QMainWindow>

class CustomDialog : public QDialog {
    Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = nullptr, QMainWindow *window = nullptr);
    void setupUI();

private:
    QLabel *label;
    QComboBox *comboBox;
    QBoxLayout *layout;
    QMainWindow *window;

private slots:
    void onComboBoxIndexChanged(int index);
};

#endif // CUSTOMDIALOG_H
