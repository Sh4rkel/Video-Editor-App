#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QCoreApplication>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog {
public:
    QFormLayout *formLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QCheckBox *darkModeCheckBox;
    QLabel *settingsLabel;
    QLabel *volumeLabel;
    QSlider *volumeSlider;
    QLabel *themeLabel;
    QComboBox *themeComboBox;
    QLabel *qualityLabel;
    QComboBox *qualityComboBox;
    QCheckBox *subtitlesCheckBox;

    void setupUi(QDialog *SettingsDialog) {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(400, 400);

        formLayout = new QFormLayout(SettingsDialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));

        settingsLabel = new QLabel(SettingsDialog);
        settingsLabel->setObjectName(QString::fromUtf8("settingsLabel"));
        settingsLabel->setText("Settings");
        formLayout->addRow(settingsLabel);

        darkModeCheckBox = new QCheckBox(SettingsDialog);
        darkModeCheckBox->setObjectName(QString::fromUtf8("darkModeCheckBox"));
        darkModeCheckBox->setText("Enable Dark Mode");
        formLayout->addRow(darkModeCheckBox);

        volumeLabel = new QLabel(SettingsDialog);
        volumeLabel->setObjectName(QString::fromUtf8("volumeLabel"));
        volumeLabel->setText("Volume");
        formLayout->addRow(volumeLabel, volumeSlider = new QSlider(Qt::Horizontal, SettingsDialog));
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setRange(0, 100);

        themeLabel = new QLabel(SettingsDialog);
        themeLabel->setObjectName(QString::fromUtf8("themeLabel"));
        themeLabel->setText("Theme");
        formLayout->addRow(themeLabel, themeComboBox = new QComboBox(SettingsDialog));
        themeComboBox->setObjectName(QString::fromUtf8("themeComboBox"));
        themeComboBox->addItems({"Light", "Dark", "Blue", "Green"});

        qualityLabel = new QLabel(SettingsDialog);
        qualityLabel->setObjectName(QString::fromUtf8("qualityLabel"));
        qualityLabel->setText("Video Quality");
        formLayout->addRow(qualityLabel, qualityComboBox = new QComboBox(SettingsDialog));
        qualityComboBox->setObjectName(QString::fromUtf8("qualityComboBox"));
        qualityComboBox->addItems({"Low", "Medium", "High"});

        subtitlesCheckBox = new QCheckBox(SettingsDialog);
        subtitlesCheckBox->setObjectName(QString::fromUtf8("subtitlesCheckBox"));
        subtitlesCheckBox->setText("Enable Subtitles");
        formLayout->addRow(subtitlesCheckBox);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));

        okButton = new QPushButton(SettingsDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setText("OK");
        buttonLayout->addWidget(okButton);

        cancelButton = new QPushButton(SettingsDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setText("Cancel");
        buttonLayout->addWidget(cancelButton);

        formLayout->addRow(buttonLayout);

        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    }

    void retranslateUi(QDialog *SettingsDialog) {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Settings", nullptr));
    }
};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
}

QT_END_NAMESPACE

#endif