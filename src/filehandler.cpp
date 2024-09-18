#include "filehandler.h"
#include "ui_FileHandler.h"
#include <QFileDialog>
#include <QListWidgetItem>

// Constructor
FileHandler::FileHandler(QWidget *parent) :
    QWidget(parent), ui(new Ui::FileHandler), fileManager(new FileManager(this)) {
    ui->setupUi(this);

    // Connect add video button to slot
    connect(ui->addVideoButton, &QPushButton::clicked, this, &FileHandler::onAddVideoButtonClicked);

    // Connect video list widget item double-clicked signal to slot
    connect(ui->videoListWidget, &QListWidget::itemDoubleClicked, this, &FileHandler::onVideoItemDoubleClicked);
}

// Destructor
FileHandler::~FileHandler() {
    delete ui;
}

// Slot for add video button clicked
void FileHandler::onAddVideoButtonClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Video"), "", tr("Video Files (*.mp4 *.avi *.mov)"));
    if (!filePath.isEmpty()) {
        fileManager->addVideo(filePath);
        ui->videoListWidget->addItem(filePath);
    }
}

// Slot for video item double-clicked
void FileHandler::onVideoItemDoubleClicked(QListWidgetItem *item) {
    emit fileSelected(item->text());
}