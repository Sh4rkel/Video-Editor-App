/********************************************************************************
** Form generated from reading UI file 'VideoPlayerWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPLAYERWIDGET_H
#define UI_VIDEOPLAYERWIDGET_H

#include <QtCore/QVariant>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoPlayerWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *fileListWidget;
    QVBoxLayout *videoLayout;
    QVideoWidget *videoWidget;

    void setupUi(QWidget *VideoPlayerWidget)
    {
        if (VideoPlayerWidget->objectName().isEmpty())
            VideoPlayerWidget->setObjectName("VideoPlayerWidget");
        VideoPlayerWidget->resize(800, 650);

        horizontalLayout = new QHBoxLayout(VideoPlayerWidget);
        horizontalLayout->setObjectName("horizontalLayout");

        fileListWidget = new QListWidget(VideoPlayerWidget);
        fileListWidget->setObjectName("fileListWidget");
        horizontalLayout->addWidget(fileListWidget);

        videoLayout = new QVBoxLayout();
        videoLayout->setObjectName("videoLayout");

        videoWidget = new QVideoWidget(VideoPlayerWidget);
        videoWidget->setObjectName("videoWidget");
        videoLayout->addWidget(videoWidget);

        horizontalLayout->addLayout(videoLayout);
    } // setupUi

    void retranslateUi(QWidget *VideoPlayerWidget)
    {
        VideoPlayerWidget->setWindowTitle(QCoreApplication::translate("VideoPlayerWidget", "Video Player", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoPlayerWidget: public Ui_VideoPlayerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPLAYERWIDGET_H