#ifndef VIDEOPLAYERWIDGET_H
#define VIDEOPLAYERWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "TextOverlayWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VideoPlayerWidget; }
QT_END_NAMESPACE

class VideoPlayerWidget : public QWidget
{
Q_OBJECT

public:
    explicit VideoPlayerWidget(QWidget *parent = nullptr);
    ~VideoPlayerWidget();

    void loadVideo(const QString &fileName);
    void addTextOverlay(const QString &text);
    void showEvent(QShowEvent *event);
    void checkOverlayPosition();
    void resizeEvent(QResizeEvent *event);

public slots:
    void seek(int position);

private:
    Ui::VideoPlayerWidget *ui;
    QMediaPlayer *mediaPlayer;
    TextOverlayWidget *textOverlayWidget;
};

#endif