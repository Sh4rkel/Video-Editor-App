#include "SpeedWidget.h"

SpeedWidget::SpeedWidget(QWidget *parent) : QWidget(parent) {
    speedComboBox = new QComboBox(this);
    speedComboBox->addItem("0.25x", 0.25);
    speedComboBox->addItem("0.5x", 0.5);
    speedComboBox->addItem("0.75x", 0.75);
    speedComboBox->addItem("1x", 1.0);
    speedComboBox->addItem("1.25x", 1.25);
    speedComboBox->addItem("1.5x", 1.5);
    speedComboBox->addItem("2x", 2.0);

    connect(speedComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SpeedWidget::onSpeedChanged);
}

void SpeedWidget::onSpeedChanged(int index) {
    qreal speed = speedComboBox->itemData(index).toReal();
    emit speedChanged(speed);
}