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
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimelineWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSlider *timelineSlider;

    void setupUi(QWidget *TimelineWidget)
    {
        if (TimelineWidget->objectName().isEmpty())
            TimelineWidget->setObjectName("TimelineWidget");
        TimelineWidget->resize(800, 50);
        horizontalLayout = new QHBoxLayout(TimelineWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        timelineSlider = new QSlider(TimelineWidget);
        timelineSlider->setObjectName("timelineSlider");
        timelineSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(timelineSlider);


        retranslateUi(TimelineWidget);

        QMetaObject::connectSlotsByName(TimelineWidget);
    } // setupUi

    void retranslateUi(QWidget *TimelineWidget)
    {
        TimelineWidget->setWindowTitle(QCoreApplication::translate("TimelineWidget", "Timeline", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimelineWidget: public Ui_TimelineWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMELINEWIDGET_H
