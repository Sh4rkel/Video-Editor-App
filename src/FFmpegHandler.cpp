#include "FFmpegHandler.h"

FFmpegHandler::FFmpegHandler(QObject *parent) : QObject(parent) {
    worker = new FFmpegWorker();
    worker->moveToThread(&workerThread);

    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(worker, &FFmpegWorker::finished, this, &FFmpegHandler::handleWorkerFinished);
    connect(worker, &FFmpegWorker::errorOccurred, this, &FFmpegHandler::handleWorkerError);

    workerThread.start();
}

FFmpegHandler::~FFmpegHandler() {
    workerThread.quit();
    workerThread.wait();
}

void FFmpegHandler::executeFFmpegCommand(const QStringList &arguments) {
    worker->setArguments(arguments);
    QMetaObject::invokeMethod(worker, "execute", Qt::QueuedConnection);
}

void FFmpegHandler::convertVideoFormat(const QString &inputVideo, const QString &outputVideo, const QString &format) {
    QStringList arguments;
    arguments << "-i" << inputVideo << outputVideo + "." + format;
    executeFFmpegCommand(arguments);
}

void FFmpegHandler::cutVideoSegment(const QString &inputVideo, const QString &outputVideo, qint64 start, qint64 end) {
    QStringList arguments;
    arguments << "-i" << inputVideo
              << "-ss" << QString::number(start / 1000.0)
              << "-to" << QString::number(end / 1000.0)
              << "-c" << "copy" << outputVideo;
    executeFFmpegCommand(arguments);
}

void FFmpegHandler::combineVideos(const QString &videoFile1, const QString &videoFile2, const QString &outputVideo) {
    QStringList arguments;
    arguments << "-i" << videoFile1
              << "-i" << videoFile2
              << "-filter_complex" << "[0:v][1:v]concat=n=2:v=1[outv];[0:a][1:a]concat=n=2:v=0:a=1[outa]"
              << "-map" << "[outv]"
              << "-map" << "[outa]"
              << outputVideo;
    executeFFmpegCommand(arguments);
}

void FFmpegHandler::addTextToVideo(const QString &inputVideo, const QString &outputVideo, const QString &text, int x, int y) {
    QStringList arguments;
    arguments << "-i" << inputVideo
              << "-vf" << QString("drawtext=text='%1':x=%2:y=%3").arg(text).arg(x).arg(y)
              << outputVideo;
    executeFFmpegCommand(arguments);
}

void FFmpegHandler::addOverlayToVideo(const QString &inputVideo, const QString &outputVideo, const QString &overlayImage, int x, int y) {
    QStringList arguments;
    arguments << "-i" << inputVideo
              << "-i" << overlayImage
              << "-filter_complex" << QString("overlay=%1:%2").arg(x).arg(y)
              << outputVideo;
    executeFFmpegCommand(arguments);
}

void FFmpegHandler::handleWorkerFinished() {
    emit commandFinished();
}

void FFmpegHandler::handleWorkerError(const QString &error) {
    emit commandError(error);
}