#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QWidget>
#include <QListWidgetItem>
#include "FileManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FileHandler; }
QT_END_NAMESPACE

class FileHandler : public QWidget {
    Q_OBJECT

public:
    explicit FileHandler(QWidget *parent = nullptr);
    ~FileHandler() override;

    signals:
        void fileSelected(const QString &filePath);

    private slots:
        void onAddVideoButtonClicked();
    void onVideoItemDoubleClicked(QListWidgetItem *item);

private:
    Ui::FileHandler *ui;
    FileManager *fileManager;
};

#endif 
