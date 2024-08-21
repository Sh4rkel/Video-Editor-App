#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "VideoPlayerWidget.h"
#include "TimelineWidget.h"
#include "SpeedWidget.h"
#include "FFmpegHandler.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    private slots:
        void openFile();
    void saveFile();
    void cutVideo();
    void combineVideos();
    void togglePlayPause();
    void changeSpeed(qreal speed);
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status); // Add this slot

private:
    Ui::MainWindow *ui;
    VideoPlayerWidget *videoPlayerWidget;
    TimelineWidget *timelineWidget;
    SpeedWidget *speedWidget;
    FFmpegHandler *ffmpegHandler;
    QString currentVideo;
};

#endif // MAINWINDOW_H