#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Client window;
    window.hide();
    return app.exec();
}
