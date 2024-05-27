#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QProcess>
#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include "VideoPlayerWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    qint64 cutStart = -1;
    qint64 cutEnd = -1;
    QString currentVideo;

    void cutVideoSegment(const QString &inputVideo, const QString &outputVideo, qint64 start, qint64 end);


private slots:

    void togglePlayPause();

    void openFile();

    void saveFile();

    void cutVideo();

    void addTextToVideo();

    void combineVideos();

    void convertVideoFormat(const QString &inputVideo, QString &outputVideo, const QString &format);
};

#endif // MAINWINDOW_H
