
#include "main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    main_window * window = new main_window();
    window->show();
    return app.exec();
}

