#include "FileImportWidget.h"
#include <QFileDialog>

FileImportWidget::FileImportWidget(QWidget *parent) : QWidget(parent) {
    importButton = new QPushButton("Import Video", this);
    fileListWidget = new QListWidget(this);

    connect(importButton, &QPushButton::clicked, this, &FileImportWidget::onImportButtonClicked);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(importButton);
    mainLayout->addWidget(fileListWidget);
    setLayout(mainLayout);
}

void FileImportWidget::onImportButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv *.mov)"));
    if (!fileName.isEmpty()) {
        fileListWidget->addItem(fileName);
        emit fileImported(fileName);
    }
}