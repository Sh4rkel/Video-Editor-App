#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>
#include "ui_TimelineWidget.h"

class TimelineWidget : public QWidget, private Ui::TimelineWidget {
    Q_OBJECT

public:
    explicit TimelineWidget(QWidget *parent = nullptr);
    void updatePlayPauseButtonText(const QString &text);

    signals:
        void playPauseClicked();
    void positionChanged(int position);

    public slots:
        void setDuration(qint64 duration);
    void setPosition(qint64 position);

    private slots:
        void onPlayPauseButtonClicked();
    void onSliderMoved(int position);

private:
    qint64 videoDuration;
};

#endif // TIMELINEWIDGET_H