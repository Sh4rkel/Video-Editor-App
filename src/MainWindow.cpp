#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QMediaPlayer>
#include "filehandler.h"

#include "filehandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ffmpegHandler(new FFmpegHandler(this)),
    videoPlayerWidget(new VideoPlayerWidget(this)),
    timelineWidget(new TimelineWidget(this)),
    speedWidget(new SpeedWidget(this)),
    fileHandler(new FileHandler(this)), 
    darkModeEnabled(true)
{
    ui->setupUi(this);

    resize(1280, 720);

    videoPlayerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    timelineWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    speedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    fileHandler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(videoPlayerWidget, 3); 
    mainLayout->addWidget(timelineWidget, 1);
    mainLayout->addWidget(speedWidget, 1);
    mainLayout->addWidget(fileHandler, 2); 

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(timelineWidget, &TimelineWidget::positionChanged, videoPlayerWidget, &VideoPlayerWidget::seek);
    connect(timelineWidget, &TimelineWidget::playPauseClicked, this, &MainWindow::togglePlayPause);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::durationChanged, timelineWidget, &TimelineWidget::setDuration);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::positionChanged, timelineWidget, &TimelineWidget::setPosition);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);
    connect(speedWidget, &SpeedWidget::speedChanged, this, &MainWindow::changeSpeed);

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
    if (outputVideo.isEmpty()) {
        return;
    }

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
        timelineWidget->updatePlayPauseButtonText("▶️");
    } else {
        player->play();
        timelineWidget->updatePlayPauseButtonText("⏸️");
    }
}

