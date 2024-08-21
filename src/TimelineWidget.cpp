#include "TimelineWidget.h"
#include <QTime> // Add this include

TimelineWidget::TimelineWidget(QWidget *parent) : QWidget(parent), videoDuration(0) {
    setupUi(this);

    connect(playPauseButton, &QPushButton::clicked, this, &TimelineWidget::onPlayPauseButtonClicked);
    connect(timelineSlider, &QSlider::sliderMoved, this, &TimelineWidget::onSliderMoved);
}

void TimelineWidget::setDuration(qint64 duration) {
    videoDuration = duration;
    timelineSlider->setMaximum(static_cast<int>(duration));
    totalTimeLabel->setText(QTime::fromMSecsSinceStartOfDay(static_cast<int>(duration)).toString("mm:ss"));
}

void TimelineWidget::setPosition(qint64 position) {
    if (!timelineSlider->isSliderDown()) {
        timelineSlider->setValue(static_cast<int>(position));
    }
    currentTimeLabel->setText(QTime::fromMSecsSinceStartOfDay(static_cast<int>(position)).toString("mm:ss"));
}

void TimelineWidget::onPlayPauseButtonClicked() {
    if (playPauseButton->text() == "▶️") {
        playPauseButton->setText("⏸️");
    } else {
        playPauseButton->setText("▶️");
    }
    emit playPauseClicked();
}

void TimelineWidget::onSliderMoved(int position) {
    emit positionChanged(position);
}

void TimelineWidget::updatePlayPauseButtonText(const QString &text) {
    playPauseButton->setText(text);
}