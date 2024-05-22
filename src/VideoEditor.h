#ifndef PROJECT_CPP_VIDEOEDITOR_H
#define PROJECT_CPP_VIDEOEDITOR_H

#include <QObject>
#include <QShowEvent>
class VideoEditor : public QObject {
Q_OBJECT

public:
    explicit VideoEditor(QObject *parent = nullptr);

//    virtual ~VideoEditor();
    // TODO: Add methods for video editing operations

signals:
    // TODO: Add signals to notify about changes in the video

};

#endif