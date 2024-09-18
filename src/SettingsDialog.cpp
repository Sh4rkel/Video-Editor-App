#include <QGraphicsDropShadowEffect>
#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

// Constructor
SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // Setup drop shadow effect for buttons
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(2, 2);
    shadowEffect->setColor(Qt::black);

    ui->okButton->setGraphicsEffect(shadowEffect);
    ui->cancelButton->setGraphicsEffect(shadowEffect);

    // Connect ok button to apply settings
    connect(ui->okButton, &QPushButton::clicked, this, &SettingsDialog::applySettings);

    // Connect cancel button to reject dialog
    connect(ui->cancelButton, &QPushButton::clicked, this, &SettingsDialog::reject);
}

// Destructor
SettingsDialog::~SettingsDialog() {
    delete ui;
}

// Apply settings and accept dialog
void SettingsDialog::applySettings() {
    accept();
}

// Check if dark mode is enabled
bool SettingsDialog::isDarkModeEnabled() const {
    return ui->darkModeCheckBox->isChecked();
}

// Get volume value
int SettingsDialog::getVolume() const {
    return ui->volumeSlider->value();
}

// Get selected theme
QString SettingsDialog::getTheme() const {
    return ui->themeComboBox->currentText();
}

// Get selected video quality
QString SettingsDialog::getVideoQuality() const {
    return ui->qualityComboBox->currentText();
}

// Check if subtitles are enabled
bool SettingsDialog::isSubtitlesEnabled() const {
    return ui->subtitlesCheckBox->isChecked();
}