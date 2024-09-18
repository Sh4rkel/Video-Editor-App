#include "SpeedWidget.h"

// Constructor
SpeedWidget::SpeedWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Initialize speed label
    speedLabel = new QLabel("Speed: 1.0x", this);
    speedLabel->setStyleSheet("color: black;");

    // Initialize speed slider
    speedSlider = new QSlider(Qt::Horizontal, this);
    speedSlider->setRange(50, 200);
    speedSlider->setValue(100);
    connect(speedSlider, &QSlider::valueChanged, this, &SpeedWidget::onSpeedSliderChanged);

    // Add widgets to layout
    layout->addWidget(speedLabel);
    layout->addWidget(speedSlider);

    setLayout(layout);
}

// Handle speed slider value change
void SpeedWidget::onSpeedSliderChanged(int value) {
    double speed = value / 100.0;
    speedLabel->setText(QString("Speed: %1x").arg(speed));
    emit speedChanged(speed);
}