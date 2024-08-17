#include "Track.h"

Track::Track(const QString &name, QWidget *parent) : QWidget(parent) {
    layout = new QHBoxLayout(this);
    label = new QLabel(name, this);
    addButton = new QPushButton("+", this);
    layout->addWidget(label);
    layout->addWidget(addButton);
    setLayout(layout);
}