#include "FilterSettings.h"
#include "ui_FilterSettings.h"

FilterSettings::FilterSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterSettings),
    gradient(0),
    shadow(0)
{
    ui->setupUi(this);
}

FilterSettings::~FilterSettings() {
    delete ui;
}

QString FilterSettings::getSelectedFilter() const {
    return ui->filterComboBox->currentText();
}

int FilterSettings::getGradient() const {
    return gradient;
}

void FilterSettings::setGradient(int value) {
    if (gradient != value) {
        gradient = value;
        emit settingsChanged();
    }
}

int FilterSettings::getShadow() const {
    return shadow;
}

void FilterSettings::setShadow(int value) {
    if (shadow != value) {
        shadow = value;
        emit settingsChanged();
    }
}