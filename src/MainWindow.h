#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FFmpegHandler.h"
#include "VideoPlayerWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FFmpegHandler *ffmpegHandler;
    QString currentVideo;

    private slots:
        void openFile();
    void saveFile();
    void cutVideo();
    void addTextToVideo();
    void combineVideos();
    void togglePlayPause();
};

#endif // MAINWINDOW_H