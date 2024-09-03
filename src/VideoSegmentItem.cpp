#include "VideoSegmentItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

VideoSegmentItem::VideoSegmentItem(QMediaPlayer *player, qreal x, qreal y, qreal width, qreal height)
    : QGraphicsRectItem(x, y, width, height), mediaPlayer(player) {
    setBrush(QBrush(Qt::blue));
}

void VideoSegmentItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    setBrush(QBrush(Qt::green));
    mediaPlayer->play();
    QGraphicsRectItem::mousePressEvent(event);
}