#include "rightplayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RightPlayer w;
    w.show();
    return a.exec();
}
