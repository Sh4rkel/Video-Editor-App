#include "FileManager.h"

// Constructor
FileManager::FileManager(QObject *parent) : QObject(parent) {}

// Add video file path to the list
void FileManager::addVideo(const QString &filePath) {
    videoList.append(filePath);
}

// Get the list of video file paths
QStringList FileManager::getVideos() const {
    return videoList;
}