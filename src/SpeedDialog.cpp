#include "SpeedDialog.h"

SpeedDialog::SpeedDialog(QWidget *parent) : QDialog(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    speedWidget = new SpeedWidget(this);
    layout->addWidget(speedWidget);

    setLayout(layout);
    setWindowTitle("Speed Settings");
}