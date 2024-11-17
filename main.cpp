#include "include/carrier.h"
#include "include/setwin.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QDir::setCurrent(QApplication::applicationDirPath()); // 设置工作目录为应用
    Carrier w;
    //SetWin w;
    w.show();
    return QApplication::exec();
}
