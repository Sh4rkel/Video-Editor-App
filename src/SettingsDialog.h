#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    bool isDarkModeEnabled() const;
    int getVolume() const;
    QString getTheme() const;
    QString getVideoQuality() const;
    bool isSubtitlesEnabled() const;

    private slots:
        void applySettings();

private:
    Ui::SettingsDialog *ui;
};

#endif