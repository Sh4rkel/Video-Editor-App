#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , currentVideo("")
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

void MainWindow::convertVideoFormat(const QString &inputVideo, const QString &outputVideo, const QString &format)
{
    QProcess ffmpeg;
    QStringList arguments;
    arguments << "-i" << inputVideo << outputVideo + "." + format;
    ffmpeg.start("ffmpeg", arguments);
    ffmpeg.waitForFinished();
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
        currentVideo = fileName;
    }
}
void MainWindow::saveFile()
{
    if (currentVideo.isEmpty()) {
        return;
    }

    QString outputVideo = QFileDialog::getSaveFileName(this, tr("Save Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (outputVideo.isEmpty()) {
        return;
    }

    QStringList formats;
    formats << "mp4" << "avi" << "mkv" << "mov";
    bool ok;
    QString format = QInputDialog::getItem(this, tr("Select Output Format"), tr("Format:"), formats, 0, false, &ok);
    if (ok && !format.isEmpty()) {
        convertVideoFormat(currentVideo, outputVideo, format);
    }
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
        ui->videoPlayerWidget->update();
    }
}

void MainWindow::combineVideos()
{
    // Implementation for combining videos
}
