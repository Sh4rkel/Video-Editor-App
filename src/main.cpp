#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Video Editor");

    // Add some style to the main window
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
    )";

    a.setStyleSheet(styleSheet);

    w.show();
    return a.exec();
}