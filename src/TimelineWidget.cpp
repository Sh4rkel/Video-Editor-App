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
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>

// Constructor
TimelineWidget::TimelineWidget(QWidget *parent) : QWidget(parent), totalDuration(0), selectedSegment(nullptr), currentMediaPlayer(nullptr) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    // Setup toolbar
    toolBar = new QToolBar(this);
    QAction *addVideoAction = new QAction(QIcon(":/icons/add.png"), "Add Video", this);
    connect(addVideoAction, &QAction::triggered, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Open Video File", "", "Video Files (*.mp4 *.avi *.mkv *.mov)");
        if (!filePath.isEmpty()) {
            addVideo(filePath);
        }
    });
    toolBar->addAction(addVideoAction);

    QAction *addVideosAction = new QAction(QIcon(":/icons/add_multiple.png"), "Add Multiple Videos", this);
    connect(addVideosAction, &QAction::triggered, this, &TimelineWidget::onAddVideosButtonClicked);
    toolBar->addAction(addVideosAction);

    QAction *playAction = new QAction(QIcon(":/icons/play.png"), "Play", this);
    connect(playAction, &QAction::triggered, this, &TimelineWidget::onPlayPauseButtonClicked);
    toolBar->addAction(playAction);

    QAction *pauseAction = new QAction(QIcon(":/icons/pause.png"), "Pause", this);
    connect(pauseAction, &QAction::triggered, this, &TimelineWidget::onPlayPauseButtonClicked);
    toolBar->addAction(pauseAction);

    mainLayout->addWidget(toolBar);

    // Setup graphics view and scene
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    mainLayout->addWidget(view);

    // Setup control layout
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

    // Setup background and play position line
    background = new QGraphicsRectItem(0, 0, 1000, 50);
    background->setBrush(QBrush(Qt::lightGray));
    scene->addItem(background);

    playPositionLine = new QGraphicsLineItem(0, 0, 0, 50);
    playPositionLine->setPen(QPen(Qt::red, 2));
    scene->addItem(playPositionLine);

    statusBar = new QStatusBar(this);
    mainLayout->addWidget(statusBar);
}

// Add video to the timeline
void TimelineWidget::addVideo(const QString &filePath) {
    QPointer<QMediaPlayer> mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, [this, mediaPlayer](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::LoadedMedia) {
            VideoSegmentItem *segment = new VideoSegmentItem(mediaPlayer, 0, 0, mediaPlayer->duration() / 1000, 50);
            scene->addItem(segment);
            mediaPlayers.append(mediaPlayer);
            totalDuration += mediaPlayer->duration();
            timelineSlider->setMaximum(totalDuration);
            totalTimeLabel->setText(QTime::fromMSecsSinceStartOfDay(totalDuration).toString("hh:mm:ss"));
        } else if (status == QMediaPlayer::InvalidMedia) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to load video: %1").arg(mediaPlayer->errorString()));
            mediaPlayer->deleteLater();
        }
    });
    mediaPlayer->setPosition(0);
}

// Render videos on the timeline
void TimelineWidget::renderVideos() {
    qDebug() << "Rendering videos";
    scene->clear();
    scene->addItem(background);
    scene->addItem(playPositionLine);
    qint64 currentPosition = 0;

    for (QPointer<QMediaPlayer> mediaPlayer : std::as_const(mediaPlayers)) {
        if (!mediaPlayer) continue;
        qint64 duration = mediaPlayer->duration();
        qDebug() << "Rendering video segment for" << mediaPlayer << "with duration" << duration;
        VideoSegmentItem *rect = new VideoSegmentItem(mediaPlayer, currentPosition, 0, duration / 1000, 50);
        connect(rect, &VideoSegmentItem::segmentSelected, this, &TimelineWidget::onSegmentSelected);
        scene->addItem(rect);
        currentPosition += duration / 1000;
    }
}

// Set total duration of the timeline
void TimelineWidget::setDuration(qint64 duration) {
    videoDuration = duration;
    timelineSlider->setMaximum(static_cast<int>(duration));
    totalTimeLabel->setText(QTime::fromMSecsSinceStartOfDay(static_cast<int>(duration)).toString("mm:ss"));
}

// Set current position on the timeline
void TimelineWidget::setPosition(qint64 position) {
    if (!timelineSlider->isSliderDown()) {
        timelineSlider->setValue(static_cast<int>(position));
    }
    currentTimeLabel->setText(QTime::fromMSecsSinceStartOfDay(static_cast<int>(position)).toString("mm:ss"));
    playPositionLine->setLine(position / 1000, 0, position / 1000, 50);
    if (currentMediaPlayer) {
        currentMediaPlayer->setPosition(position);
    }
}

// Handle play/pause button click
void TimelineWidget::onPlayPauseButtonClicked() {
    if (playPauseButton->text() == "▶️") {
        playPauseButton->setText("⏸️");
        if (currentMediaPlayer) {
            currentMediaPlayer->play();
        }
    } else {
        playPauseButton->setText("▶️");
        if (currentMediaPlayer) {
            currentMediaPlayer->pause();
        }
    }
    emit playPauseClicked();
}

// Handle slider moved event
void TimelineWidget::onSliderMoved(int position) {
    emit positionChanged(position);
    if (currentMediaPlayer) {
        currentMediaPlayer->setPosition(position);
    }
}

// Update play/pause button text
void TimelineWidget::updatePlayPauseButtonText(const QString &text) {
    playPauseButton->setText(text);
}

// Handle key press event
void TimelineWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        playPauseButton->click();
    } else {
        QWidget::keyPressEvent(event);
    }
}

// Handle segment selected event
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
    currentMediaPlayer = player;
    setPosition(player->position());
}

// Handle add multiple videos button click
void TimelineWidget::onAddVideosButtonClicked() {
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Video Files"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (fileNames.isEmpty()) {
        return;
    }

    for (const QString &fileName : fileNames) {
        addVideo(fileName);
    }
    renderVideos();
}

// Add frame widget to the layout
void TimelineWidget::addFrameWidget(QWidget *frameWidget) {
    frameLayout->addWidget(frameWidget);
}