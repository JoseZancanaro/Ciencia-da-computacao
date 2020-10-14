#include "View\MainWindow.hpp"

#include <QApplication>
#include <algorithm>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
