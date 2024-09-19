#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include <QStatusBar>
#include <QPointer>
#include <QVBoxLayout>
#include "VideoSegmentItem.h"

class TimelineWidget : public QWidget {
    Q_OBJECT

public:
    explicit TimelineWidget(QWidget *parent = nullptr);
    void updatePlayPauseButtonText(const QString &text);
    void addVideo(const QString &filePath);
    void renderVideos();
    void addFrameWidget(QWidget *frameWidget);
    void addTextOverlay(const QString &text, const QPointF &position, const QFont &font, const QColor &color); // Add semicolon here

    signals:
        void playPauseClicked();
    void positionChanged(int position);

    public slots:
        void setDuration(qint64 duration);
    void setPosition(qint64 position);

    private slots:
        void onPlayPauseButtonClicked();
    void onSliderMoved(int position);
    void onSegmentSelected(QMediaPlayer *player);
    void onAddVideosButtonClicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QList<QPointer<QMediaPlayer>> mediaPlayers;
    qint64 totalDuration;
    qint64 videoDuration;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QSlider *timelineSlider;
    QLabel *currentTimeLabel;
    QLabel *totalTimeLabel;
    QPushButton *playPauseButton;
    VideoSegmentItem *selectedSegment;
    QGraphicsRectItem *background;
    QGraphicsLineItem *playPositionLine;
    QPointer<QMediaPlayer> currentMediaPlayer;
    QToolBar *toolBar;
    QStatusBar *statusBar;
    QPointer<QMediaPlayer> mediaPlayer;
    QVBoxLayout *frameLayout;
};

#endif