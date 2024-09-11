#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QMediaPlayer>
#include "filehandler.h"
#include "FFmpegHandler.h"
#include <QSplitter>
#include "FilterSettings.h"
#include "FFmpegWorker.h"
#include "SpeedDialog.h"
#include "VideoPlayerWidget.h"
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ffmpegHandler(new FFmpegHandler(this)),
    videoPlayerWidget(new VideoPlayerWidget(this)),
    timelineWidget(new TimelineWidget(this)),
    speedDialog(new SpeedDialog(this)),
    speedWidget(new SpeedWidget(this)),
    fileHandler(new FileHandler(this)),
    darkModeEnabled(true),
    currentVideo("")
{
    ui->setupUi(this);

    resize(1280, 720);

    videoPlayerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    timelineWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    fileHandler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(videoPlayerWidget, 3);
    mainLayout->addWidget(timelineWidget, 1);
    mainLayout->addWidget(fileHandler, 2);

    QSplitter *splitter = new QSplitter(Qt::Vertical, this);
    splitter->addWidget(videoPlayerWidget);
    splitter->addWidget(timelineWidget);
    splitter->addWidget(fileHandler);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->addWidget(speedWidget, 1);
    controlLayout->addWidget(timelineWidget, 9);

    mainLayout->addLayout(controlLayout);

    connect(timelineWidget, &TimelineWidget::positionChanged, videoPlayerWidget, &VideoPlayerWidget::seek);
    connect(timelineWidget, &TimelineWidget::playPauseClicked, this, &MainWindow::togglePlayPause);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::durationChanged, timelineWidget, &TimelineWidget::setDuration);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::positionChanged, timelineWidget, &TimelineWidget::setPosition);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);
    connect(speedWidget, &SpeedWidget::speedChanged, videoPlayerWidget, &VideoPlayerWidget::setSpeed);

    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    videoMenu = new QMenu(tr("Video"), this);
    menuBar->addMenu(videoMenu);

    openAction = new QAction(tr("Open"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    videoMenu->addAction(openAction);

    saveAction = new QAction(tr("Save"), this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    videoMenu->addAction(saveAction);

    cutAction = new QAction(tr("Cut"), this);
    connect(cutAction, &QAction::triggered, this, &MainWindow::cutVideo);
    videoMenu->addAction(cutAction);

    combineAction = new QAction(tr("Combine"), this);
    connect(combineAction, &QAction::triggered, this, &MainWindow::combineVideos);
    videoMenu->addAction(combineAction);

    addTextAction = new QAction(tr("Add Text"), this);
    connect(addTextAction, &QAction::triggered, this, &MainWindow::addTextToVideo);
    videoMenu->addAction(addTextAction);

    addOverlayAction = new QAction(tr("Add Overlay"), this);
    connect(addOverlayAction, &QAction::triggered, this, &MainWindow::addOverlayToVideo);
    videoMenu->addAction(addOverlayAction);

    QAction *addVideosAction = new QAction(tr("Add Videos to Timeline"), this);
    connect(addVideosAction, &QAction::triggered, this, &MainWindow::addVideosToTimeline);
    videoMenu->addAction(addVideosAction);

    connect(fileHandler, &FileHandler::fileSelected, this, &MainWindow::handleFileSelected);

    QShortcut *cutShortcut = new QShortcut(QKeySequence("Ctrl+X"), this);
    connect(cutShortcut, &QShortcut::activated, this, &MainWindow::cutVideo);

    QShortcut *combineShortcut = new QShortcut(QKeySequence("Ctrl+M"), this);
    connect(combineShortcut, &QShortcut::activated, this, &MainWindow::combineVideos);

    QShortcut *addTextShortcut = new QShortcut(QKeySequence("Ctrl+T"), this);
    connect(addTextShortcut, &QShortcut::activated, this, &MainWindow::addTextToVideo);

    QShortcut *addOverlayShortcut = new QShortcut(QKeySequence("Ctrl+O"), this);
    connect(addOverlayShortcut, &QShortcut::activated, this, &MainWindow::addOverlayToVideo);

    QShortcut *addVideosShortcut = new QShortcut(QKeySequence("Ctrl+Shift+A"), this);
    connect(addVideosShortcut, &QShortcut::activated, this, &MainWindow::addVideosToTimeline);

    setupThemeMenu();
}

void MainWindow::addVideosToTimeline() {
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Video Files"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (fileNames.isEmpty()) {
        return;
    }

    for (const QString &fileName : fileNames) {
        try {
            timelineWidget->addVideo(fileName);
        } catch (const std::exception &e) {
            QMessageBox::critical(this, tr("Error"), tr("Failed to add video: %1").arg(e.what()));
        }
    }
    timelineWidget->renderVideos();
}

void MainWindow::handleFileSelected(const QString &filePath) {
    currentVideo = filePath;
    videoPlayerWidget->loadVideo(filePath);
}

MainWindow::~MainWindow() {
    delete ui;
    delete ffmpegHandler;
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (!fileName.isEmpty()) {
        handleFileSelected(fileName);
    }
}

void MainWindow::saveFile() {
    if (currentVideo.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No video file is currently loaded.");
        return;
    }

    QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    bool ok;
    QStringList formats = {"mp4", "avi", "mkv", "mov"};
    QString format = QInputDialog::getItem(this, tr("Save Video File"), tr("Select the desired format:"), formats, 0, false, &ok);
    if (!ok || format.isEmpty()) {
        return;
    }

    ffmpegHandler->convertVideoFormat(currentVideo, outputVideo, format);
}

void MainWindow::cutVideo() {
    if (currentVideo.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No video file is currently loaded.");
        return;
    }

    bool ok;
    qint64 start = QInputDialog::getInt(this, tr("Cut Video"), tr("Start time (ms):"), 0, 0, INT_MAX, 1, &ok);
    if (!ok) return;
    qint64 end = QInputDialog::getInt(this, tr("Cut Video"), tr("End time (ms):"), 0, 0, INT_MAX, 1, &ok);
    if (!ok) return;

    QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Cut Video"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (outputVideo.isEmpty()) {
        return;
    }

    ffmpegHandler->cutVideoSegment(currentVideo, outputVideo, start, end);
}

