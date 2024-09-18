#include "VideoFrameWidget.h"
#include <QPainter>
#include <QDebug>

// Constructor
VideoFrameWidget::VideoFrameWidget(QWidget *parent) : QWidget(parent) {}

// Set the current frame to display
void VideoFrameWidget::setFrame(const QImage &frame) {
    currentFrame = frame;
    update();
}

// Paint event to render the current frame
void VideoFrameWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!currentFrame.isNull()) {
        painter.drawImage(rect(), currentFrame);
    } else {
        qDebug() << "No frame to display";
    }
}