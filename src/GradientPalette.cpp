#include "GradientPalette.h"

QString GradientPalette::createGradientFromPalette(const QList<QColor> &colors) {
    QString gradient = "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, ";
    double stopInterval = 1.0 / (colors.size() - 1);
    for (int i = 0; i < colors.size(); ++i) {
        gradient += QString("stop:%1 %2, ").arg(i * stopInterval).arg(colors[i].name());
    }
    gradient.chop(2);
    gradient += ")";
    return gradient;
}