#include "TimelineWidget.h"
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QMediaPlayer>
#include <QUrl>
#include <QTime>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>

TimelineWidget::TimelineWidget(QWidget *parent) : QWidget(parent), totalDuration(0), selectedSegment(nullptr) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    mainLayout->addWidget(view);

    QHBoxLayout *controlLayout = new QHBoxLayout();
    playPauseButton = new QPushButton("▶️", this);
    connect(playPauseButton, &QPushButton::clicked, this, &TimelineWidget::onPlayPauseButtonClicked);
    controlLayout->addWidget(playPauseButton);

    timelineSlider = new QSlider(Qt::Horizontal, this);
    connect(timelineSlider, &QSlider::sliderMoved, this, &TimelineWidget::onSliderMoved);
    controlLayout->addWidget(timelineSlider);

    currentTimeLabel = new QLabel("00:00", this);
    controlLayout->addWidget(currentTimeLabel);

    totalTimeLabel = new QLabel("00:00", this);
    controlLayout->addWidget(totalTimeLabel);

    mainLayout->addLayout(controlLayout);

    background = new QGraphicsRectItem(0, 0, 1000, 50);
    background->setBrush(QBrush(Qt::lightGray));
    scene->addItem(background);

    playPositionLine = new QGraphicsLineItem(0, 0, 0, 50);
    playPositionLine->setPen(QPen(Qt::red, 2));
    scene->addItem(playPositionLine);
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
        renderVideos();
    });

    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &TimelineWidget::positionChanged);
}

void TimelineWidget::renderVideos() {
    scene->clear();
    scene->addItem(background);
    scene->addItem(playPositionLine);
    qint64 currentPosition = 0;

    for (QMediaPlayer *mediaPlayer : std::as_const(mediaPlayers)) {
        qint64 duration = mediaPlayer->duration();
        VideoSegmentItem *rect = new VideoSegmentItem(mediaPlayer, currentPosition, 0, duration / 1000, 50);
        connect(rect, &VideoSegmentItem::segmentSelected, this, &TimelineWidget::onSegmentSelected);
        scene->addItem(rect);
        currentPosition += duration / 1000;
    }
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
    playPositionLine->setLine(position / 1000, 0, position / 1000, 50);
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

void TimelineWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        playPauseButton->click();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void TimelineWidget::onSegmentSelected(QMediaPlayer *player) {
    if (selectedSegment) {
        selectedSegment->deselect();
    }
    for (auto *segment : scene->items()) {
        auto *videoSegment = dynamic_cast<VideoSegmentItem*>(segment);
        if (videoSegment && videoSegment->getMediaPlayer() == player) {
            selectedSegment = videoSegment;
            selectedSegment->select();
            break;
        }
    }
    setPosition(player->position());
}