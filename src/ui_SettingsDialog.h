#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QCoreApplication>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog {
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QCheckBox *darkModeCheckBox;
    QLabel *settingsLabel;
    QLabel *volumeLabel;
    QSlider *volumeSlider;
    QLabel *themeLabel;
    QComboBox *themeComboBox;

    void setupUi(QDialog *SettingsDialog) {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(400, 300);

        verticalLayout = new QVBoxLayout(SettingsDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        settingsLabel = new QLabel(SettingsDialog);
        settingsLabel->setObjectName(QString::fromUtf8("settingsLabel"));
        settingsLabel->setText("Settings");
        verticalLayout->addWidget(settingsLabel);

        darkModeCheckBox = new QCheckBox(SettingsDialog);
        darkModeCheckBox->setObjectName(QString::fromUtf8("darkModeCheckBox"));
        darkModeCheckBox->setText("Enable Dark Mode");
        verticalLayout->addWidget(darkModeCheckBox);

        volumeLabel = new QLabel(SettingsDialog);
        volumeLabel->setObjectName(QString::fromUtf8("volumeLabel"));
        volumeLabel->setText("Volume");
        verticalLayout->addWidget(volumeLabel);

        volumeSlider = new QSlider(SettingsDialog);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setOrientation(Qt::Horizontal);
        volumeSlider->setRange(0, 100);
        verticalLayout->addWidget(volumeSlider);

        themeLabel = new QLabel(SettingsDialog);
        themeLabel->setObjectName(QString::fromUtf8("themeLabel"));
        themeLabel->setText("Theme");
        verticalLayout->addWidget(themeLabel);

        themeComboBox = new QComboBox(SettingsDialog);
        themeComboBox->setObjectName(QString::fromUtf8("themeComboBox"));
        themeComboBox->addItems({"Light", "Dark", "Blue", "Green"});
        verticalLayout->addWidget(themeComboBox);

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

        verticalLayout->addLayout(buttonLayout);

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