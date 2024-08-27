#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QMediaPlayer>
#include "filehandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ffmpegHandler(new FFmpegHandler(this)),
    videoPlayerWidget(new VideoPlayerWidget(this)),
    timelineWidget(new TimelineWidget(this)),
    speedDialog(new SpeedDialog(this)),
    speedWidget(new SpeedWidget(this)),
    fileHandler(new FileHandler(this)),
    darkModeEnabled(true)
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

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->addWidget(speedWidget);
    controlLayout->addWidget(timelineWidget);

    mainLayout->addLayout(controlLayout);

    connect(timelineWidget, &TimelineWidget::positionChanged, videoPlayerWidget, &VideoPlayerWidget::seek);
    connect(timelineWidget, &TimelineWidget::playPauseClicked, this, &MainWindow::togglePlayPause);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::durationChanged, timelineWidget, &TimelineWidget::setDuration);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::positionChanged, timelineWidget, &TimelineWidget::setPosition);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);

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

    toggleThemeAction = new QAction(tr("&Toggle Theme"), this);
    connect(toggleThemeAction, &QAction::triggered, this, &MainWindow::toggleTheme);

    themeMenu = menuBar->addMenu(tr("&Theme"));
    themeMenu->addAction(toggleThemeAction);
    toggleTheme();

    speedAction = new QAction(tr("Speed"), this);
    connect(speedAction, &QAction::triggered, this, &MainWindow::showSpeedDialog);
    videoMenu->addAction(speedAction);

    connect(fileHandler, &FileHandler::fileSelected, this, &MainWindow::handleFileSelected);
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
        videoPlayerWidget->loadVideo(fileName);
        currentVideo = fileName;
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

void MainWindow::toggleTheme() {
    darkModeEnabled = !darkModeEnabled;
    QString styleSheet;
    if (darkModeEnabled) {
        styleSheet = R"(
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
    } else {
        styleSheet = R"(
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
    }
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::showSpeedDialog() {
    speedDialog->exec();
}