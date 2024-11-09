#include "CustomDialog.h"

CustomDialog::CustomDialog(QWidget *parent, QMainWindow *window):
    QDialog(parent),
    label(new QLabel("Background", this)),
    comboBox(new QComboBox(this)),
    layout(new QHBoxLayout(this)),
    window(window)

{
    this->setFixedSize(400, 200);
}

void CustomDialog::setupUI() {
    comboBox->addItems({"Library", "Dark", "Light"});
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChanged(int)));
    layout->addWidget(label);
    layout->addWidget(comboBox);

    setLayout(layout);
}

void CustomDialog::onComboBoxIndexChanged(int index) {
    if (index == 0) {
        window->close();
    }
    else if (index == 1) {
        qDebug() << "index1";
    } else if (index == 2) {
        qDebug() << "index2";
    }
}
