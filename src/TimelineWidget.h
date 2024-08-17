#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class TimelineWidget; }
QT_END_NAMESPACE

class TimelineWidget : public QWidget {
    Q_OBJECT

public:
    explicit TimelineWidget(QWidget *parent = nullptr);
    ~TimelineWidget();
    void setDuration(int duration);
    void setPosition(int position);

    signals:
        void positionChanged(int position);
    void playPauseClicked();
    void speedChanged(double speed);

    private slots:
        void onSliderValueChanged(int value);
    void onPlayPauseButtonClicked();

private:
    Ui::TimelineWidget *ui;
    QSlider *slider;
    QSlider *speedSlider;
    QPushButton *playPauseButton;
    QHBoxLayout *controlsLayout;
    QVBoxLayout *mainLayout;
    bool isPlaying;
};

#endif // TIMELINEWIDGET_H