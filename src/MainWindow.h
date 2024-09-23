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
#include "SettingsDialog.h"
#include <QProgressBar>

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
    void addTextOverlay();
    void handleFileSelected(const QString &filePath);
    void addOverlayToVideo();
    void applyLightTheme();
    void applyGreenTheme();
    void applyBlueTheme();
    void applyDarkTheme();
    void applyPurpleNouncesTheme();
    void applyBorders();
    void applyButtonBorders();
    void applySliderBorders();
    void applyMenuBarBorders();
    void applyToolBarBorders();
    void applyGradientTheme();
    void setupThemeMenu();
    void addVideosToTimeline();
    void applyCustomStyle();
    void updateProgressBar(qint64 duration);
    void openSettings();
    void applySmoothTransition(QWidget *widget, const QRect &startRect, const QRect &endRect);
    void applyModernStyle();
    void applyShadows();
    void openFilterSettings();
    void applyFilter(const QString &filter);

private:
    Ui::MainWindow *ui;
    VideoPlayerWidget *videoPlayerWidget;
    TimelineWidget *timelineWidget;
    SpeedDialog *speedDialog;
    SpeedWidget *speedWidget;
    SettingsDialog *settingsDialog;
    FFmpegHandler *ffmpegHandler;
    QString currentVideo;
    QString outputVideo;
    QAction *openAction;
    QAction *saveAction;
    QAction *cutAction;
    QAction *combineAction;
    QAction *addTextAction;
    QAction *addOverlayAction;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QMenu *videoMenu;
    QMenu *themeMenu;
    QMenu *settingsMenu;
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    FileHandler *fileHandler;
    bool darkModeEnabled;
};

#endif 
