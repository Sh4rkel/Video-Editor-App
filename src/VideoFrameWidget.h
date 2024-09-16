#ifndef VIDEOFRAMEWIDGET_H
#define VIDEOFRAMEWIDGET_H

#include <QWidget>
#include <QImage>

class VideoFrameWidget : public QWidget {
    Q_OBJECT

public:
    explicit VideoFrameWidget(QWidget *parent = nullptr);
    void setFrame(const QImage &frame);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QImage currentFrame;
};

#endif