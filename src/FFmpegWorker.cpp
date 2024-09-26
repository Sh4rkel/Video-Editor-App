#include "FFmpegWorker.h"
#include <QThread>

FFmpegWorker::FFmpegWorker(QObject *parent) : QObject(parent) {}

void FFmpegWorker::setArguments(const QStringList &arguments) {
    this->arguments = arguments;
}

void FFmpegWorker::execute() {
    QProcess process;
    process.start("ffmpeg", arguments);
    if (!process.waitForStarted()) {
        emit errorOccurred(process.errorString());
        return;
    }

    if (!process.waitForFinished()) {
        emit errorOccurred(process.errorString());
        return;
    }

    if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
        emit errorOccurred(process.readAllStandardError());
        return;
    }

    emit finished();
}
