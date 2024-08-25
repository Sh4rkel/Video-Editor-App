#include "filehandler.h"
#include "ui_FileHandler.h"
#include <QFileDialog>
#include <QListWidgetItem>

FileHandler::FileHandler(QWidget *parent) :
    QWidget(parent), ui(new Ui::FileHandler), fileManager(new FileManager(this)) {
    ui->setupUi(this);

    connect(ui->addVideoButton, &QPushButton::clicked, this, &FileHandler::onAddVideoButtonClicked);

    connect(ui->videoListWidget, &QListWidget::itemDoubleClicked, this, &FileHandler::onVideoItemDoubleClicked);
}

FileHandler::~FileHandler() {
    delete ui;
}

void FileHandler::onAddVideoButtonClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Video"), "", tr("Video Files (*.mp4 *.avi *.mov)"));
    if (!filePath.isEmpty()) {
        fileManager->addVideo(filePath);
        ui->videoListWidget->addItem(filePath);
    }
}

void FileHandler::onVideoItemDoubleClicked(QListWidgetItem *item) {
    emit fileSelected(item->text());
}