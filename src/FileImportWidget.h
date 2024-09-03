#ifndef FILEIMPORTWIDGET_H
#define FILEIMPORTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>

class FileImportWidget : public QWidget {
    Q_OBJECT

public:
    explicit FileImportWidget(QWidget *parent = nullptr);

    signals:
        void fileImported(const QString &fileName);

    private slots:
        void onImportButtonClicked();

private:
    QPushButton *importButton;
    QListWidget *fileListWidget;
    QVBoxLayout *mainLayout;
};

#endif 
