#include "FileManager.h"

FileManager::FileManager(QObject *parent) : QObject(parent) {}

void FileManager::addVideo(const QString &filePath) {
    videoList.append(filePath);
}

QStringList FileManager::getVideos() const {
    return videoList;
}