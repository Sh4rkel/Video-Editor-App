#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QVBoxLayout>
#include <QPushButton>

namespace Ui {
    class FilterSettings {
    public:
        QComboBox *filterComboBox;
        QPushButton *applyButton;
        QPushButton *cancelButton;

        void setupUi(QDialog *FilterSettings) {
            if (FilterSettings->objectName().isEmpty())
                FilterSettings->setObjectName(QString::fromUtf8("FilterSettings"));
            FilterSettings->resize(400, 300);

            filterComboBox = new QComboBox(FilterSettings);
            filterComboBox->setObjectName(QString::fromUtf8("filterComboBox"));
            filterComboBox->addItem("Grayscale");
            filterComboBox->addItem("Sepia");
            filterComboBox->addItem("Invert");

            applyButton = new QPushButton(FilterSettings);
            applyButton->setObjectName(QString::fromUtf8("applyButton"));
            applyButton->setText("Apply");

            cancelButton = new QPushButton(FilterSettings);
            cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
            cancelButton->setText("Cancel");

            QVBoxLayout *layout = new QVBoxLayout(FilterSettings);
            layout->addWidget(filterComboBox);
            layout->addWidget(applyButton);
            layout->addWidget(cancelButton);

            retranslateUi(FilterSettings);

            QMetaObject::connectSlotsByName(FilterSettings);
        }

        void retranslateUi(QDialog *FilterSettings) {
            FilterSettings->setWindowTitle(QCoreApplication::translate("FilterSettings", "Filter Settings", nullptr));
        }
    };
}