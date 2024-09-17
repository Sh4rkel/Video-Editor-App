#include "FFmpegHandler.h"
#include <QProcess>

// Constructor
FFmpegHandler::FFmpegHandler(QObject *parent) : QObject(parent) {
    worker = new FFmpegWorker();
    worker->moveToThread(&workerThread);

    // Connect signals and slots for worker thread
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(worker, &FFmpegWorker::finished, this, &FFmpegHandler::handleWorkerFinished);
    connect(worker, &FFmpegWorker::errorOccurred, this, &FFmpegHandler::handleWorkerError);

    // Start worker thread
    workerThread.start();
}

// Destructor
FFmpegHandler::~FFmpegHandler() {
    workerThread.quit();
    workerThread.wait();
}

// Apply filters to video
void FFmpegHandler::applyFilters(const QString &inputVideo, const QString &outputVideo, FilterSettings::FilterType filter) {
    QStringList arguments;
    arguments << "-i" << inputVideo;

    // Add filter arguments based on filter type
    switch (filter) {
        case FilterSettings::Grayscale:
            arguments << "-vf" << "hue=s=0";
            break;
        case FilterSettings::Sepia:
            arguments << "-vf" << "colorchannelmixer=.393:.769:.189:0:.349:.686:.168:0:.272:.534:.131";
            break;
        case FilterSettings::Invert:
            arguments << "-vf" << "negate";
            break;
    }

    arguments << outputVideo;
    executeFFmpegCommand(arguments);
}

// Execute FFmpeg command
void FFmpegHandler::executeFFmpegCommand(const QStringList &arguments) {
    QProcess process;
    process.start("ffmpeg", arguments);

    // Wait for process to start
    if (!process.waitForStarted()) {
        return;
    }

    // Wait for process to finish
    if (!process.waitForFinished()) {
        return;
    }

    // Check process exit status
    if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
        return;
    }
}

// Convert video format
void FFmpegHandler::convertVideoFormat(const QString &inputVideo, const QString &outputVideo, const QString &format) {
    QStringList arguments;
    arguments << "-i" << inputVideo << outputVideo + "." + format;
    executeFFmpegCommand(arguments);
}

// Cut video segment
void FFmpegHandler::cutVideoSegment(const QString &inputVideo, const QString &outputVideo, qint64 start, qint64 end) {
    QStringList arguments;
    arguments << "-i" << inputVideo
              << "-ss" << QString::number(start / 1000.0)
              << "-to" << QString::number(end / 1000.0)
              << "-c" << "copy" << outputVideo;
    executeFFmpegCommand(arguments);
    simulateProgress();
}

// Combine two videos
void FFmpegHandler::combineVideos(const QString &videoFile1, const QString &videoFile2, const QString &outputVideo) {
    QStringList arguments;
    arguments << "-i" << videoFile1
              << "-i" << videoFile2
              << "-filter_complex" << "[0:v][1:v]concat=n=2:v=1[outv];[0:a][1:a]concat=n=2:v=0:a=1[outa]"
              << "-map" << "[outv]"
              << "-map" << "[outa]"
              << outputVideo;
    executeFFmpegCommand(arguments);
    simulateProgress();
}

// Add text to video
void FFmpegHandler::addTextToVideo(const QString &inputVideo, const QString &outputVideo, const QString &text, int x, int y) {
    QStringList arguments;
    arguments << "-i" << inputVideo
              << "-vf" << QString("drawtext=text='%1':x=%2:y=%3").arg(text).arg(x).arg(y)
              << outputVideo;
    executeFFmpegCommand(arguments);
    simulateProgress();
}

// Add overlay to video
void FFmpegHandler::addOverlayToVideo(const QString &inputVideo, const QString &outputVideo, const QString &overlayImage, int x, int y) {
    QStringList arguments;
    arguments << "-i" << inputVideo
              << "-i" << overlayImage
              << "-filter_complex" << QString("overlay=%1:%2").arg(x).arg(y)
              << outputVideo;
    executeFFmpegCommand(arguments);
    simulateProgress();
}

// Simulate progress for long-running operations
void FFmpegHandler::simulateProgress() {
    for (int i = 0; i <= 100; ++i) {
        QThread::msleep(50);
        emit progressUpdated(i);
    }
}

// Handle worker finished signal
void FFmpegHandler::handleWorkerFinished() {
    emit commandFinished();
}

// Handle worker error signal
void FFmpegHandler::handleWorkerError(const QString &error) {
    emit commandError(error);
}