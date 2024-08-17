#ifndef TRACK_H
#define TRACK_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class Track : public QWidget {
    Q_OBJECT

public:
    explicit Track(const QString &name, QWidget *parent = nullptr);

private:
    QHBoxLayout *layout;
    QLabel *label;
    QPushButton *addButton;
};

#endif // TRACK_H