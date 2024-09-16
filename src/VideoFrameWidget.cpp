#include "VideoFrameWidget.h"
#include <QPainter>

VideoFrameWidget::VideoFrameWidget(QWidget *parent) : QWidget(parent) {}

void VideoFrameWidget::setFrame(const QImage &frame) {
    currentFrame = frame;
    update();
}

void VideoFrameWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!currentFrame.isNull()) {
        painter.drawImage(rect(), currentFrame);
    }
}