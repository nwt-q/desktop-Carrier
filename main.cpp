#include "include/carrier.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Carrier w;
    w.show();
    return QApplication::exec();
}
