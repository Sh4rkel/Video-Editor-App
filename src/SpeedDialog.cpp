#include "SpeedDialog.h"

// Constructor
SpeedDialog::SpeedDialog(QWidget *parent) : QDialog(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Initialize speed widget
    speedWidget = new SpeedWidget(this);
    layout->addWidget(speedWidget);

    setLayout(layout);
    setWindowTitle("Speed Settings");
}