#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QStringList>

class FileManager : public QObject {
    Q_OBJECT

public:
    explicit FileManager(QObject *parent = nullptr);
    void addVideo(const QString &filePath);
    QStringList getVideos() const;

private:
    QStringList videoList;
};

#endif 
