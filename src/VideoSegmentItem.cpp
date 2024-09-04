#include "VideoSegmentItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

VideoSegmentItem::VideoSegmentItem(QMediaPlayer *player, qreal x, qreal y, qreal width, qreal height)
    : QGraphicsRectItem(x, y, width, height), mediaPlayer(player), isSelected(false) {
    setBrush(QBrush(Qt::blue));
}

void VideoSegmentItem::select() {
    isSelected = true;
    setBrush(QBrush(Qt::green));
}

void VideoSegmentItem::deselect() {
    isSelected = false;
    setBrush(QBrush(Qt::blue));
}

void VideoSegmentItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!isSelected) {
        select();
        mediaPlayer->play();
    } else {
        deselect();
        mediaPlayer->pause();
    }
    QGraphicsRectItem::mousePressEvent(event);
}