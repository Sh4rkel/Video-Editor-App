#include "FilterSettings.h"
#include "ui_FilterSettings.h"

// Constructor
FilterSettings::FilterSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterSettings),
    gradient(0),
    shadow(0)
{
    ui->setupUi(this);

    // Connect apply button to accept dialog
    connect(ui->applyButton, &QPushButton::clicked, this, &FilterSettings::accept);

    // Connect cancel button to reject dialog
    connect(ui->cancelButton, &QPushButton::clicked, this, &FilterSettings::reject);
}

// Destructor
FilterSettings::~FilterSettings() {
    delete ui;
}

// Get selected filter from combo box
QString FilterSettings::getSelectedFilter() const {
    return ui->filterComboBox->currentText();
}

// Get gradient value
int FilterSettings::getGradient() const {
    return gradient;
}

// Set gradient value and emit settingsChanged signal if value changes
void FilterSettings::setGradient(int value) {
    if (gradient != value) {
        gradient = value;
        emit settingsChanged();
    }
}

// Get shadow value
int FilterSettings::getShadow() const {
    return shadow;
}

// Set shadow value and emit settingsChanged signal if value changes
void FilterSettings::setShadow(int value) {
    if (shadow != value) {
        shadow = value;
        emit settingsChanged();
    }
}