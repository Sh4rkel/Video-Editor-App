#ifndef FFMPEGHANDLER_H
#define FFMPEGHANDLER_H

#include <QObject>
#include <QThread>
#include "FFmpegWorker.h"

class FFmpegHandler : public QObject {
    Q_OBJECT

public:
    explicit FFmpegHandler(QObject *parent = nullptr);
    void executeFFmpegCommand(const QStringList &arguments);
    void convertVideoFormat(const QString &inputVideo, const QString &outputVideo, const QString &format);
    void cutVideoSegment(const QString &inputVideo, const QString &outputVideo, qint64 start, qint64 end);
    void combineVideos(const QString &videoFile1, const QString &videoFile2, const QString &outputVideo);
    void addTextToVideo(const QString &inputVideo, const QString &outputVideo, const QString &text, int x, int y);
    void addOverlayToVideo(const QString &inputVideo, const QString &outputVideo, const QString &overlayImage, int x, int y);

    signals:
        void commandFinished();
    void commandError(const QString &error);

    private slots:
        void handleWorkerFinished();
    void handleWorkerError(const QString &error);

private:
    QThread workerThread;
    FFmpegWorker *worker;
};

#endif // FFMPEGHANDLER_H