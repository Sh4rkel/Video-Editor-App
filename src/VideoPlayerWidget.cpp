#include "VideoPlayerWidget.h"
#include "ui_VideoPlayerWidget.h"

VideoPlayerWidget::VideoPlayerWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::VideoPlayerWidget),
        mediaPlayer(new QMediaPlayer(this))
{
    ui->setupUi(this);
    mediaPlayer->setVideoOutput(ui->videoWidget);
}

VideoPlayerWidget::~VideoPlayerWidget()
{
    delete ui;
}

void VideoPlayerWidget::loadVideo(const QString &fileName)
{
    mediaPlayer->setSource(QUrl::fromLocalFile(fileName));
    mediaPlayer->play();
}