void MainWindow::changeSpeed(qreal speed) {
    videoPlayerWidget->getMediaPlayer()->setPlaybackRate(speed);
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
                border-bottom: 1px solid #5E5E5E;
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
                border: 1px solid #5E5E5E;
            }
            QMenu::item:selected {
                background-color: #5E5E5E;
            }
            QPushButton {
                background-color: #4E4E4E;
                color: #FFFFFF;
                border: 1px solid #5E5E5E;
                border-radius: 5px;
                padding: 5px;
            }
            QPushButton:hover {
                background-color: #5E5E5E;
            }
            QPushButton:pressed {
                background-color: #3E3E3E;
            }
            QStatusBar {
                background-color: #3E3E3E;
                color: #FFFFFF;
                border-top: 1px solid #5E5E5E;
            }
            QSlider::groove:horizontal {
                border: 1px solid #5E5E5E;
                height: 8px;
                background: #3E3E3E;
                margin: 2px 0;
                border-radius: 4px;
            }
            QSlider::handle:horizontal {
                background: #5E5E5E;
                border: 1px solid #5E5E5E;
                width: 18px;
                margin: -2px 0;
                border-radius: 9px;
            }
            QSlider::handle:horizontal:hover {
                background: #7E7E7E;
            }
            QSlider::handle:horizontal:pressed {
                background: #3E3E3E;
            }
            QLabel {
                color: #FFFFFF;
            }
            QListWidget {
                background-color: #2E2E2E;
                color: #FFFFFF;
                border: 1px solid #5E5E5E;
            }
            QListWidget::item {
                background-color: #3E3E3E;
                color: #FFFFFF;
            }
            QListWidget::item:selected {
                background-color: #5E5E5E;
            }
            QLineEdit {
                background-color: #3E3E3E;
                color: #FFFFFF;
                border: 1px solid #5E5E5E;
                border-radius: 5px;
                padding: 5px;
            }
            QComboBox {
                background-color: #3E3E3E;
                color: #FFFFFF;
                border: 1px solid #5E5E5E;
                border-radius: 5px;
                padding: 5px;
            }
            QComboBox::drop-down {
                background-color: #4E4E4E;
            }
            QComboBox::down-arrow {
                image: url(:/icons/down_arrow.png);
            }
            QCheckBox {
                color: #FFFFFF;
            }
            QCheckBox::indicator {
                width: 20px;
                height: 20px;
            }
            QCheckBox::indicator:checked {
                image: url(:/icons/checkbox_checked.png);
            }
            QCheckBox::indicator:unchecked {
                image: url(:/icons/checkbox_unchecked.png);
            }
            QRadioButton {
                color: #FFFFFF;
            }
            QRadioButton::indicator {
                width: 20px;
                height: 20px;
            }
            QRadioButton::indicator:checked {
                image: url(:/icons/radiobutton_checked.png);
            }
            QRadioButton::indicator:unchecked {
                image: url(:/icons/radiobutton_unchecked.png);
            }
            QTabWidget::pane {
                border: 1px solid #5E5E5E;
                background: #3E3E3E;
            }
            QTabWidget::tab-bar {
                left: 5px;
            }
            QTabBar::tab {
                background: #4E4E4E;
                color: #FFFFFF;
                border: 1px solid #5E5E5E;
                border-radius: 5px;
                padding: 5px;
            }
            QTabBar::tab:selected {
                background: #5E5E5E;
            }
            QTabBar::tab:hover {
                background: #5E5E5E;
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
                border-bottom: 1px solid #C0C0C0;
            }
            QMenuBar::item {
                background-color: #F0F0F0;
                color: #000000;
            }
            QMenuBar::item:selected {
                background-color: #C0C0C0;
            }
            QMenu {
                background-color: #F0F0F0;
                color: #000000;
                border: 1px solid #C0C0C0;
            }
            QMenu::item:selected {
                background-color: #C0C0C0;
            }
            QPushButton {
                background-color: #E0E0E0;
                color: #000000;
                border: 1px solid #C0C0C0;
                border-radius: 5px;
                padding: 5px;
            }
            QPushButton:hover {
                background-color: #C0C0C0;
            }
            QPushButton:pressed {
                background-color: #A0A0A0;
            }
            QStatusBar {
                background-color: #F0F0F0;
                color: #000000;
                border-top: 1px solid #C0C0C0;
            }
            QSlider::groove:horizontal {
                border: 1px solid #C0C0C0;
                height: 8px;
                background: #F0F0F0;
                margin: 2px 0;
                border-radius: 4px;
            }
            QSlider::handle:horizontal {
                background: #C0C0C0;
                border: 1px solid #C0C0C0;
                width: 18px;
                margin: -2px 0;
                border-radius: 9px;
            }
            QSlider::handle:horizontal:hover {
                background: #A0A0A0;
            }
            QSlider::handle:horizontal:pressed {
                background: #808080;
            }
            QLabel {
                color: #000000;
            }
            QListWidget {
                background-color: #FFFFFF;
                color: #000000;
                border: 1px solid #C0C0C0;
            }
            QListWidget::item {
                background-color: #F0F0F0;
                color: #000000;
            }
            QListWidget::item:selected {
                background-color: #C0C0C0;
            }
            QLineEdit {
                background-color: #F0F0F0;
                color: #000000;
                border: 1px solid #C0C0C0;
                border-radius: 5px;
                padding: 5px;
            }
            QComboBox {
                background-color: #F0F0F0;
                color: #000000;
                border: 1px solid #C0C0C0;
                border-radius: 5px;
                padding: 5px;
            }
            QComboBox::drop-down {
                background-color: #E0E0E0;
            }
            QComboBox::down-arrow {
                image: url(:/icons/down_arrow.png);
            }
            QCheckBox {
                color: #000000;
            }
            QCheckBox::indicator {
                width: 20px;
                height: 20px;
            }
            QCheckBox::indicator:checked {
                image: url(:/icons/checkbox_checked.png);
            }
            QCheckBox::indicator:unchecked {
                image: url(:/icons/checkbox_unchecked.png);
            }
            QRadioButton {
                color: #000000;
            }
            QRadioButton::indicator {
                width: 20px;
                height: 20px;
            }
            QRadioButton::indicator:checked {
                image: url(:/icons/radiobutton_checked.png);
            }
            QRadioButton::indicator:unchecked {
                image: url(:/icons/radiobutton_unchecked.png);
            }
            QTabWidget::pane {
                border: 1px solid #C0C0C0;
                background: #F0F0F0;
            }
            QTabWidget::tab-bar {
                left: 5px;
            }
            QTabBar::tab {
                background: #E0E0E0;
                color: #000000;
                border: 1px solid #C0C0C0;
                border-radius: 5px;
                padding: 5px;
            }
            QTabBar::tab:selected {
                background: #C0C0C0;
            }
            QTabBar::tab:hover {
                background: #C0C0C0;
            }
        )";
    }
    qApp->setStyleSheet(styleSheet);
}
