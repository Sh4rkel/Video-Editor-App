#ifndef SPEEDWIDGET_H
#define SPEEDWIDGET_H

#include <QWidget>
#include <QComboBox>

class SpeedWidget : public QWidget {
    Q_OBJECT

public:
    explicit SpeedWidget(QWidget *parent = nullptr);

    signals:
        void speedChanged(qreal speed);

    private slots:
        void onSpeedChanged(int index);

private:
    QComboBox *speedComboBox;
};

#endif // SPEEDWIDGET_H