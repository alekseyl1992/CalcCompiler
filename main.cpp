#include <QtWidgets/QApplication>
#include <QTextCodec>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
