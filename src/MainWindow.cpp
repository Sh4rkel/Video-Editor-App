#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveFile);
    connect(ui->cutButton, &QPushButton::clicked, this, &MainWindow::cutVideo);
    connect(ui->addTextButton, &QPushButton::clicked, this, &MainWindow::addTextToVideo);
    connect(ui->combineButton, &QPushButton::clicked, this, &MainWindow::combineVideos);
    connect(ui->timelineWidget, &TimelineWidget::positionChanged, ui->videoPlayerWidget, &VideoPlayerWidget::seek);
    ui->videoPlayerWidget->show(); // Add this line
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destroyed";
    delete ui;
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (!fileName.isEmpty()) {
        ui->videoPlayerWidget->loadVideo(fileName);
    }
}
void MainWindow::saveFile()
{
    QString inputVideo = "/path/to/input/video.mp4";
    QString outputVideo = "/path/to/output/video.mp4";
    QString text = "Your text here";

    QProcess ffmpeg;
    QStringList arguments;
    arguments << "-i" << inputVideo << "-vf" << QString("drawtext=text='%1':x=10:y=10:fontsize=24:fontcolor=white").arg(text) << outputVideo;
    ffmpeg.start("ffmpeg", arguments);
    ffmpeg.waitForFinished();
}

void MainWindow::cutVideo()
{
    // Implementation for cutting video
}

void MainWindow::addTextToVideo()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Text"), tr("Text to overlay:"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        ui->videoPlayerWidget->addTextOverlay(text);
        ui->videoPlayerWidget->update(); // Add this line
    }
}

void MainWindow::combineVideos()
{
    // Implementation for combining videos
}
