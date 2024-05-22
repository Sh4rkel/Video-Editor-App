#include "TimelineWidget.h"
#include "ui_TimelineWidget.h"

TimelineWidget::TimelineWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TimelineWidget),
        slider(new QSlider(this))
{
    ui->setupUi(this);
    slider->setOrientation(Qt::Horizontal);
    connect(slider, &QSlider::valueChanged, this, &TimelineWidget::onSliderValueChanged);
}

TimelineWidget::~TimelineWidget()
{
    delete ui;
}

void TimelineWidget::onSliderValueChanged(int value)
{
    emit positionChanged(value);
}