#ifndef SPEEDWIDGET_H
#define SPEEDWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>

class SpeedWidget : public QWidget {
    Q_OBJECT

public:
    explicit SpeedWidget(QWidget *parent = nullptr);

    signals:
        void speedChanged(double speed);

    private slots:
        void onSpeedSliderChanged(int value);

private:
    QSlider *speedSlider;
    QLabel *speedLabel;
};

#endif // SPEEDWIDGET_H