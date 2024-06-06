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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimelineWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *pausePlayButton;
    QSlider *timelineSlider;

    void setupUi(QWidget *TimelineWidget)
    {
        if (TimelineWidget->objectName().isEmpty())
            TimelineWidget->setObjectName("TimelineWidget");
        TimelineWidget->resize(800, 85);
        horizontalLayout = new QHBoxLayout(TimelineWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        pausePlayButton = new QPushButton(TimelineWidget);
        pausePlayButton->setObjectName("pausePlayButton");

        horizontalLayout->addWidget(pausePlayButton);

        timelineSlider = new QSlider(TimelineWidget);
        timelineSlider->setObjectName("timelineSlider");
        timelineSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(timelineSlider);


        retranslateUi(TimelineWidget);

        QMetaObject::connectSlotsByName(TimelineWidget);
    } // setupUi

    void retranslateUi(QWidget *TimelineWidget)
    {
        TimelineWidget->setWindowTitle(QCoreApplication::translate("TimelineWidget", "Timeline", nullptr));
        pausePlayButton->setText(QCoreApplication::translate("TimelineWidget", "\342\217\270\357\270\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimelineWidget: public Ui_TimelineWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMELINEWIDGET_H
