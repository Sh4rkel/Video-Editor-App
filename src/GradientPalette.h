#ifndef GRADIENTPALETTE_H
#define GRADIENTPALETTE_H

#include <QColor>
#include <QString>
#include <QList>

class GradientPalette {
public:
    static QString createGradientFromPalette(const QList<QColor> &colors);
};

#endif