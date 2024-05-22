#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (!fileName.isEmpty()) {
        ui->videoPlayerWidget->loadVideo(fileName);
    }
}

void MainWindow::saveFile() {
    // Implementation for saving file
}

void MainWindow::cutVideo() {
    // Implementation for cutting video
}

void MainWindow::addTextToVideo() {
    // Implementation for adding text to video
}

void MainWindow::combineVideos() {
    // Implementation for combining videos
}
