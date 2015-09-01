
#include <QtWidgets/QApplication>
#include "Launcher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Launcher w;
    w.show();
    return a.exec();
}
