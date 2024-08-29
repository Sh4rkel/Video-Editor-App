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
#include "FilterSettings.h"
#include "FilterSettingsDialog.h"

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
    void handleFileSelected(const QString &filePath);
    void showSpeedDialog();
    void addOverlayToVideo();
    void applyLightTheme();
    void applyGreenTheme();
    void applyBlueTheme();
    void applyDarkTheme();
    void applyPurpleNouncesTheme();
    void setupThemeMenu();
    void applyFilters();
    void updateFilterSettings();
    void showFilterSettingsDialog();

private:
    Ui::MainWindow *ui;
    VideoPlayerWidget *videoPlayerWidget;
    TimelineWidget *timelineWidget;
    SpeedDialog *speedDialog;
    SpeedWidget *speedWidget;
    FFmpegHandler *ffmpegHandler;
    FileHandler *fileHandler;
    QString currentVideo;
    QAction *openAction;
    QAction *saveAction;
    QAction *cutAction;
    QAction *combineAction;
    QAction *addTextAction;
    QAction *speedAction;
    QAction *addOverlayAction;
    QAction *filterSettingsAction;
    QMenuBar *menuBar;
    QMenu *videoMenu;
    QMenu *themeMenu;
    bool darkModeEnabled;
    FilterSettings *filterSettings;
    FilterSettingsDialog *filterSettingsDialog;
};

#endif // MAINWINDOW_H