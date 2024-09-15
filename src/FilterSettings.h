#ifndef FILTERSETTINGS_H
#define FILTERSETTINGS_H

#include <QDialog>

namespace Ui {
    class FilterSettings;
}

class FilterSettings : public QDialog {
    Q_OBJECT

public:
    explicit FilterSettings(QWidget *parent = nullptr);
    ~FilterSettings();

    QString getSelectedFilter() const;
    int getGradient() const;
    void setGradient(int value);
    int getShadow() const;
    void setShadow(int value);

    enum FilterType {
        Grayscale,
        Sepia,
        Invert
    };

    signals:
        void settingsChanged();

private:
    Ui::FilterSettings *ui;
    int gradient;
    int shadow;
};

#endif