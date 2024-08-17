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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimelineWidget
{
public:
    QVBoxLayout *verticalLayout;
    QSlider *timelineSlider;
    QPushButton *pausePlayButton;

    void setupUi(QWidget *TimelineWidget)
    {
        if (TimelineWidget->objectName().isEmpty())
            TimelineWidget->setObjectName("TimelineWidget");
        TimelineWidget->resize(1200, 400);
        verticalLayout = new QVBoxLayout(TimelineWidget);
        verticalLayout->setObjectName("verticalLayout");
        timelineSlider = new QSlider(TimelineWidget);
        timelineSlider->setObjectName("timelineSlider");
        timelineSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(timelineSlider);

        pausePlayButton = new QPushButton(TimelineWidget);
        pausePlayButton->setObjectName("pausePlayButton");

        verticalLayout->addWidget(pausePlayButton);

        retranslateUi(TimelineWidget);

        QMetaObject::connectSlotsByName(TimelineWidget);
    } // setupUi

    void retranslateUi(QWidget *TimelineWidget)
    {
        pausePlayButton->setText(QCoreApplication::translate("TimelineWidget", "▶️", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimelineWidget: public Ui_TimelineWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMELINEWIDGET_H