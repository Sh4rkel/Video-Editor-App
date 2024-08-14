#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "TimelineWidget.h"
#include "VideoPlayerWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    VideoPlayerWidget *videoPlayerWidget;
    TimelineWidget *timelineWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QMenu *fileMenu;
    QAction *openAction;
    QAction *saveAction;
    QAction *cutAction;
    QAction *combineAction;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");

        videoPlayerWidget = new VideoPlayerWidget(centralwidget);
        videoPlayerWidget->setObjectName("videoPlayerWidget");
        verticalLayout->addWidget(videoPlayerWidget);

        timelineWidget = new TimelineWidget(centralwidget);
        timelineWidget->setObjectName("timelineWidget");
        verticalLayout->addWidget(timelineWidget);

        MainWindow->setCentralWidget(centralwidget);

        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);

        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName("fileMenu");
        menubar->addMenu(fileMenu);

        openAction = new QAction(MainWindow);
        openAction->setObjectName("openAction");
        saveAction = new QAction(MainWindow);
        saveAction->setObjectName("saveAction");
        cutAction = new QAction(MainWindow);
        cutAction->setObjectName("cutAction");
        combineAction = new QAction(MainWindow);
        combineAction->setObjectName("combineAction");

        fileMenu->addAction(openAction);
        fileMenu->addAction(saveAction);
        fileMenu->addAction(cutAction);
        fileMenu->addAction(combineAction);

        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Simple Video Editor", nullptr));
        fileMenu->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        openAction->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        saveAction->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        cutAction->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
        combineAction->setText(QCoreApplication::translate("MainWindow", "Combine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H