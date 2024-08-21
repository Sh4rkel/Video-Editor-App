#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "VideoPlayerWidget.h" // Add this include
#include "TimelineWidget.h"    // Add this include
#include "SpeedWidget.h"       // Add this include
#include "FFmpegHandler.h"     // Add this include

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