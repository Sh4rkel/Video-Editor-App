#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FileImportWidget.h"
#include "TimelineWidget.h"
#include "VideoPlayerWidget.h"
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
    void onFileImported(const QString &fileName);

private:
    Ui::MainWindow *ui;
    FFmpegHandler *ffmpegHandler;
    QString currentVideo;
    FileImportWidget *fileImportWidget;
    TimelineWidget *timelineWidget;
    VideoPlayerWidget *videoPlayerWidget;
};

#endif // MAINWINDOW_H