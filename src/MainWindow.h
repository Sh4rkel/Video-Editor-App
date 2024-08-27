#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "VideoPlayerWidget.h"
#include "TimelineWidget.h"
#include "SpeedDialog.h"
#include "FFmpegHandler.h"
#include "FileHandler.h"
#include "SpeedWidget.h"

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
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void addTextToVideo();
    void toggleTheme();
    void handleFileSelected(const QString &filePath);
    void showSpeedDialog();
    void addOverlayToVideo();  // Ensure this slot is declared

private:
    Ui::MainWindow *ui;
    VideoPlayerWidget *videoPlayerWidget;
    TimelineWidget *timelineWidget;
    SpeedDialog *speedDialog;
    SpeedWidget *speedWidget;
    FFmpegHandler *ffmpegHandler;
    QString currentVideo;
    QAction *openAction;
    QAction *saveAction;
    QAction *cutAction;
    QAction *combineAction;
    QAction *addTextAction;
    QAction *toggleThemeAction;
    QAction *speedAction;
    QAction *addOverlayAction;  // Ensure this action is declared
    QMenuBar *menuBar;
    QMenu *videoMenu;
    QMenu *themeMenu;
    FileHandler *fileHandler;
    bool darkModeEnabled;
};

#endif // MAINWINDOW_H