#include "synwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SynWindow w;
    w.show();
    return a.exec();
}
