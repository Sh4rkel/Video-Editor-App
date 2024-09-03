#ifndef VIDEOSEGMENTITEM_H
#define VIDEOSEGMENTITEM_H

#include <QGraphicsRectItem>
#include <QMediaPlayer>

class VideoSegmentItem : public QGraphicsRectItem {
public:
    VideoSegmentItem(QMediaPlayer *player, qreal x, qreal y, qreal width, qreal height);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QMediaPlayer *mediaPlayer;
};

#endif