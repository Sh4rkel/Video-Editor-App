#include "FFmpegHandler.h"
#include <QFile>
#include <QMessageBox>

FFmpegHandler::FFmpegHandler(QObject *parent) : QObject(parent) {}

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

    ffmpeg.start("ffmpeg", arguments);

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

    ffmpeg.start("ffmpeg", arguments);

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

void FFmpegHandler::addTextToVideo(const QString &inputVideo, const QString &outputVideo, const QString &text) {
    QStringList arguments;
    arguments << "-i" << inputVideo
              << "-vf" << QString("drawtext=text='%1':fontcolor=white:fontsize=24").arg(text)
              << outputVideo;

    ffmpeg.start("ffmpeg", arguments);

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

    QMessageBox::information(nullptr, "Success", "Video with text overlay created successfully.");
}

void FFmpegHandler::combineVideos(const QString &videoFile1, const QString &videoFile2, const QString &outputVideo) {
    ffmpeg.start("ffmpeg", QStringList() << "-i" << videoFile1 << "-c" << "copy" << "-bsf:v" << "h264_mp4toannexb" << "-f" << "mpegts" << "part1.ts");
    ffmpeg.waitForFinished();
    ffmpeg.start("ffmpeg", QStringList() << "-i" << videoFile2 << "-c" << "copy" << "-bsf:v" << "h264_mp4toannexb" << "-f" << "mpegts" << "part2.ts");
    ffmpeg.waitForFinished();

    ffmpeg.start("ffmpeg", QStringList() << "-i" << "concat:part1.ts|part2.ts" << "-c" << "copy" << "-bsf:a" << "aac_adtstoasc" << outputVideo);
    ffmpeg.waitForFinished();
}