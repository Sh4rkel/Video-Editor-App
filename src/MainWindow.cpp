#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "VideoFrameWidget.h"
#include "GradientPalette.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QDockWidget>
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
    ui(std::make_unique<Ui::MainWindow>()),
    ffmpegHandler(std::make_unique<FFmpegHandler>(this)),
    videoPlayerWidget(std::make_unique<VideoPlayerWidget>(this)),
    timelineWidget(std::make_unique<TimelineWidget>(this)),
    speedDialog(std::make_unique<SpeedDialog>(this)),
    speedWidget(std::make_unique<SpeedWidget>(this)),
    fileHandler(std::make_unique<FileHandler>(this)),
    settingsDialog(std::make_unique<SettingsDialog>(this)),
    darkModeEnabled(true),
    currentVideo("")
{
    ui->setupUi(this);

    if (videoPlayerWidget && timelineWidget && fileHandler) {
        applyModernStyle();
        // applyShadows();
        // applyBorders();
        // applyGradientTheme();
        // applyCustomGradientTheme();
        // Set initial window size
        resize(1920, 1080);

        // Set size policies for widgets
        videoPlayerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        timelineWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        fileHandler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // Main layout
        QVBoxLayout *mainLayout = new QVBoxLayout();
        mainLayout->addWidget(videoPlayerWidget.get(), 3);
        mainLayout->addWidget(timelineWidget.get(), 1);
        mainLayout->addWidget(fileHandler.get(), 2);

        // Splitter for vertical layout
        QSplitter *splitter = new QSplitter(Qt::Vertical, this);
        splitter->addWidget(videoPlayerWidget.get());
        splitter->addWidget(timelineWidget.get());
        splitter->addWidget(fileHandler.get());

        // Central widget
        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(mainLayout);
        setCentralWidget(centralWidget);

        // Control layout
        QHBoxLayout *controlLayout = new QHBoxLayout();
        controlLayout->addWidget(speedWidget.get(), 1);
        controlLayout->addWidget(timelineWidget.get(), 9);
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
        connect(timelineWidget.get(), &TimelineWidget::positionChanged, videoPlayerWidget.get(), &VideoPlayerWidget::seek);
        connect(timelineWidget.get(), &TimelineWidget::playPauseClicked, this, &MainWindow::togglePlayPause);
        connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::durationChanged, timelineWidget.get(), &TimelineWidget::setDuration);
        connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::positionChanged, timelineWidget.get(), &TimelineWidget::setPosition);
        connect(videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);
        connect(speedWidget.get(), &SpeedWidget::speedChanged, videoPlayerWidget.get(), &VideoPlayerWidget::setSpeed);

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

        connect(fileHandler.get(), &FileHandler::fileSelected, this, &MainWindow::handleFileSelected);

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

        // Add a QDockWidget for additional controls
        QDockWidget *dockWidget = new QDockWidget(tr("Controls"), this);
        QWidget *dockContent = new QWidget(dockWidget);
        QVBoxLayout *dockLayout = new QVBoxLayout(dockContent);

        QPushButton *addTextButton = new QPushButton(tr("Add Text Overlay"), dockContent);
        connect(addTextButton, &QPushButton::clicked, this, &MainWindow::addTextOverlay);
        dockLayout->addWidget(addTextButton);

        dockContent->setLayout(dockLayout);
        dockWidget->setWidget(dockContent);
        addDockWidget(Qt::RightDockWidgetArea, dockWidget);

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
}

// Destructor
MainWindow::~MainWindow() {
}

