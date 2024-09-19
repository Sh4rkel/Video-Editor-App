#include <QApplication>
#include "MainWindow.h"
#include <QIcon>
#include <QTranslator>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Video Editor");
    w.setWindowIcon(QIcon("C:/Users/filip/CLionProjects/Video-Editor-App/assets/logo.png"));

    QString styleSheet = R"(
        QMainWindow {
            background-color: #2E2E2E;
            color: #FFFFFF;
        }

        QMenuBar {
            background-color: #3E3E3E;
            color: #FFFFFF;
            border-bottom: 1px solid #5E5E5E;
        }

        QMenuBar::item {
            background-color: #3E3E3E;
            color: #FFFFFF;
        }

        QMenuBar::item:selected {
            background-color: #5E5E5E;
        }

        QMenu {
            background-color: #3E3E3E;
            color: #FFFFFF;
            border: 1px solid #5E5E5E;
        }

        QMenu::item:selected {
            background-color: #5E5E5E;
        }

        QPushButton {
            background-color: #4E4E4E;
            color: #FFFFFF;
            border: 1px solid #5E5E5E;
            border-radius: 5px;
            padding: 5px;
        }

        QPushButton:hover {
            background-color: #5E5E5E;
        }

        QPushButton:pressed {
            background-color: #3E3E3E;
        }

        QStatusBar {
            background-color: #3E3E3E;
            color: #FFFFFF;
            border-top: 1px solid #5E5E5E;
        }

        QSlider::groove:horizontal {
            border: 1px solid #5E5E5E;
            height: 8px;
            background: #3E3E3E;
            margin: 2px 0;
            border-radius: 4px;
        }

        QSlider::sub-page:horizontal {
            background: #FFFFFF;
            border: 1px solid #5E5E5E;
            height: 8px;
            border-radius: 4px;
        }

        QSlider::handle:horizontal {
            background: #5E5E5E;
            border: 1px solid #5E5E5E;
            width: 18px;
            margin: -2px 0;
            border-radius: 9px;
        }

        QSlider::handle:horizontal:hover {
            background: #7E7E7E;
        }

        QSlider::handle:horizontal:pressed {
            background: #3E3E3E;
        }

        QLabel {
            color: #FFFFFF;
        }

        QListWidget {
            background-color: #2E2E2E;
            color: #FFFFFF;
            border: 1px solid #5E5E5E;
        }

        QListWidget::item {
            background-color: #3E3E3E;
            color: #FFFFFF;
        }

        QListWidget::item:selected {
            background-color: #5E5E5E;
        }

        QLineEdit {
            background-color: #3E3E3E;
            color: #FFFFFF;
            border: 1px solid #5E5E5E;
            border-radius: 5px;
            padding: 5px;
        }

        QComboBox {
            background-color: #3E3E3E;
            color: #FFFFFF;
            border: 1px solid #5E5E5E;
            border-radius: 5px;
            padding: 5px;
        }

        QComboBox::drop-down {
            background-color: #4E4E4E;
        }

        QComboBox::down-arrow {
            image: url(:/icons/down_arrow.png);
        }

        QCheckBox {
            color: #FFFFFF;
        }

        QCheckBox::indicator {
            width: 20px;
            height: 20px;
        }

        QCheckBox::indicator:checked {
            image: url(:/icons/checkbox_checked.png);
        }

        QCheckBox::indicator:unchecked {
            image: url(:/icons/checkbox_unchecked.png);
        }

        QRadioButton {
            color: #FFFFFF;
        }

        QTabWidget::pane {
            border: 1px solid #5E5E5E;
            background: #2E2E2E;
        }

        QTabBar::tab {
            background: #3E3E3E;
            color: #FFFFFF;
            padding: 10px;
            border: 1px solid #5E5E5E;
            border-bottom: none;
        }

        QTabBar::tab:selected {
            background: #5E5E5E;
            margin-bottom: -1px;
        }

        QToolBar {
            background: #3E3E3E;
            border: 1px solid #5E5E5E;
        }

        QToolButton {
            background: #4E4E4E;
            color: #FFFFFF;
            border: 1px solid #5E5E5E;
            border-radius: 5px;
            padding: 5px;
        }

        QToolButton:hover {
            background: #5E5E5E;
        }

        QToolButton:pressed {
            background: #3E3E3E;
        }
    )";

    qApp->setStyleSheet(styleSheet);
    w.show();
    return a.exec();
}