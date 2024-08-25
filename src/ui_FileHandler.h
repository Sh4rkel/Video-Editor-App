/********************************************************************************
** Form generated from reading UI file 'filehandler.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEHANDLER_H
#define UI_FILEHANDLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileHandler
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *addVideoButton;
    QListWidget *videoListWidget;

    void setupUi(QWidget *FileHandler)
    {
        if (FileHandler->objectName().isEmpty())
            FileHandler->setObjectName("FileHandler");
        FileHandler->resize(400, 300);
        verticalLayout = new QVBoxLayout(FileHandler);
        verticalLayout->setObjectName("verticalLayout");
        addVideoButton = new QPushButton(FileHandler);
        addVideoButton->setObjectName("addVideoButton");

        verticalLayout->addWidget(addVideoButton);

        videoListWidget = new QListWidget(FileHandler);
        videoListWidget->setObjectName("videoListWidget");

        verticalLayout->addWidget(videoListWidget);


        retranslateUi(FileHandler);

        QMetaObject::connectSlotsByName(FileHandler);
    } // setupUi

    void retranslateUi(QWidget *FileHandler)
    {
        FileHandler->setWindowTitle(QCoreApplication::translate("FileHandler", "FileHandler", nullptr));
        addVideoButton->setText(QCoreApplication::translate("FileHandler", "Add Video", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileHandler: public Ui_FileHandler {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEHANDLER_H