void MainWindow::combineVideos() {
    QString videoFile1 = QFileDialog::getOpenFileName(this, tr("Open First Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (videoFile1.isEmpty()) {
        return;
    }

    QString videoFile2 = QFileDialog::getOpenFileName(this, tr("Open Second Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (videoFile2.isEmpty()) {
        return;
    }

    QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Combined Video"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (outputVideo.isEmpty()) {
        return;
    }

    ffmpegHandler->combineVideos(videoFile1, videoFile2, outputVideo);
}

void MainWindow::togglePlayPause() {
    QMediaPlayer *player = videoPlayerWidget->getMediaPlayer();
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
    } else {
        player->play();
    }
}

void MainWindow::handleMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        videoPlayerWidget->getMediaPlayer()->pause();
        timelineWidget->updatePlayPauseButtonText("▶️");
    }
}

void MainWindow::addTextToVideo() {
    if (currentVideo.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No video file is currently loaded.");
        return;
    }

    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Text to Video"), tr("Enter text:"), QLineEdit::Normal, "", &ok);
    if (!ok || text.isEmpty()) {
        return;
    }

    int x = QInputDialog::getInt(this, tr("Add Text to Video"), tr("X position:"), 0, 0, INT_MAX, 1, &ok);
    if (!ok) return;
    int y = QInputDialog::getInt(this, tr("Add Text to Video"), tr("Y position:"), 0, 0, INT_MAX, 1, &ok);
    if (!ok) return;

    QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Video with Text"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (outputVideo.isEmpty()) {
        return;
    }

    ffmpegHandler->addTextToVideo(currentVideo, outputVideo, text, x, y);
}

