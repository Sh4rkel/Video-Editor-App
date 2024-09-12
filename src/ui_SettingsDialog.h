#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
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