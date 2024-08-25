#include "filehandler.h"
#include "ui_FileHandler.h"
#include <QFileDialog>

FileHandler::FileHandler(QWidget *parent) :
    QWidget(parent), ui(new Ui::FileHandler), fileManager(new FileManager(this)) {
    ui->setupUi(this);

    // Connect the add video button to the slot
    connect(ui->addVideoButton, &QPushButton::clicked, this, &FileHandler::onAddVideoButtonClicked);
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