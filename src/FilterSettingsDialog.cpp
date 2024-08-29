#include "FilterSettingsDialog.h"

FilterSettingsDialog::FilterSettingsDialog(FilterSettings *settings, QWidget *parent)
    : QDialog(parent), filterSettings(settings) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    gradientSlider = new QSlider(Qt::Horizontal, this);
    gradientSlider->setRange(0, 100);
    gradientSlider->setValue(filterSettings->getGradient());
    connect(gradientSlider, &QSlider::valueChanged, filterSettings, &FilterSettings::setGradient);

    shadowSlider = new QSlider(Qt::Horizontal, this);
    shadowSlider->setRange(0, 100);
    shadowSlider->setValue(filterSettings->getShadow());
    connect(shadowSlider, &QSlider::valueChanged, filterSettings, &FilterSettings::setShadow);

    layout->addWidget(new QLabel("Gradient"));
    layout->addWidget(gradientSlider);
    layout->addWidget(new QLabel("Shadow"));
    layout->addWidget(shadowSlider);

    setLayout(layout);
    setWindowTitle("Filter Settings");
}