void MainWindow::applyLightTheme() {
    QString styleSheet = R"(
        QMainWindow {
            background-color: #FFFFFF;
            color: #000000;
        }
        QMenuBar {
            background-color: #F0F0F0;
            color: #000000;
        }
        QMenuBar::item {
            background-color: #F0F0F0;
            color: #000000;
        }
        QMenuBar::item:selected {
            background-color: #D0D0D0;
        }
        QMenu {
            background-color: #F0F0F0;
            color: #000000;
        }
    )";
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::applyDarkTheme() {
    QString styleSheet = R"(
        QMainWindow {
            background-color: #2E2E2E;
            color: #FFFFFF;
        }
        QMenuBar {
            background-color: #3E3E3E;
            color: #FFFFFF;
        }
        QMenuBar::item {
            background-color: #3E3E3E;
            color: #FFFFFF;
        }
        QMenuBar::item:selected {
            background-color: #5E5E5E;
        }
        QMenu {
            background-color: #3E3E3E;
            color: #FFFFFF;
        }
    )";
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::applyPurpleNouncesTheme() {
    QString styleSheet = R"(
        QMainWindow {
            background-color: #4B0082;
            color: #E6E6FA;
        }
        QMenuBar {
            background-color: #8A2BE2;
            color: #E6E6FA;
        }
        QMenuBar::item {
            background-color: #8A2BE2;
            color: #E6E6FA;
        }
        QMenuBar::item:selected {
            background-color: #9370DB;
        }
        QMenu {
            background-color: #8A2BE2;
            color: #E6E6FA;
        }
    )";
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::applyGreenTheme() {
    QString styleSheet = R"(
        QMainWindow {
            background-color: #008000;
            color: #F0FFF0;
        }
        QMenuBar {
            background-color: #32CD32;
            color: #F0FFF0;
        }
        QMenuBar::item {
            background-color: #32CD32;
            color: #F0FFF0;
        }
        QMenuBar::item:selected {
            background-color: #98FB98;
        }
        QMenu {
            background-color: #32CD32;
            color: #F0FFF0;
        }
    )";
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::applyBlueTheme() {
    QString styleSheet = R"(
        QMainWindow {
            background-color: #0000FF;
            color: #F0F8FF;
        }
        QMenuBar {
            background-color: #1E90FF;
            color: #F0F8FF;
        }
        QMenuBar::item {
            background-color: #1E90FF;
            color: #F0F8FF;
        }
        QMenuBar::item:selected {
            background-color: #87CEFA;
        }
        QMenu {
            background-color: #1E90FF;
            color: #F0F8FF;
        }
    )";
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::applyCustomStyle() {
    QString styleSheet = R"(
        QMainWindow {
            background-color: #2E2E2E;
            color: #FFFFFF;
        }
        QMenuBar {
            background-color: #3E3E3E;
            color: #FFFFFF;
        }
        QMenuBar::item {
            background-color: #3E3E3E;
            color: #FFFFFF;
        }
        QMenuBar::item:selected {
            background-color: #5E5E5E;
        }
        QMenu {
            background-color: #3E3E3E;
            color: #FFFFFF;
        }
        QToolBar {
            background-color: #3E3E3E;
            border: 1px solid #5E5E5E;
        }
        QPushButton {
            background-color: #5E5E5E;
            color: #FFFFFF;
            border: 1px solid #7E7E7E;
            padding: 5px;
        }
        QPushButton:hover {
            background-color: #7E7E7E;
        }
        QSlider::groove:horizontal {
            border: 1px solid #5E5E5E;
            height: 8px;
            background: #3E3E3E;
        }
        QSlider::handle:horizontal {
            background: #5E5E5E;
            border: 1px solid #7E7E7E;
            width: 18px;
            margin: -2px 0;
        }
        QLabel {
            color: #FFFFFF;
        }
        QGraphicsView {
            border: 1px solid #5E5E5E;
        }
        QStatusBar {
            background-color: #3E3E3E;
            color: #FFFFFF;
        }
        QLineEdit {
            background-color: #5E5E5E;
            color: #FFFFFF;
            border: 1px solid #7E7E7E;
            padding: 5px;
        }
        QLineEdit:focus {
            border: 1px solid #9E9E9E;
        }
        QInputDialog {
            background-color: #2E2E2E;
            color: #FFFFFF;
        }
        QMessageBox {
            background-color: #2E2E2E;
            color: #FFFFFF;
        }
    )";
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::setupThemeMenu() {
    themeMenu = menuBar->addMenu(tr("&Theme"));

    QAction *lightThemeAction = new QAction(tr("Light Theme"), this);
    connect(lightThemeAction, &QAction::triggered, this, &MainWindow::applyLightTheme);
    themeMenu->addAction(lightThemeAction);

    QAction *darkThemeAction = new QAction(tr("Dark Theme"), this);
    connect(darkThemeAction, &QAction::triggered, this, &MainWindow::applyDarkTheme);
    themeMenu->addAction(darkThemeAction);

    QAction *purpleNouncesThemeAction = new QAction(tr("Purple Nounces Theme"), this);
    connect(purpleNouncesThemeAction, &QAction::triggered, this, &MainWindow::applyPurpleNouncesTheme);
    themeMenu->addAction(purpleNouncesThemeAction);

    QAction *greenThemeAction = new QAction(tr("Green Theme"), this);
    connect(greenThemeAction, &QAction::triggered, this, &MainWindow::applyGreenTheme);
    themeMenu->addAction(greenThemeAction);

    QAction *blueThemeAction = new QAction(tr("Blue Theme"), this);
    connect(blueThemeAction, &QAction::triggered, this, &MainWindow::applyBlueTheme);
    themeMenu->addAction(blueThemeAction);

    QAction *customStyleAction = new QAction(tr("Custom Style"), this);
    connect(customStyleAction, &QAction::triggered, this, &MainWindow::applyCustomStyle);
    themeMenu->addAction(customStyleAction);
}

void MainWindow::addOverlayToVideo() {
    if (currentVideo.isEmpty()) {
        return;
    }

    bool ok;
    QString overlayText = QInputDialog::getText(this, tr("Add Overlay Text"), tr("Enter overlay text:"), QLineEdit::Normal, "", &ok);
    if (!ok || overlayText.isEmpty()) {
        return;
    }

    int x = QInputDialog::getInt(this, tr("Add Overlay to Video"), tr("X position:"), 0, 0, INT_MAX, 1);
    int y = QInputDialog::getInt(this, tr("Add Overlay to Video"), tr("Y position:"), 0, 0, INT_MAX, 1);

    QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Video with Overlay"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (outputVideo.isEmpty()) {
        return;
    }

    ffmpegHandler->addTextToVideo(currentVideo, outputVideo, overlayText, x, y);
}
