#ifndef TEXTOVERLAYITEM_H
#define TEXTOVERLAYITEM_H

#include <QGraphicsTextItem>
#include <QFont>
#include <QColor>

class TextOverlayItem : public QGraphicsTextItem {
public:
    TextOverlayItem(const QString &text, QGraphicsItem *parent = nullptr);

    void setFont(const QFont &font);
    void setColor(const QColor &color);
    void setPosition(const QPointF &position);

};

#endif // TEXTOVERLAYITEM_H