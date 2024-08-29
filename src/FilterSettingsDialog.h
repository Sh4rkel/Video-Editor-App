#ifndef FILTERSETTINGSDIALOG_H
#define FILTERSETTINGSDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include "FilterSettings.h"

class FilterSettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit FilterSettingsDialog(FilterSettings *settings, QWidget *parent = nullptr);

private:
    FilterSettings *filterSettings;
    QSlider *gradientSlider;
    QSlider *shadowSlider;
};

#endif // FILTERSETTINGSDIALOG_H