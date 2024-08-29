#ifndef FILTERSETTINGS_H
#define FILTERSETTINGS_H

#include <QObject>

class FilterSettings : public QObject {
    Q_OBJECT

public:
    explicit FilterSettings(QObject *parent = nullptr);

    int getGradient() const;
    void setGradient(int value);

    int getShadow() const;
    void setShadow(int value);

    signals:
        void settingsChanged();

private:
    int gradient;
    int shadow;
};

#endif // FILTERSETTINGS_H