void MainWindow::applyGradientThemeFromPalette(const QList<QColor> &colors) {
    QString gradient = GradientPalette::createGradientFromPalette(colors);
    QString styleSheet = QString(R"(
    QMainWindow {
        background: %1;
    }
    QMenuBar {
        background: %1;
        color: #FFFFFF;
    }
    QMenuBar::item {
        background: transparent;
        color: #FFFFFF;
    }
    QMenuBar::item:selected {
        background: %1;
    }
    QToolBar {
        background: %1;
        border: none;
    }
    QPushButton {
        background: %1;
        color: white;
        border-radius: 5px;
        padding: 10px;
    }
    QPushButton:hover {
        background: %1;
    }
    QSlider::groove:horizontal {
        height: 8px;
        background: #ddd;
    }
    QSlider::handle:horizontal {
        background: %1;
        width: 20px;
    }
    )").arg(gradient);
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::applyCustomGradientTheme() {
    QList<QColor> colors = { QColor("#FF5733"), QColor("#FFC300"), QColor("#C70039") };
    applyGradientThemeFromPalette(colors);
}

void MainWindow::applyGradientTheme() {
    QString styleSheet = R"(
    QMainWindow {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FF5733, stop:1 #C70039);
    }
    QMenuBar {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFC300, stop:1 #FF5733);
        color: #FFFFFF;
    }
    QMenuBar::item {
        background: transparent;
        color: #FFFFFF;
    }
    QMenuBar::item:selected {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FF5733, stop:1 #C70039);
    }
    QToolBar {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FFC300, stop:1 #FF5733);
        border: none;
    }
    QPushButton {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FF5733, stop:1 #C70039);
        color: white;
        border-radius: 5px;
        padding: 10px;
    }
    QPushButton:hover {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #C70039, stop:1 #900C3F);
    }
    QSlider::groove:horizontal {
        height: 8px;
        background: #ddd;
    }
    QSlider::handle:horizontal {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #FF5733, stop:1 #C70039);
        width: 20px;
    }
    )";
    qApp->setStyleSheet(styleSheet);
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
    if (!settingsDialog) {
        settingsDialog = std::make_unique<SettingsDialog>(this);
    }
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
    QMainWindow {
        background-color: #FFFFFF;
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
        background-color: #D3D3D3;
    }
    QToolBar {
        background-color: #F0F0F0;
        border: none;
    }
    QPushButton {
        background-color: #ADD8E6;
        color: black;
        border-radius: 5px;
        padding: 10px;
    }
    QPushButton:hover {
        background-color: #87CEEB;
    }
    QSlider::groove:horizontal {
        height: 8px;
        background: #ddd;
    }
    QSlider::handle:horizontal {
        background: #ADD8E6;
        width: 20px;
    }
    )";
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::applyBorders() {
    QString styleSheet = R"(
    QPushButton {
        border: 2px solid #4CAF50;
        border-radius: 5px;
        padding: 10px;
    }
    QPushButton:hover {
        border: 2px solid #45A049;
    }
    QSlider::groove:horizontal {
        border: 1px solid #999999;
        height: 8px;
        background: #ddd;
    }
    QSlider::handle:horizontal {
        border: 1px solid #4CAF50;
        width: 20px;
    }
    QMenuBar {
        border: 1px solid #CCCCCC;
        background-color: #F0F0F0;
        color: #000000;
    }
    QMenuBar::item {
        border: 1px solid #CCCCCC;
        background-color: #F0F0F0;
        color: #000000;
    }
    QMenuBar::item:selected {
        border: 1px solid #AAAAAA;
        background-color: #D3D3D3;
    }
    QToolBar {
        border: 1px solid #CCCCCC;
        background-color: #F0F0F0;
    }
    QGraphicsView {
        border: 2px solid #4CAF50;
    }
    )";
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::applyButtonBorders() {
    QString styleSheet = R"(
    QPushButton {
        border: 2px solid #4CAF50;
        border-radius: 5px;
        padding: 10px;
    }
    QPushButton:hover {
        border: 2px solid #45A049;
    }
    )";
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::applySliderBorders() {
    QString styleSheet = R"(
    QSlider::groove:horizontal {
        border: 1px solid #999999;
        height: 8px;
        background: #ddd;
    }
    QSlider::handle:horizontal {
        border: 1px solid #4CAF50;
        width: 20px;
    }
    )";
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::applyMenuBarBorders() {
    QString styleSheet = R"(
    QMenuBar {
        border: 1px solid #CCCCCC;
        background-color: #F0F0F0;
        color: #000000;
    }
    QMenuBar::item {
        border: 1px solid #CCCCCC;
        background-color: #F0F0F0;
        color: #000000;
    }
    QMenuBar::item:selected {
        border: 1px solid #AAAAAA;
        background-color: #D3D3D3;
    }
    )";
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::applyToolBarBorders() {
    QString styleSheet = R"(
    QToolBar {
        border: 1px solid #CCCCCC;
        background-color: #F0F0F0;
    }
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply dark theme
void MainWindow::applyDarkTheme() {
    QString styleSheet = R"(
    QMainWindow {
        background-color: #2E2E2E;
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
    QToolBar {
        background-color: #3E3E3E;
        border: none;
    }
    QPushButton {
        background-color: #4CAF50;
        color: white;
        border-radius: 5px;
        padding: 10px;
    }
    QPushButton:hover {
        background-color: #45A049;
    }
    QSlider::groove:horizontal {
        height: 8px;
        background: #ddd;
    }
    QSlider::handle:horizontal {
        background: #4CAF50;
        width: 20px;
    }
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply purple theme
void MainWindow::applyPurpleNouncesTheme() {
    QString styleSheet = R"(
    QMainWindow {
        background-color: #4B0082;
    }
    QMenuBar {
        background-color: #6A0DAD;
        color: #FFFFFF;
    }
    QMenuBar::item {
        background-color: #6A0DAD;
        color: #FFFFFF;
    }
    QMenuBar::item:selected {
        background-color: #8A2BE2;
    }
    QToolBar {
        background-color: #6A0DAD;
        border: none;
    }
    QPushButton {
        background-color: #9370DB;
        color: white;
        border-radius: 5px;
        padding: 10px;
    }
    QPushButton:hover {
        background-color: #7B68EE;
    }
    QSlider::groove:horizontal {
        height: 8px;
        background: #ddd;
    }
    QSlider::handle:horizontal {
        background: #9370DB;
        width: 20px;
    }
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply green theme
void MainWindow::applyGreenTheme() {
    QString styleSheet = R"(
    QMainWindow {
        background-color: #2E8B57;
    }
    QMenuBar {
        background-color: #3CB371;
        color: #FFFFFF;
    }
    QMenuBar::item {
        background-color: #3CB371;
        color: #FFFFFF;
    }
    QMenuBar::item:selected {
        background-color: #66CDAA;
    }
    QToolBar {
        background-color: #3CB371;
        border: none;
    }
    QPushButton {
        background-color: #8FBC8F;
        color: white;
        border-radius: 5px;
        padding: 10px;
    }
    QPushButton:hover {
        background-color: #7FFF00;
    }
    QSlider::groove:horizontal {
        height: 8px;
        background: #ddd;
    }
    QSlider::handle:horizontal {
        background: #8FBC8F;
        width: 20px;
    }
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply blue theme
void MainWindow::applyBlueTheme() {
    QString styleSheet = R"(
    QMainWindow {
        background-color: #1E90FF;
    }
    QMenuBar {
        background-color: #4682B4;
        color: #FFFFFF;
    }
    QMenuBar::item {
        background-color: #4682B4;
        color: #FFFFFF;
    }
    QMenuBar::item:selected {
        background-color: #5F9EA0;
    }
    QToolBar {
        background-color: #4682B4;
        border: none;
    }
    QPushButton {
        background-color: #87CEFA;
        color: white;
        border-radius: 5px;
        padding: 10px;
    }
    QPushButton:hover {
        background-color: #00BFFF;
    }
    QSlider::groove:horizontal {
        height: 8px;
        background: #ddd;
    }
    QSlider::handle:horizontal {
        background: #87CEFA;
        width: 20px;
    }
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply custom style
void MainWindow::applyCustomStyle() {
    QString styleSheet = R"(
    QMainWindow {
        background-color: #FFFFFF;
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
        background-color: #D3D3D3;
    }
    QToolBar {
        background-color: #F0F0F0;
        border: none;
    }
    QPushButton {
        background-color: #ADD8E6;
        color: black;
        border-radius: 5px;
        padding: 10px;
    }
    QPushButton:hover {
        background-color: #87CEEB;
    }
    QSlider::groove:horizontal {
        height: 8px;
        background: #ddd;
    }
    QSlider::handle:horizontal {
        background: #ADD8E6;
        width: 20px;
    }
    )";
    qApp->setStyleSheet(styleSheet);
}

// Apply modern style
void MainWindow::applyModernStyle() {
    static bool styleApplied = false;
    if (styleApplied) return;

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
        background-color: transparent;
        color: #FFFFFF;
    }
    QMenuBar::item:selected {
        background-color: #5E5E5E;
    }
    QToolBar {
        background-color: #3E3E3E;
        border: none;
    }
    QPushButton {
        background-color: #5E5E5E;
        color: white;
        border-radius: 5px;
        padding: 10px;
    }
    QPushButton:hover {
        background-color: #7E7E7E;
    }
    QSlider::groove:horizontal {
        height: 8px;
        background: #ddd;
    }
    QSlider::handle:horizontal {
        background: #5E5E5E;
        width: 20px;
    }
    QProgressBar {
        background-color: #3E3E3E;
        border: 1px solid #5E5E5E;
        border-radius: 5px;
        text-align: center;
        color: white;
    }
    QProgressBar::chunk {
        background-color: #5E5E5E;
    }
    )";
    qApp->setStyleSheet(styleSheet);
    styleApplied = true;
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
    auto addShadow = [](QWidget *widget) {
        if (!widget) return;
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(10);
        shadow->setOffset(2, 2);
        widget->setGraphicsEffect(shadow);
    };

    addShadow(videoPlayerWidget.get());
    addShadow(timelineWidget.get());
    addShadow(speedWidget.get());
    addShadow(progressBar);
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

    timelineWidget->addTextOverlay(text, QPointF(x, y), font, color);
}