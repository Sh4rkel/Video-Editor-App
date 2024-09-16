#include "VideoFrameWidget.h"
#include <QPainter>
#include <QDebug>

VideoFrameWidget::VideoFrameWidget(QWidget *parent) : QWidget(parent) {}

void VideoFrameWidget::setFrame(const QImage &frame) {
    currentFrame = frame;
    update();
}

void VideoFrameWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!currentFrame.isNull()) {
        painter.drawImage(rect(), currentFrame);
    } else {
        qDebug() << "No frame to display";
    }
}