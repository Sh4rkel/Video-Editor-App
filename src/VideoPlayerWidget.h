#ifndef VIDEOPLAYERWIDGET_H
#define VIDEOPLAYERWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>

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

private:
    Ui::VideoPlayerWidget *ui;
    QMediaPlayer *mediaPlayer;
};

#endif // VIDEOPLAYERWIDGET_H