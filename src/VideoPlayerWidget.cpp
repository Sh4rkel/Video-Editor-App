#include "VideoPlayerWidget.h"
#include "ui_VideoPlayerWidget.h"
#include <QTimer>
#include <QResizeEvent>

VideoPlayerWidget::VideoPlayerWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::VideoPlayerWidget), mediaPlayer(new QMediaPlayer(this)), textOverlayWidget(new TextOverlayWidget(this)) {
    ui->setupUi(this);
    mediaPlayer->setVideoOutput(ui->videoWidget);
    textOverlayWidget->setGeometry(ui->videoWidget->geometry());
    ui->videoWidget->setParent(this);
    ui->videoWidget->stackUnder(textOverlayWidget);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, textOverlayWidget, &QWidget::raise);
    timer->start(100);
}

VideoPlayerWidget::~VideoPlayerWidget() {
    delete ui;
}

void VideoPlayerWidget::loadVideo(const QString &fileName) {
    mediaPlayer->setSource(QUrl::fromLocalFile(fileName));
    mediaPlayer->play();
    QTimer::singleShot(100, textOverlayWidget, &QWidget::raise);
}

void VideoPlayerWidget::seek(int position) {
    mediaPlayer->setPosition(position);
}

void VideoPlayerWidget::checkOverlayPosition() {
    QRect videoGeometry = ui->videoWidget->geometry();
    QRect overlayGeometry = textOverlayWidget->geometry();

    if (textOverlayWidget->isVisible()) {
        qDebug() << "TextOverlayWidget is visible.";
    } else {
        qDebug() << "TextOverlayWidget is not visible.";
        textOverlayWidget->show();
    }

    QRegion visibleRegion = textOverlayWidget->visibleRegion();
}

void VideoPlayerWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    textOverlayWidget->setGeometry(ui->videoWidget->geometry());
    textOverlayWidget->show();
    textOverlayWidget->raise();
    checkOverlayPosition();
}

void VideoPlayerWidget::addTextOverlay(const QString &text) {
    if (!text.isEmpty()) {
        textOverlayWidget->setText(text);
        textOverlayWidget->show();
        textOverlayWidget->raise();
        checkOverlayPosition();
        textOverlayWidget->update();
    }
}

void VideoPlayerWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    textOverlayWidget->setGeometry(ui->videoWidget->geometry());
    textOverlayWidget->show();
    textOverlayWidget->raise();
    checkOverlayPosition();
}

QMediaPlayer* VideoPlayerWidget::getMediaPlayer() const {
    return mediaPlayer;
}

void VideoPlayerWidget::setPlaybackRate(double rate) {
    mediaPlayer->setPlaybackRate(rate);
}