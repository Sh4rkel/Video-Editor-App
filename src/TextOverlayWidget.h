#ifndef TEXTOVERLAYWIDGET_H
#define TEXTOVERLAYWIDGET_H

#include <QWidget>
#include <QLabel>

class TextOverlayWidget : public QWidget
{
Q_OBJECT

public:
    explicit TextOverlayWidget(QWidget *parent = nullptr);
    virtual ~TextOverlayWidget();
    void setText(const QString &text);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;



private:
    QString text;
    QPoint dragStartPosition;
};

#endif
