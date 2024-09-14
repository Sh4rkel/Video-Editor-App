#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    ui->okButton->setIcon(QIcon(":/icons/ok.png"));
    ui->okButton->setToolTip("Apply settings");

    ui->cancelButton->setIcon(QIcon(":/icons/cancel.png"));
    ui->cancelButton->setToolTip("Cancel changes");

    connect(ui->okButton, &QPushButton::clicked, this, &SettingsDialog::applySettings);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SettingsDialog::reject);
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::applySettings() {
    accept();
}

bool SettingsDialog::isDarkModeEnabled() const {
    return ui->darkModeCheckBox->isChecked();
}

int SettingsDialog::getVolume() const {
    return ui->volumeSlider->value();
}

QString SettingsDialog::getTheme() const {
    return ui->themeComboBox->currentText();
}

QString SettingsDialog::getVideoQuality() const {
    return ui->qualityComboBox->currentText();
}

bool SettingsDialog::isSubtitlesEnabled() const {
    return ui->subtitlesCheckBox->isChecked();
}