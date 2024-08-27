#include "SpeedDialog.h"
#include <QVBoxLayout>

SpeedDialog::SpeedDialog(QWidget *parent) : QDialog(parent), speedWidget(new SpeedWidget(this)) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(speedWidget);
    setLayout(layout);
    setWindowTitle(tr("Adjust Playback Speed"));
}