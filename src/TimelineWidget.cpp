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
    connect(slider, &QSlider::valueChanged, this, &TimelineWidget::onSliderValueChanged);
    connect(ui->pausePlayButton, &QPushButton::clicked, this, &TimelineWidget::onPlayPauseButtonClicked);
}

void TimelineWidget::onSliderValueChanged(int value)
{
    emit positionChanged(value);
}

void TimelineWidget::onPlayPauseButtonClicked()
{
    isPlaying = !isPlaying; // Toggle isPlaying
    if (isPlaying) {
        ui->pausePlayButton->setText("⏸️"); // Change button text to pause symbol
    } else {
        ui->pausePlayButton->setText("▶️"); // Change button text to play symbol
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