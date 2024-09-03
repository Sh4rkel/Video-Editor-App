#ifndef FFMPEGWORKER_H
#define FFMPEGWORKER_H

#include <QObject>
#include <QProcess>

class FFmpegWorker : public QObject {
    Q_OBJECT

public:
    explicit FFmpegWorker(QObject *parent = nullptr);
    void setArguments(const QStringList &arguments);

    public slots:
        void execute();

    signals:
        void finished();
    void errorOccurred(const QString &error);

private:
    QStringList arguments;
};

#endif 
