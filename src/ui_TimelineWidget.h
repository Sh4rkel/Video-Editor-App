/********************************************************************************
** Form generated from reading UI file 'TimelineWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMELINEWIDGET_H
#define UI_TIMELINEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimelineWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *currentTimeLabel;
    QSlider *timelineSlider;
    QLabel *totalTimeLabel;
    QPushButton *playPauseButton;

    void setupUi(QWidget *TimelineWidget)
    {
        if (TimelineWidget->objectName().isEmpty())
            TimelineWidget->setObjectName("TimelineWidget");
        TimelineWidget->resize(800, 100);
        verticalLayout = new QVBoxLayout(TimelineWidget);
        verticalLayout->setObjectName("verticalLayout");

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");

        playPauseButton = new QPushButton(TimelineWidget);
        playPauseButton->setObjectName("playPauseButton");
        playPauseButton->setFixedSize(30, 30);
        horizontalLayout->addWidget(playPauseButton);

        currentTimeLabel = new QLabel(TimelineWidget);
        currentTimeLabel->setObjectName("currentTimeLabel");
        currentTimeLabel->setText("00:00");
        horizontalLayout->addWidget(currentTimeLabel);

        timelineSlider = new QSlider(TimelineWidget);
        timelineSlider->setObjectName("timelineSlider");
        timelineSlider->setOrientation(Qt::Horizontal);
        horizontalLayout->addWidget(timelineSlider);

        totalTimeLabel = new QLabel(TimelineWidget);
        totalTimeLabel->setObjectName("totalTimeLabel");
        totalTimeLabel->setText("00:00");
        horizontalLayout->addWidget(totalTimeLabel);

        verticalLayout->addLayout(horizontalLayout);

        retranslateUi(TimelineWidget);

        QMetaObject::connectSlotsByName(TimelineWidget);
    } // setupUi

    void retranslateUi(QWidget *TimelineWidget)
    {
        playPauseButton->setText(QCoreApplication::translate("TimelineWidget", "▶️", nullptr));
    } 

};

namespace Ui {
    class TimelineWidget: public Ui_TimelineWidget {};
} 

QT_END_NAMESPACE

#endif 