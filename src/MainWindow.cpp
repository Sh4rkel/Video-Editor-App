#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QProcess>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , currentVideo("")
{
    ui->setupUi(this);
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
        QMessageBox::critical(this, "Error", "Unsupported output format.");
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
        QMessageBox::critical(this, "Error", "Failed to start ffmpeg process.");
        return;
    }

    if (!ffmpeg.waitForFinished()) {
        QMessageBox::critical(this, "Error", "Failed to finish ffmpeg process.");
        return;
    }

//    QByteArray errorOutput = ffmpeg.readAllStandardError();
//    if (!errorOutput.isEmpty()) {
//        qDebug() << "FFmpeg error output:" << errorOutput;
//        QMessageBox::warning(this, "Warning", "There were some issues during conversion. Check the log for details.");
//    }

    if (!QFile::exists(outputFilePath)) {
        QMessageBox::critical(this, "Error", "Output file was not created.");
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

    QStringList formats;
    formats << "mp4" << "avi" << "mkv" << "mov";
    bool ok;
    QString format = QInputDialog::getItem(this, tr("Select Output Format"), tr("Format:"), formats, 0, false, &ok);
    if (ok && !format.isEmpty()) {
        convertVideoFormat(currentVideo, outputVideo, format);
    }
}

void MainWindow::cutVideo()
{
    // Implementation for cutting video
}

void MainWindow::addTextToVideo()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Text"), tr("Text to overlay:"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        ui->videoPlayerWidget->addTextOverlay(text);
        ui->videoPlayerWidget->update();
    }
}

void MainWindow::combineVideos()
{
    // Implementation for combining videos
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

void MainWindow::stopVideo()
{
    ui->videoPlayerWidget->getMediaPlayer()->stop();
}