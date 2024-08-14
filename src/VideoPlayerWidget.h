#ifndef VIDEOPLAYERWIDGET_H
#define VIDEOPLAYERWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "TextOverlayWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VideoPlayerWidget; }
QT_END_NAMESPACE

class VideoPlayerWidget : public QWidget {
    Q_OBJECT

    public:
    explicit VideoPlayerWidget(QWidget *parent = nullptr);
    ~VideoPlayerWidget();
    void loadVideo(const QString &fileName);
    void seek(int position);
    QMediaPlayer* getMediaPlayer() const;
    void setPlaybackRate(double rate);
    void addTextOverlay(const QString &text);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    Ui::VideoPlayerWidget *ui;
    QMediaPlayer *mediaPlayer;
    TextOverlayWidget *textOverlayWidget;
    void checkOverlayPosition();
};

#endif // VIDEOPLAYERWIDGET_H