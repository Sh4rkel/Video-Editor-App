#include "TimelineWidget.h"
#include "ui_TimelineWidget.h"
#include <QLabel>

TimelineWidget::TimelineWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TimelineWidget),
        isPlaying(false)
{
    ui->setupUi(this);

    // Initialize widgets
    slider = new QSlider(Qt::Horizontal, this);
    speedSlider = new QSlider(Qt::Horizontal, this);
    playPauseButton = new QPushButton("▶️", this);

    // Configure widgets
    speedSlider->setRange(50, 200);
    speedSlider->setValue(100);

    // Connect signals and slots
    connect(speedSlider, &QSlider::valueChanged, [this](int value) {
        emit speedChanged(value / 100.0);
    });
    connect(slider, &QSlider::valueChanged, this, &TimelineWidget::onSliderValueChanged);
    connect(playPauseButton, &QPushButton::clicked, this, &TimelineWidget::onPlayPauseButtonClicked);

    // Layout setup
    controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(playPauseButton);
    controlsLayout->addWidget(slider);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(speedSlider);
    setLayout(mainLayout);
}

void TimelineWidget::onSliderValueChanged(int value)
{
    emit positionChanged(value);
}

void TimelineWidget::onPlayPauseButtonClicked()
{
    isPlaying = !isPlaying;
    playPauseButton->setText(isPlaying ? "⏸️" : "▶️");
    emit playPauseClicked();
}

void TimelineWidget::setDuration(int duration)
{
    slider->setMaximum(duration);
}

void TimelineWidget::setPosition(int position)
{
    slider->setValue(position);
}

TimelineWidget::~TimelineWidget()
{
    delete ui;
}