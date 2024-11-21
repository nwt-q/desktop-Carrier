#include "include/carrier.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QResource::registerResource(qApp->applicationDirPath() + "resources/res.rcc");
    Carrier w;
    w.show();
    return QApplication::exec();
}
