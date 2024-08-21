#ifndef FFMPEGHANDLER_H
#define FFMPEGHANDLER_H

#include <QObject>
#include <QProcess>

class FFmpegHandler : public QObject {
    Q_OBJECT

public:
    explicit FFmpegHandler(QObject *parent = nullptr);
    void convertVideoFormat(const QString &inputFile, const QString &outputFile, const QString &format);
    void cutVideoSegment(const QString &inputFile, const QString &outputFile, qint64 start, qint64 end);
    void combineVideos(const QString &inputFile1, const QString &inputFile2, const QString &outputFile);
    void addTextToVideo(const QString &inputVideo, const QString &outputVideo, const QString &text, int x, int y);

private:
    QString ffmpegPath;
    QProcess ffmpeg;
    void executeFFmpegCommand(const QStringList &arguments);

};

#endif // FFMPEGHANDLER_H