#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), ffmpegHandler(new FFmpegHandler(this)), currentVideo("") {
    ui->setupUi(this);
    connect(ui->timelineWidget, &TimelineWidget::positionChanged, ui->videoPlayerWidget, &VideoPlayerWidget::seek);
    connect(ui->timelineWidget, &TimelineWidget::playPauseClicked, this, &MainWindow::togglePlayPause);
    connect(ui->videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::durationChanged, ui->timelineWidget, &TimelineWidget::setDuration);
    connect(ui->videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::positionChanged, ui->timelineWidget, &TimelineWidget::setPosition);
    ui->videoPlayerWidget->show();

    // Connect menu actions to slots
    connect(ui->openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->cutAction, &QAction::triggered, this, &MainWindow::cutVideo);
    connect(ui->combineAction, &QAction::triggered, this, &MainWindow::combineVideos);
}

MainWindow::~MainWindow() {
    delete ui;
    delete ffmpegHandler;
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (!fileName.isEmpty()) {
        ui->videoPlayerWidget->loadVideo(fileName);
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

void MainWindow::addTextToVideo() {
    if (currentVideo.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No video file is currently loaded.");
        return;
    }

    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Text to Video"), tr("Text:"), QLineEdit::Normal, "", &ok);
    if (!ok || text.isEmpty()) {
        return;
    }

    QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Video with Text"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (outputVideo.isEmpty()) {
        return;
    }

    ffmpegHandler->addTextToVideo(currentVideo, outputVideo, text);
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
    QMediaPlayer::MediaStatus status = ui->videoPlayerWidget->getMediaPlayer()->mediaStatus();
    if (status == QMediaPlayer::LoadedMedia || status == QMediaPlayer::BufferedMedia) {
        ui->videoPlayerWidget->getMediaPlayer()->pause();
    } else {
        ui->videoPlayerWidget->getMediaPlayer()->play();
    }
}