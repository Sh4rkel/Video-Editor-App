#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QWidget>
#include "FileManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FileHandler; }
QT_END_NAMESPACE

class FileHandler : public QWidget {
    Q_OBJECT

public:
    explicit FileHandler(QWidget *parent = nullptr);
    ~FileHandler() override;

    private slots:
        void onAddVideoButtonClicked();

private:
    Ui::FileHandler *ui;
    FileManager *fileManager;
};

#endif // FILEHANDLER_H