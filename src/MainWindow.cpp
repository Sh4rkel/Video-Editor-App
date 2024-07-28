#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QProcess>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QStandardPaths>
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , currentVideo("")
{
    ui->setupUi(this);
    connect(ui->timelineWidget, &TimelineWidget::speedChanged, ui->videoPlayerWidget, &VideoPlayerWidget::setPlaybackRate);
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveFile);
    connect(ui->cutButton, &QPushButton::clicked, this, &MainWindow::cutVideo);
    connect(ui->addTextButton, &QPushButton::clicked, this, &MainWindow::addTextToVideo);
    connect(ui->combineButton, &QPushButton::clicked, this, &MainWindow::combineVideos);
    connect(ui->timelineWidget, &TimelineWidget::positionChanged, ui->videoPlayerWidget, &VideoPlayerWidget::seek);
    connect(ui->timelineWidget, &TimelineWidget::playPauseClicked, this, &MainWindow::togglePlayPause);
    connect(ui->videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::durationChanged, ui->timelineWidget, &TimelineWidget::setDuration);
    connect(ui->videoPlayerWidget->getMediaPlayer(), &QMediaPlayer::positionChanged, ui->timelineWidget, &TimelineWidget::setPosition);
    ui->videoPlayerWidget->show();
}

void MainWindow::convertVideoFormat(const QString &inputVideo, QString &outputVideo, const QString &format)
{
    QProcess ffmpeg;
    QStringList arguments;

    if (!outputVideo.endsWith("." + format)) {
        int lastDotIndex = outputVideo.lastIndexOf(".");
        if (lastDotIndex != -1) {
            outputVideo = outputVideo.left(lastDotIndex);
        }
        outputVideo += "." + format;
    }

    QString outputFilePath = outputVideo;
    if (!outputFilePath.endsWith("." + format)) {
        outputFilePath += "." + format;
    }

    QString videoCodec, audioCodec;
    std::map<QString, std::pair<QString, QString>> formatMap = {
            {"mp4", {"libx264", "aac"}},
            {"avi", {"libxvid", "libmp3lame"}},
            {"mkv", {"libvpx", "libvorbis"}},
            {"mov", {"prores", "pcm_s16le"}}
    };

    auto it = formatMap.find(format);
    if (it != formatMap.end()) {
        videoCodec = it->second.first;
        audioCodec = it->second.second;
    } else {
        return;
    }

    arguments << "-y"
              << "-i" << inputVideo
              << "-c:v" << videoCodec
              << "-preset" << "medium"
              << "-crf" << "23"
              << "-c:a" << audioCodec
              << "-b:a" << "192k"
              << outputFilePath;

    ffmpeg.start("ffmpeg", arguments);

    if (!ffmpeg.waitForStarted()) {
        return;
    }

    if (!ffmpeg.waitForFinished()) {
        return;
    }

//    QByteArray errorOutput = ffmpeg.readAllStandardError();
//    if (!errorOutput.isEmpty()) {
//        qDebug() << "FFmpeg error output:" << errorOutput;
//        QMessageBox::warning(this, "Warning", "There were some issues during conversion. Check the log for details.");
//    }

    if (!QFile::exists(outputFilePath)) {
        return;
    }

    QMessageBox::information(this, "Success", "Video converted successfully.");
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destroyed";
    delete ui;
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (!fileName.isEmpty()) {
        ui->videoPlayerWidget->loadVideo(fileName);
        currentVideo = fileName;
    }
}

void MainWindow::saveFile()
{
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

    convertVideoFormat(currentVideo, outputVideo, format);
}

void MainWindow::cutVideo()
{
    qint64 position = ui->videoPlayerWidget->getMediaPlayer()->position();
    if (cutStart == -1) {
        cutStart = position;
        QMessageBox::information(this, "Cut Video", "Start point set. Please set the end point.");
    } else if (cutEnd == -1) {
        cutEnd = position;
        QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Video Segment"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
        if (!outputVideo.isEmpty()) {
            cutVideoSegment(currentVideo, outputVideo, cutStart, cutEnd);
            cutStart = -1;
            cutEnd = -1;
        }
    }
}

