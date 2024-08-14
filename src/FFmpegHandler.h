#ifndef FFMPEGHANDLER_H
#define FFMPEGHANDLER_H

#include <QObject>
#include <QProcess>

class FFmpegHandler : public QObject {
    Q_OBJECT

public:
    explicit FFmpegHandler(QObject *parent = nullptr);
    void convertVideoFormat(const QString &inputVideo, const QString &outputVideo, const QString &format);
    void cutVideoSegment(const QString &inputVideo, const QString &outputVideo, qint64 start, qint64 end);
    void addTextToVideo(const QString &inputVideo, const QString &outputVideo, const QString &text);
    void combineVideos(const QString &videoFile1, const QString &videoFile2, const QString &outputVideo);

private:
    QProcess ffmpeg;
};

#endif // FFMPEGHANDLER_H