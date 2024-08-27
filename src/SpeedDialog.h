#ifndef SPEEDDIALOG_H
#define SPEEDDIALOG_H

#include <QDialog>
#include "SpeedWidget.h"

class SpeedDialog : public QDialog {
    Q_OBJECT

public:
    explicit SpeedDialog(QWidget *parent = nullptr);

private:
    SpeedWidget *speedWidget;
};

#endif // SPEEDDIALOG_H