void MainWindow::cutVideoSegment(const QString &inputVideo, const QString &outputVideo, qint64 start, qint64 end)
{
    QProcess ffmpeg;
    QStringList arguments;
    arguments << "-i" << inputVideo
              << "-ss" << QString::number(start / 1000.0)
              << "-to" << QString::number(end / 1000.0)
              << "-c" << "copy"
              << outputVideo;

    ffmpeg.start("ffmpeg", arguments);

    if (!ffmpeg.waitForStarted()) {
        return;
    }

    if (!ffmpeg.waitForFinished()) {
        return;
    }

    if (!QFile::exists(outputVideo)) {
        return;
    }

    QMessageBox::information(this, "Success", "Video segment cut successfully.");
}

void MainWindow::addTextToVideo()
{
    QString videoFile = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));

    QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Video With Text Overlay"), "", tr("Video Files (*.mp4)"));

    if (!outputVideo.endsWith(".mp4")) {
        outputVideo += ".mp4";
    }

    QFile inputFile("C:/books/C programming/project-cpp/Files/input.txt");
    if (!inputFile.open(QIODevice::ReadOnly)) {
        return;
    }
    QTextStream in(&inputFile);
    QString text = in.readAll();
    inputFile.close();

    // Escape special characters in the text
    text.replace("'", "'\\''");

    ffmpeg.start("ffmpeg", ffmpegCommand);

    if (!ffmpeg.waitForStarted()) {
        return;
    }

    if (!ffmpeg.waitForFinished()) {
        return;
    }

    QByteArray errorOutput = ffmpeg.readAllStandardError();
    if (!errorOutput.isEmpty()) {
        qDebug() << "FFmpeg error output:" << errorOutput;
    }

    if (!QFile::exists(outputVideo)) {
        return;
    }

    QMessageBox::information(this, "Success", "Video with text overlay created successfully.");
}

void MainWindow::combineVideos()
{
    QString videoFile1 = QFileDialog::getOpenFileName(this, tr("Open First Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    QString videoFile2 = QFileDialog::getOpenFileName(this, tr("Open Second Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));

    if (!QFile::exists(videoFile1) || !QFile::exists(videoFile2)) {
        return;
    }

    QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Combined Video"), "", tr("Video Files (*.mp4)"));
    if (outputVideo.isEmpty()) {
        return;
    }

    if (!outputVideo.endsWith(".mp4")) {
        outputVideo += ".mp4";
    }

    QProcess ffmpeg;
    ffmpeg.start("ffmpeg", QStringList() << "-i" << videoFile1 << "-c" << "copy" << "-bsf:v" << "h264_mp4toannexb" << "-f" << "mpegts" << "part1.ts");
    ffmpeg.waitForFinished();
    ffmpeg.start("ffmpeg", QStringList() << "-i" << videoFile2 << "-c" << "copy" << "-bsf:v" << "h264_mp4toannexb" << "-f" << "mpegts" << "part2.ts");
    ffmpeg.waitForFinished();

    ffmpeg.start("ffmpeg", QStringList() << "-i" << "parts.ts" << "-c" << "copy" << "-bsf:a" << "aac_adtstoasc" << outputVideo);
    ffmpeg.waitForFinished();
}

void MainWindow::togglePlayPause()
{
    QMediaPlayer::MediaStatus status = ui->videoPlayerWidget->getMediaPlayer()->mediaStatus();
    if (status == QMediaPlayer::LoadedMedia || status == QMediaPlayer::BufferedMedia) {
        ui->videoPlayerWidget->getMediaPlayer()->pause();
    } else {
        ui->videoPlayerWidget->getMediaPlayer()->play();
    }
}
