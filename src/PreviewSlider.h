#ifndef PREVIEWSLIDER_H
#define PREVIEWSLIDER_H

#include <QSlider>
#include <QLabel>
#include <QMediaPlayer>
#include <QVideoWidget>

class PreviewSlider : public QSlider {
    Q_OBJECT

public:
    explicit PreviewSlider(Qt::Orientation orientation, QWidget *parent = nullptr);
    void setMediaPlayer(QMediaPlayer *player);
    void setMainVideoPlayer(QMediaPlayer *mainPlayer);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    private slots:
        void updatePreview(int value);

private:
    QLabel *previewLabel;
    QMediaPlayer *mediaPlayer;
    QMediaPlayer *mainVideoPlayer;
    QVideoWidget *videoWidget;
};

#endif // PREVIEWSLIDER_H