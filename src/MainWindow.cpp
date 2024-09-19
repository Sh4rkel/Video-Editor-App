#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "VideoFrameWidget.h"
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
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QImageReader>
#include <QFontDialog>
#include <QColorDialog>

// Constructor
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
    currentVideo(""),
    settingsDialog(new SettingsDialog(this))
{
    ui->setupUi(this);

    // Set initial window size
    resize(1280, 720);

    // Set size policies for widgets
    videoPlayerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    timelineWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    fileHandler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(videoPlayerWidget, 3);
    mainLayout->addWidget(timelineWidget, 1);
    mainLayout->addWidget(fileHandler, 2);

    // Splitter for vertical layout
    QSplitter *splitter = new QSplitter(Qt::Vertical, this);
    splitter->addWidget(videoPlayerWidget);
    splitter->addWidget(timelineWidget);
    splitter->addWidget(fileHandler);

    // Central widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Control layout
    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->addWidget(speedWidget, 1);
    controlLayout->addWidget(timelineWidget, 9);
    mainLayout->addLayout(controlLayout);

    // Progress bar
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    mainLayout->addWidget(progressBar);

    // Media player setup
    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    mainLayout->addWidget(videoWidget);
    mediaPlayer->setVideoOutput(videoWidget);

    // Connect signals and slots
    connect(timelineWidget, &TimelineWidget::positionChanged, videoPlayerWidget, &VideoPlayerWidget::seek);
    connect(timelineWidget, &TimelineWidget::playPauseClicked, this, &MainWindow::togglePlayPause);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::durationChanged, timelineWidget, &TimelineWidget::setDuration);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::positionChanged, timelineWidget, &TimelineWidget::setPosition);
    connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);
    connect(speedWidget, &SpeedWidget::speedChanged, videoPlayerWidget, &VideoPlayerWidget::setSpeed);

    // Menu bar setup
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Video menu
    videoMenu = new QMenu(tr("Video"), this);
    menuBar->addMenu(videoMenu);

    // Actions
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

    // Shortcuts
    QShortcut *cutShortcut = new QShortcut(QKeySequence("Ctrl+X"), this);
    connect(cutShortcut, &QShortcut::activated, this, &MainWindow::cutVideo);

    QShortcut *combineShortcut = new QShortcut(QKeySequence("Ctrl+M"), this);
    connect(combineShortcut, &QShortcut::activated, this, &MainWindow::combineVideos);

    QShortcut *addTextShortcut = new QShortcut(QKeySequence("Ctrl+T"), this);
    connect(addTextShortcut, &QShortcut::activated, this, &MainWindow::addTextOverlay);

    QShortcut *addOverlayShortcut = new QShortcut(QKeySequence("Ctrl+O"), this);
    connect(addOverlayShortcut, &QShortcut::activated, this, &MainWindow::addOverlayToVideo);

    QShortcut *addVideosShortcut = new QShortcut(QKeySequence("Ctrl+Shift+A"), this);
    connect(addVideosShortcut, &QShortcut::activated, this, &MainWindow::addVideosToTimeline);

    // Apply styles and shadows
    applyModernStyle();
    applyShadows();

    // Setup theme menu
    setupThemeMenu();

    // Settings menu
    settingsMenu = new QMenu(tr("Settings"), this);
    menuBar->addMenu(settingsMenu);

    QAction *settingsAction = new QAction(tr("Settings"), this);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::openSettings);
    settingsMenu->addAction(settingsAction);

    QAction *filterSettingsAction = new QAction(tr("Filter Settings"), this);
    connect(filterSettingsAction, &QAction::triggered, this, &MainWindow::openFilterSettings);
    videoMenu->addAction(filterSettingsAction);

}

// Destructor
MainWindow::~MainWindow() {
    delete ui;
    delete ffmpegHandler;
}

// Open file dialog
void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (!fileName.isEmpty()) {
        handleFileSelected(fileName);
    }
}

// Save file dialog
void MainWindow::saveFile() {
    if (currentVideo.isEmpty()) {
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

// Handle file selection
void MainWindow::handleFileSelected(const QString &filePath) {
    currentVideo = filePath;
    videoPlayerWidget->loadVideo(filePath);
    mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
    mediaPlayer->play();
}

// Open filter settings dialog
void MainWindow::openFilterSettings() {
    FilterSettings filterSettings(this);
    if (filterSettings.exec() == QDialog::Accepted) {
        applyFilter(filterSettings.getSelectedFilter());
    }
}

// Define the addOverlayToVideo function
void MainWindow::addOverlayToVideo() {
    QString inputVideo = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (inputVideo.isEmpty()) {
        return;
    }

    QString overlayImage = QFileDialog::getOpenFileName(this, tr("Open Overlay Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (overlayImage.isEmpty()) {
        return;
    }

    QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Output Video"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (outputVideo.isEmpty()) {
        return;
    }

    int x = QInputDialog::getInt(this, tr("Overlay Position"), tr("X position:"), 0, 0, INT_MAX, 1);
    int y = QInputDialog::getInt(this, tr("Overlay Position"), tr("Y position:"), 0, 0, INT_MAX, 1);

    ffmpegHandler->addOverlayToVideo(inputVideo, outputVideo, overlayImage, x, y);
}

// Apply filter to video
void MainWindow::applyFilter(const QString &filter) {
    if (currentVideo.isEmpty()) {
        return;
    }

    QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Filtered Video"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (outputVideo.isEmpty()) {
        return;
    }

    FilterSettings::FilterType filterType;
    if (filter == "Grayscale") {
        filterType = FilterSettings::Grayscale;
    } else if (filter == "Sepia") {
        filterType = FilterSettings::Sepia;
    } else {
        filterType = FilterSettings::Invert;
    }

    ffmpegHandler->applyFilters(currentVideo, outputVideo, filterType);
}

// Update progress bar
void MainWindow::updateProgressBar(qint64 value) {
    progressBar->setValue(value);
}

// Function to add videos to the timeline
void MainWindow::addVideosToTimeline() {
    // Implement the logic to add videos to the timeline
    // For example, you might open a file dialog to select videos and then add them to the timeline
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Add Videos to Timeline"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (!fileNames.isEmpty()) {
        // Add the selected videos to the timeline
        foreach (const QString &fileName, fileNames) {
            // Assuming you have a method in TimelineWidget to add videos
            timelineWidget->addVideo(fileName);
        }
    }
}

