#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VideoPlayerWidget.h"
#include "TimelineWidget.h"
#include "FFmpegHandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

private:
    Ui::MainWindow *ui;
    FFmpegHandler *ffmpegHandler;
    QString currentVideo;
    VideoPlayerWidget *videoPlayerWidget;
    TimelineWidget *timelineWidget;
};

#endif // MAINWINDOW_H