#include <QApplication>
#include "MainWindow.h"
#include <QScopedPointer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QScopedPointer<MainWindow> w(new MainWindow);
    w->show();
    return a.exec();
}