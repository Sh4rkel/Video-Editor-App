#include "FilterSettingsDialog.h"
#include <QMouseEvent>
#include <QStyle>
FilterSettingsDialog::FilterSettingsDialog(FilterSettings *settings, QWidget *parent)
    : QDialog(parent), filterSettings(settings) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    gradientSlider = new QSlider(Qt::Horizontal, this);
    gradientSlider->setRange(0, 100);
    gradientSlider->setValue(filterSettings->getGradient());
    connect(gradientSlider, &QSlider::valueChanged, filterSettings, &FilterSettings::setGradient);
    gradientSlider->installEventFilter(this);

    shadowSlider = new QSlider(Qt::Horizontal, this);
    shadowSlider->setRange(0, 100);
    shadowSlider->setValue(filterSettings->getShadow());
    connect(shadowSlider, &QSlider::valueChanged, filterSettings, &FilterSettings::setShadow);
    shadowSlider->installEventFilter(this);

    QLabel *gradientLabel = new QLabel("Gradient", this);
    gradientLabel->setStyleSheet("color: black;");
    QLabel *shadowLabel = new QLabel("Shadow", this);
    shadowLabel->setStyleSheet("color: black;");

    layout->addWidget(gradientLabel);
    layout->addWidget(gradientSlider);
    layout->addWidget(shadowLabel);
    layout->addWidget(shadowSlider);

    setLayout(layout);
    setWindowTitle("Filter Settings");
}

bool FilterSettingsDialog::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QSlider *slider = qobject_cast<QSlider*>(obj);
            if (slider) {
                int value = QStyle::sliderValueFromPosition(slider->minimum(), slider->maximum(), mouseEvent->pos().x(), slider->width());
                slider->setValue(value);
                return true;
            }
        }
    }
    return QDialog::eventFilter(obj, event);
}