#include "PreviewSlider.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QStyle>

PreviewSlider::PreviewSlider(Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent), mediaPlayer(nullptr), mainVideoPlayer(nullptr) {
    previewLabel = new QLabel(this);
    previewLabel->setFixedSize(160, 90);
    previewLabel->setStyleSheet("background-color: black; border: 1px solid white;");
    previewLabel->hide();

    videoWidget = new QVideoWidget(previewLabel);
    videoWidget->setFixedSize(160, 90);

    connect(this, &QSlider::valueChanged, this, &PreviewSlider::updatePreview);
}

void PreviewSlider::setMediaPlayer(QMediaPlayer *player) {
    mediaPlayer = player;
    mediaPlayer->setVideoOutput(videoWidget);
}

void PreviewSlider::setMainVideoPlayer(QMediaPlayer *mainPlayer) {
    mainVideoPlayer = mainPlayer;
}

void PreviewSlider::mousePressEvent(QMouseEvent *event) {
    QSlider::mousePressEvent(event);
    if (mediaPlayer) {
        int value = QStyle::sliderValueFromPosition(minimum(), maximum(), event->pos().x(), width());
        setValue(value);
        previewLabel->move(event->pos().x() - previewLabel->width() / 2, -previewLabel->height());
        previewLabel->show();
    }
}

void PreviewSlider::updatePreview(int value) {
    if (mediaPlayer) {
        qint64 duration = mediaPlayer->duration();
        qint64 position = (duration * value) / maximum();
        mediaPlayer->setPosition(position);
        if (mainVideoPlayer) {
            mainVideoPlayer->setPosition(position);
        }
    }
}