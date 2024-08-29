#include "SpeedWidget.h"

SpeedWidget::SpeedWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    speedLabel = new QLabel("Speed: 1.0x", this);
    speedLabel->setStyleSheet("color: black;");

    speedSlider = new QSlider(Qt::Horizontal, this);
    speedSlider->setRange(50, 200);
    speedSlider->setValue(100);
    connect(speedSlider, &QSlider::valueChanged, this, &SpeedWidget::onSpeedSliderChanged);

    layout->addWidget(speedLabel);
    layout->addWidget(speedSlider);

    setLayout(layout);
}

void SpeedWidget::onSpeedSliderChanged(int value) {
    double speed = value / 100.0;
    speedLabel->setText(QString("Speed: %1x").arg(speed));
    emit speedChanged(speed);
}