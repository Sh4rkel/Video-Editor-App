#ifndef PROJECT_CPP_VIDEOEDITOR_H
#define PROJECT_CPP_VIDEOEDITOR_H

#include <QObject>

class VideoEditor : public QObject {
Q_OBJECT

public:
    explicit VideoEditor(QObject *parent = nullptr);

    // TODO: Add methods for video editing operations

signals:
    // TODO: Add signals to notify about changes in the video

};

#endif