// Function to open settings dialog
void MainWindow::openSettings() {
    // Implement the logic to open the settings dialog
    // For example, you might create and show a settings dialog
    settingsDialog->exec();
}

// Cut video segment
void MainWindow::cutVideo() {
    if (currentVideo.isEmpty()) {
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

// Combine two videos
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

// Toggle play/pause
void MainWindow::togglePlayPause() {
    QMediaPlayer *player = videoPlayerWidget->getMediaPlayer();
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
    } else {
        player->play();
    }
}

// Handle media status change
void MainWindow::handleMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        videoPlayerWidget->getMediaPlayer()->stop();
    }
}

// Add text to video
void MainWindow::addTextToVideo() {
    if (currentVideo.isEmpty()) {
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

// Apply light theme
void MainWindow::applyLightTheme() {
    QString styleSheet = R"(
    /* Light theme styles */
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply dark theme
void MainWindow::applyDarkTheme() {
    QString styleSheet = R"(
    /* Dark theme styles */
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply purple theme
void MainWindow::applyPurpleNouncesTheme() {
    QString styleSheet = R"(
    /* Purple theme styles */
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply green theme
void MainWindow::applyGreenTheme() {
    QString styleSheet = R"(
    /* Green theme styles */
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply blue theme
void MainWindow::applyBlueTheme() {
    QString styleSheet = R"(
    /* Blue theme styles */
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply custom style
void MainWindow::applyCustomStyle() {
    QString styleSheet = R"(
    /* Custom styles */
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply modern style
void MainWindow::applyModernStyle() {
    QString styleSheet = R"(
    /* Modern styles */
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply smooth transition animation
void MainWindow::applySmoothTransition(QWidget *widget, const QRect &startRect, const QRect &endRect) {
    QPropertyAnimation *animation = new QPropertyAnimation(widget, "geometry");
    animation->setDuration(500);
    animation->setStartValue(startRect);
    animation->setEndValue(endRect);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

// Apply shadows to widgets
void MainWindow::applyShadows() {
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(2, 2);
    shadowEffect->setColor(Qt::black);

    videoPlayerWidget->setGraphicsEffect(shadowEffect);
    timelineWidget->setGraphicsEffect(shadowEffect);
    speedWidget->setGraphicsEffect(shadowEffect);
    progressBar->setGraphicsEffect(shadowEffect);
}

// Setup theme menu
void MainWindow::setupThemeMenu() {
    themeMenu = menuBar->addMenu(tr("&Theme"));

    QAction *lightThemeAction = new QAction(tr("Light Theme"), this);
    connect(lightThemeAction, &QAction::triggered, this, &MainWindow::applyLightTheme);
    themeMenu->addAction(lightThemeAction);

    QAction *darkThemeAction = new QAction(tr("Dark Theme"), this);
    connect(darkThemeAction, &QAction::triggered, this, &MainWindow::applyDarkTheme);
    themeMenu->addAction(darkThemeAction);

    QAction *purpleNouncesThemeAction = new QAction(tr("Purple Theme"), this);
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

// Add overlay to video
void MainWindow::addTextOverlay() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Text Overlay"), tr("Enter text:"), QLineEdit::Normal, "", &ok);
    if (!ok || text.isEmpty()) {
        return;
    }

    int x = QInputDialog::getInt(this, tr("Add Text Overlay"), tr("X position:"), 0, 0, INT_MAX, 1, &ok);
    if (!ok) return;
    int y = QInputDialog::getInt(this, tr("Add Text Overlay"), tr("Y position:"), 0, 0, INT_MAX, 1, &ok);
    if (!ok) return;

    QFont font = QFontDialog::getFont(&ok, QFont("Arial", 24), this);
    if (!ok) return;

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Select Text Color"));
    if (!color.isValid()) return;

    // Assuming you have a method in TimelineWidget to add text overlay
    timelineWidget->addTextOverlay(text, QPointF(x, y), font, color);
}