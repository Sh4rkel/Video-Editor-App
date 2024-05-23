#include "VideoPlayerWidget.h"
#include "ui_VideoPlayerWidget.h"
#include "QTimer"
#include <QVideoWidget>
#include <QResizeEvent>
VideoPlayerWidget::VideoPlayerWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::VideoPlayerWidget),
        mediaPlayer(new QMediaPlayer(this)),
        textOverlayWidget(new TextOverlayWidget(this))
{
    ui->setupUi(this);
    mediaPlayer->setVideoOutput(ui->videoWidget);
    textOverlayWidget->setGeometry(ui->videoWidget->geometry());
    ui->videoWidget->setParent(this);
    ui->videoWidget->stackUnder(textOverlayWidget);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, textOverlayWidget, &QWidget::raise);
    timer->start(100);
}

VideoPlayerWidget::~VideoPlayerWidget()
{
    qDebug() << "VideoPlayerWidget destroyed";
    delete ui;
}

void VideoPlayerWidget::loadVideo(const QString &fileName)
{
    mediaPlayer->setSource(QUrl::fromLocalFile(fileName));
    mediaPlayer->play();
    QTimer::singleShot(100, textOverlayWidget, &QWidget::raise);
}

void VideoPlayerWidget::seek(int position)
{
    mediaPlayer->setPosition(position);
}

void VideoPlayerWidget::checkOverlayPosition()
{
    QRect videoGeometry = ui->videoWidget->geometry();
    QRect overlayGeometry = textOverlayWidget->geometry();

    if(videoGeometry == overlayGeometry) {
        qDebug() << "TextOverlayWidget is correctly positioned over the QVideoWidget.";
    } else {
        qDebug() << "TextOverlayWidget is not correctly positioned over the QVideoWidget.";
    }

    if(textOverlayWidget->isVisible()) {
        qDebug() << "TextOverlayWidget is visible.";
    } else {
        qDebug() << "TextOverlayWidget is not visible.";
        textOverlayWidget->show();
    }

    QRegion visibleRegion = textOverlayWidget->visibleRegion();
    if(visibleRegion.boundingRect() == textOverlayWidget->rect()) {
        qDebug() << "TextOverlayWidget is not obscured by other widgets.";
    } else {
        qDebug() << "TextOverlayWidget might be obscured by other widgets.";
        textOverlayWidget->raise();
    }


}

void VideoPlayerWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    textOverlayWidget->setGeometry(ui->videoWidget->geometry());
    textOverlayWidget->show();
    textOverlayWidget->raise();
    checkOverlayPosition();
}

void VideoPlayerWidget::addTextOverlay(const QString &text)
{
    if (!text.isEmpty()) {
        textOverlayWidget->setText(text);
        textOverlayWidget->show();
        textOverlayWidget->raise();
        checkOverlayPosition();
        textOverlayWidget->update();
    }
}

void VideoPlayerWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    textOverlayWidget->setGeometry(ui->videoWidget->geometry());
    textOverlayWidget->show();
    textOverlayWidget->raise();
    checkOverlayPosition();
}

