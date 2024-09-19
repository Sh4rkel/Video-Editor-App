#include "TextOverlayItem.h"

TextOverlayItem::TextOverlayItem(const QString &text, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent) {
    setDefaultTextColor(Qt::white);
    setFont(QFont("Arial", 24));
}

void TextOverlayItem::setFont(const QFont &font) {
    QGraphicsTextItem::setFont(font);
}

void TextOverlayItem::setColor(const QColor &color) {
    setDefaultTextColor(color);
}

void TextOverlayItem::setPosition(const QPointF &position) {
    setPos(position);
}