#ifndef VIDEOPLAYERWIDGET_H
#define VIDEOPLAYERWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class VideoPlayerWidget; }
QT_END_NAMESPACE

class VideoPlayerWidget : public QWidget {
    Q_OBJECT

public:
    explicit VideoPlayerWidget(QWidget *parent = nullptr);
    ~VideoPlayerWidget();
    void loadVideo(const QString &fileName);
    QMediaPlayer* getMediaPlayer() const;
    void seek(int position);
    void setSpeed(double speed);
    QGraphicsScene* getScene() const;

private:
    Ui::VideoPlayerWidget *ui;
    QMediaPlayer *mediaPlayer;
    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // VIDEOPLAYERWIDGET_H