#include "FFmpegHandler.h"
#include <QFile>
#include <QMessageBox>

FFmpegHandler::FFmpegHandler(QObject *parent) : QObject(parent), ffmpegPath("ffmpeg") {
    ffmpeg.setProgram(ffmpegPath);
}

void FFmpegHandler::convertVideoFormat(const QString &inputVideo, const QString &outputVideo, const QString &format) {
    QStringList arguments;
    QString output = outputVideo;
    if (!output.endsWith("." + format)) {
        int lastDotIndex = output.lastIndexOf(".");
        if (lastDotIndex != -1) {
            output = output.left(lastDotIndex);
        }
        output += "." + format;
    }

    QString videoCodec, audioCodec;
    std::map<QString, std::pair<QString, QString>> formatMap = {
        {"mp4", {"libx264", "aac"}},
        {"avi", {"libxvid", "mp3"}},
        {"mkv", {"libx264", "aac"}},
        {"mov", {"libx264", "aac"}}
    };

    auto it = formatMap.find(format);
    if (it != formatMap.end()) {
        videoCodec = it->second.first;
        audioCodec = it->second.second;
    } else {
        QMessageBox::warning(nullptr, "Error", "Unsupported format.");
        return;
    }

    arguments << "-y"
              << "-i" << inputVideo
              << "-c:v" << videoCodec
              << "-preset" << "medium"
              << "-crf" << "23"
              << "-c:a" << audioCodec
              << "-b:a" << "192k"
              << output;

    ffmpeg.setArguments(arguments);
    ffmpeg.start();

    if (!ffmpeg.waitForStarted()) {
        QMessageBox::warning(nullptr, "Error", "Failed to start FFmpeg.");
        return;
    }

    if (!ffmpeg.waitForFinished()) {
        QMessageBox::warning(nullptr, "Error", "FFmpeg process failed.");
        return;
    }

    if (!QFile::exists(output)) {
        QMessageBox::warning(nullptr, "Error", "Output video file was not created.");
        return;
    }

    QMessageBox::information(nullptr, "Success", "Video converted successfully.");
}

void FFmpegHandler::cutVideoSegment(const QString &inputVideo, const QString &outputVideo, qint64 start, qint64 end) {
    QStringList arguments;
    arguments << "-i" << inputVideo
              << "-ss" << QString::number(start / 1000.0)
              << "-to" << QString::number(end / 1000.0)
              << "-c" << "copy"
              << outputVideo;

    ffmpeg.setArguments(arguments);
    ffmpeg.start();

    if (!ffmpeg.waitForStarted()) {
        QMessageBox::warning(nullptr, "Error", "Failed to start FFmpeg.");
        return;
    }

    if (!ffmpeg.waitForFinished()) {
        QMessageBox::warning(nullptr, "Error", "FFmpeg process failed.");
        return;
    }

    if (!QFile::exists(outputVideo)) {
        QMessageBox::warning(nullptr, "Error", "Output video file was not created.");
        return;
    }

    QMessageBox::information(nullptr, "Success", "Video segment cut successfully.");
}

void FFmpegHandler::combineVideos(const QString &videoFile1, const QString &videoFile2, const QString &outputVideo) {
    ffmpeg.setArguments(QStringList() << "-i" << videoFile1 << "-c" << "copy" << "-bsf:v" << "h264_mp4toannexb" << "-f" << "mpegts" << "part1.ts");
    ffmpeg.start();
    ffmpeg.waitForFinished();

    ffmpeg.setArguments(QStringList() << "-i" << videoFile2 << "-c" << "copy" << "-bsf:v" << "h264_mp4toannexb" << "-f" << "mpegts" << "part2.ts");
    ffmpeg.start();
    ffmpeg.waitForFinished();

    ffmpeg.setArguments(QStringList() << "-i" << "concat:part1.ts|part2.ts" << "-c" << "copy" << "-bsf:a" << "aac_adtstoasc" << outputVideo);
    ffmpeg.start();
    ffmpeg.waitForFinished();
}

void FFmpegHandler::addTextToVideo(const QString &inputVideo, const QString &outputVideo, const QString &text, int x, int y) {
    QStringList arguments;
    arguments << "-i" << inputVideo
              << "-vf" << QString("drawtext=text='%1':x=%2:y=%3").arg(text).arg(x).arg(y)
              << outputVideo;

    QProcess ffmpegProcess;
    ffmpegProcess.start("ffmpeg", arguments);
    if (!ffmpegProcess.waitForStarted()) {
        qDebug() << "FFmpeg process failed to start:" << ffmpegProcess.errorString();
        return;
    }
    ffmpegProcess.waitForFinished();
}

void FFmpegHandler::executeFFmpegCommand(const QStringList &arguments) {
    QProcess process;
    process.start("ffmpeg", arguments);
    if (!process.waitForStarted()) {
        qDebug() << "FFmpeg process failed to start:" << process.errorString();
        QMessageBox::warning(nullptr, "Error", "Failed to start FFmpeg.");
        return;
    }

    if (!process.waitForFinished()) {
        qDebug() << "FFmpeg process failed:" << process.errorString();
        QMessageBox::warning(nullptr, "Error", "FFmpeg process failed.");
        return;
    }

    if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
        qDebug() << "FFmpeg process exited with errors:" << process.readAllStandardError();
        QMessageBox::warning(nullptr, "Error", "FFmpeg process exited with errors.");
        return;
    }

    qDebug() << "FFmpeg process finished successfully.";
    QMessageBox::information(nullptr, "Success", "Video with text overlay created successfully.");
}

void FFmpegHandler::addOverlayToVideo(const QString &inputVideo, const QString &outputVideo, const QString &overlayImage, int x, int y) {
    QStringList arguments;
    arguments << "-i" << inputVideo
              << "-i" << overlayImage
              << "-filter_complex" << QString("overlay=%1:%2").arg(x).arg(y)
              << outputVideo;

    QProcess ffmpegProcess;
    ffmpegProcess.start("ffmpeg", arguments);
    if (!ffmpegProcess.waitForStarted()) {
        qDebug() << "FFmpeg process failed to start:" << ffmpegProcess.errorString();
        return;
    }
    ffmpegProcess.waitForFinished();
}