#include "VideoPlayerWidget.h"
#include "ui_VideoPlayerWidget.h"
#include <QUrl>
#include <QMediaPlayer>
#include <QGraphicsScene>
// Constructor
VideoPlayerWidget::VideoPlayerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::VideoPlayerWidget), mediaPlayer(new QMediaPlayer(this)), scene(new QGraphicsScene(this)) {
    ui->setupUi(this);
    mediaPlayer->setVideoOutput(ui->videoWidget);
}

// Destructor
VideoPlayerWidget::~VideoPlayerWidget() {
    delete ui;
}

// Load video file
void VideoPlayerWidget::loadVideo(const QString &fileName) {
    mediaPlayer->setSource(QUrl::fromLocalFile(fileName));
    mediaPlayer->play();
}

// Get media player instance
QMediaPlayer* VideoPlayerWidget::getMediaPlayer() const {
    return mediaPlayer;
}

// Seek to a specific position in the video
void VideoPlayerWidget::seek(int position) {
    mediaPlayer->setPosition(position);
}

// Set playback speed
void VideoPlayerWidget::setSpeed(double speed) {
    mediaPlayer->setPlaybackRate(speed);
}

QGraphicsScene* VideoPlayerWidget::getScene() const {
    return scene;
}