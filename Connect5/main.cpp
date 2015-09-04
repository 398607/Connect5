
#include <QtWidgets/QApplication>
#include "Launcher.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(connect5);
    QApplication a(argc, argv);
    Launcher w;

    w.show();
    return a.exec();
}
