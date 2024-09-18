#include "VideoSegmentItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPen>
#include <QDebug>

// Constructor
VideoSegmentItem::VideoSegmentItem(QMediaPlayer *player, qint64 x, qint64 y, qint64 width, qint64 height, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent), mediaPlayer(player) {
    // Set initial brush color
    setBrush(QBrush(Qt::blue));
}

// Select the segment
void VideoSegmentItem::select() {
    isSelected = true;
    setBrush(QBrush(Qt::green)); // Change brush color to green
    setPen(QPen(Qt::yellow, 2)); // Change pen color to yellow with width 2
    emit segmentSelected(mediaPlayer); // Emit segmentSelected signal
}

// Deselect the segment
void VideoSegmentItem::deselect() {
    isSelected = false;
    setBrush(QBrush(Qt::blue)); // Change brush color back to blue
    setPen(QPen(Qt::black, 2)); // Change pen color back to black with width 2
}

// Get the media player associated with the segment
QMediaPlayer* VideoSegmentItem::getMediaPlayer() const {
    return mediaPlayer;
}

// Handle mouse press event
void VideoSegmentItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!isSelected) {
        select(); // Select the segment if not already selected
        if (mediaPlayer) {
            mediaPlayer->play(); // Play the media if mediaPlayer is not null
        } else {
            qDebug() << "Error: QMediaPlayer is null in mousePressEvent";
        }
    } else {
        deselect(); // Deselect the segment if already selected
        if (mediaPlayer) {
            mediaPlayer->pause(); // Pause the media if mediaPlayer is not null
        } else {
            qDebug() << "Error: QMediaPlayer is null in mousePressEvent";
        }
    }
    QGraphicsRectItem::mousePressEvent(event); // Call base class implementation
}