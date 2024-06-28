#include "TimelineWidget.h"
#include "ui_TimelineWidget.h"

TimelineWidget::TimelineWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TimelineWidget),
        isPlaying(false)
{

    ui->setupUi(this);
    slider = ui->timelineSlider;
    slider->setOrientation(Qt::Horizontal);
    speedSlider = new QSlider(this);
    speedSlider->setOrientation(Qt::Horizontal);
    speedSlider->setRange(50, 200);
    speedSlider->setValue(100);
    connect(speedSlider, &QSlider::valueChanged, [this](int value) {
        emit speedChanged(value / 100.0);
    });
    connect(slider, &QSlider::valueChanged, this, &TimelineWidget::onSliderValueChanged);
    connect(ui->pausePlayButton, &QPushButton::clicked, this, &TimelineWidget::onPlayPauseButtonClicked);
}

void TimelineWidget::onSliderValueChanged(int value)
{
    emit positionChanged(value);
}

void TimelineWidget::onPlayPauseButtonClicked()
{
    isPlaying = !isPlaying;
    if (isPlaying) {
        ui->pausePlayButton->setText("⏸️");
    } else {
        ui->pausePlayButton->setText("▶️");
    }
    emit playPauseClicked();
}

void TimelineWidget::setDuration(int duration)
{
    slider->setMaximum(duration);
}

void TimelineWidget::setPosition(int position)
{
    slider->setValue(position);
}

TimelineWidget::~TimelineWidget()
{
    delete ui;
}