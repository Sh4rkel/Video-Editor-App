#ifndef VIDEOSEGMENTITEM_H
#define VIDEOSEGMENTITEM_H

#include <QGraphicsRectItem>
#include <QMediaPlayer>

class VideoSegmentItem : public QGraphicsRectItem {
public:
    VideoSegmentItem(QMediaPlayer *player, qreal x, qreal y, qreal width, qreal height);

    void select();
    void deselect();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QMediaPlayer *mediaPlayer;
    bool isSelected;
};

#endif