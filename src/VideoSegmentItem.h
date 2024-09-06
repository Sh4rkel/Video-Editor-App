#ifndef VIDEOSEGMENTITEM_H
#define VIDEOSEGMENTITEM_H

#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QObject>

class VideoSegmentItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    VideoSegmentItem(QMediaPlayer *player, qint64 x, qint64 y, qint64 width, qint64 height);

    void select();
    void deselect();
    QMediaPlayer* getMediaPlayer() const;

    signals:
        void segmentSelected(QMediaPlayer *player);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QMediaPlayer *mediaPlayer;
    bool isSelected;
};

#endif