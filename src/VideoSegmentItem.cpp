#include "VideoSegmentItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPen>
#include <QDebug>

VideoSegmentItem::VideoSegmentItem(QMediaPlayer *player, qint64 x, qint64 y, qint64 width, qint64 height)
    : QObject(), QGraphicsRectItem(x, y, width, height), mediaPlayer(player), isSelected(false) {
    setBrush(QBrush(Qt::blue));
    setPen(QPen(Qt::black, 2));
    if (!mediaPlayer) {
        qDebug() << "Error: QMediaPlayer is null in VideoSegmentItem constructor";
    }
}

void VideoSegmentItem::select() {
    isSelected = true;
    setBrush(QBrush(Qt::green));
    setPen(QPen(Qt::yellow, 2));
    emit segmentSelected(mediaPlayer);
}

void VideoSegmentItem::deselect() {
    isSelected = false;
    setBrush(QBrush(Qt::blue));
    setPen(QPen(Qt::black, 2));
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