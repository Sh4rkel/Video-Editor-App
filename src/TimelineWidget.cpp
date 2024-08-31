#include "TimelineWidget.h"
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QMediaPlayer>
#include <QUrl>
#include <QTime>
#include <QDebug>

TimelineWidget::TimelineWidget(QWidget *parent) : QWidget(parent), totalDuration(0) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    setLayout(layout);
}

void TimelineWidget::addVideo(const QString &filePath) {
    QMediaPlayer *mediaPlayer = new QMediaPlayer(this);
    if (!mediaPlayer) {
        qDebug() << "Failed to create QMediaPlayer";
        return;
    }

    mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
    mediaPlayers.append(mediaPlayer);

    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, [this, mediaPlayer](qint64 duration) {
        totalDuration += duration;
        emit setDuration(totalDuration);
    });

    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &TimelineWidget::positionChanged);
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