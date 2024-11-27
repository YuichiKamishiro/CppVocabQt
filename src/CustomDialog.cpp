#include "CustomDialog.h"

CustomDialog::CustomDialog(QWidget *parent, QMainWindow *window):
    QDialog(parent),
    label(new QLabel("Background", this)),
    comboBox(new QComboBox(this)),
    layout(new QHBoxLayout(this)),
    window(window)

{
    this->setFixedSize(400, 200);
    comboBox->addItems({"Library", "Dark", "Light"});
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChanged(int)));
    layout->addWidget(label);
    layout->addWidget(comboBox);

    setLayout(layout);
}

void CustomDialog::onComboBoxIndexChanged(int index) {
    if (index == 0) {
        window->setStyleSheet("#centralwidget {border-image: url(\":/resources/backgrounds/library.jpg\");}");
    }
    else if (index == 1) {
        window->setStyleSheet("#centralwidget {border-image: url(\":/resources/backgrounds/dark.jpg\");}");
    } else if (index == 2) {
        window->setStyleSheet("#centralwidget {border-image: url(\":/resources/backgrounds/light.jpg\");}");
    }
    this->close();
}
