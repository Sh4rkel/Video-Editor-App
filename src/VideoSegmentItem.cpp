#include "VideoSegmentItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QDebug>

VideoSegmentItem::VideoSegmentItem(QMediaPlayer *player, qreal x, qreal y, qreal width, qreal height)
    : QObject(), QGraphicsRectItem(x, y, width, height), mediaPlayer(player), isSelected(false) {
    setBrush(QBrush(Qt::blue));
    if (!mediaPlayer) {
        qDebug() << "Error: QMediaPlayer is null in VideoSegmentItem constructor";
    }
}

void VideoSegmentItem::select() {
    isSelected = true;
    setBrush(QBrush(Qt::green));
    emit segmentSelected(mediaPlayer);
}

void VideoSegmentItem::deselect() {
    isSelected = false;
    setBrush(QBrush(Qt::blue));
}

QMediaPlayer* VideoSegmentItem::getMediaPlayer() const {
    return mediaPlayer;
}

void VideoSegmentItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!isSelected) {
        select();
        if (mediaPlayer) {
            mediaPlayer->play();
        } else {
            qDebug() << "Error: QMediaPlayer is null in mousePressEvent";
        }
    } else {
        deselect();
        if (mediaPlayer) {
            mediaPlayer->pause();
        } else {
            qDebug() << "Error: QMediaPlayer is null in mousePressEvent";
        }
    }
    QGraphicsRectItem::mousePressEvent(event);
}