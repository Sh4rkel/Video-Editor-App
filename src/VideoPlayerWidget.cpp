#include "VideoPlayerWidget.h"
#include "ui_VideoPlayerWidget.h"

VideoPlayerWidget::VideoPlayerWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::VideoPlayerWidget), mediaPlayer(new QMediaPlayer(this)), videoWidget(new QVideoWidget(this)) {
    ui->setupUi(this);
    mediaPlayer->setVideoOutput(videoWidget);
    ui->videoLayout->addWidget(videoWidget);
}

VideoPlayerWidget::~VideoPlayerWidget() {
    delete ui;
}

void VideoPlayerWidget::loadVideo(const QString &fileName) {
    mediaPlayer->setSource(QUrl::fromLocalFile(fileName));
    mediaPlayer->play();
}

QMediaPlayer* VideoPlayerWidget::getMediaPlayer() const {
    return mediaPlayer;
}

void VideoPlayerWidget::seek(int position) {
    mediaPlayer->setPosition(position);
}