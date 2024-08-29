#include "FilterSettings.h"

FilterSettings::FilterSettings(QObject *parent) : QObject(parent), gradient(0), shadow(0) {}

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