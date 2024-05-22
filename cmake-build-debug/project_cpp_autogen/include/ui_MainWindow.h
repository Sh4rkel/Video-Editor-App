/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "timelinewidget.h"
#include "videoplayerwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *openButton;
    QPushButton *saveButton;
    QPushButton *cutButton;
    QComboBox *comboBox;
    QPushButton *addTextButton;
    QPushButton *combineButton;
    VideoPlayerWidget *videoPlayerWidget;
    TimelineWidget *timelineWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1125, 883);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        openButton = new QPushButton(centralwidget);
        openButton->setObjectName("openButton");

        horizontalLayout->addWidget(openButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");

        horizontalLayout->addWidget(saveButton);

        cutButton = new QPushButton(centralwidget);
        cutButton->setObjectName("cutButton");

        horizontalLayout->addWidget(cutButton);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setEditable(true);

        horizontalLayout->addWidget(comboBox);

        addTextButton = new QPushButton(centralwidget);
        addTextButton->setObjectName("addTextButton");

        horizontalLayout->addWidget(addTextButton);

        combineButton = new QPushButton(centralwidget);
        combineButton->setObjectName("combineButton");

        horizontalLayout->addWidget(combineButton);


        verticalLayout->addLayout(horizontalLayout);

        videoPlayerWidget = new VideoPlayerWidget(centralwidget);
        videoPlayerWidget->setObjectName("videoPlayerWidget");

        verticalLayout->addWidget(videoPlayerWidget);

        timelineWidget = new TimelineWidget(centralwidget);
        timelineWidget->setObjectName("timelineWidget");

        verticalLayout->addWidget(timelineWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1125, 33));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Simple Video Editor", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        cutButton->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
        comboBox->setCurrentText(QCoreApplication::translate("MainWindow", "Format", nullptr));
        addTextButton->setText(QCoreApplication::translate("MainWindow", "Add Text", nullptr));
        combineButton->setText(QCoreApplication::translate("MainWindow", "Combine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
