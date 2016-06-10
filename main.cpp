#include "okno.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    okno w;
    w.show();

    return a.exec();
}
