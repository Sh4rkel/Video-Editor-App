#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->okButton, &QPushButton::clicked, this, &SettingsDialog::applySettings);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SettingsDialog::reject);
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::applySettings() {
    bool darkModeEnabled = ui->darkModeCheckBox->isChecked();
    int volume = ui->volumeSlider->value();
    QString theme = ui->themeComboBox->currentText();
    accept();
}

bool SettingsDialog::isDarkModeEnabled() const {
    return ui->darkModeCheckBox->isChecked();
}