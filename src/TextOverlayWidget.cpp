#include "TextOverlayWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>

TextOverlayWidget::TextOverlayWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground);
    bool isTransparentForMouseEvents = testAttribute(Qt::WA_TransparentForMouseEvents);
    bool isTranslucentBackground = testAttribute(Qt::WA_TranslucentBackground);

}

void TextOverlayWidget::setText(const QString &text)
{
    this->text = text;
    raise();
    update();
}

void TextOverlayWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 30));
    int x = 10;
    int y = 50;

    QFontMetrics fm(painter.font());
    int textWidth = fm.horizontalAdvance(text);
    int textHeight = fm.height();
    QRect textRect(x, y - textHeight, textWidth, textHeight);

    painter.setOpacity(1);

    painter.fillRect(textRect, QColor(255, 255, 0, 127));

    painter.drawText(x, y, text);

}

void TextOverlayWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->pos();
    }
}

void TextOverlayWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton)) {
        return;
    }
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
        return;
    }

    update();
}

TextOverlayWidget::~TextOverlayWidget()
{
    qDebug() << "TextOverlayWidget destroyed";
    if (parent())
        qDebug() << "Parent widget:" << parent()->metaObject()->className();
    else
        qDebug() << "No parent widget";
}




