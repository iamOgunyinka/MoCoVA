#include "mainwindows.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    mainwindows windows;

    windows.show();
    return app.exec();
}
