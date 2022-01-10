#include "widget.h"
#include <QApplication>

const int ticks_per_second = 25;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
