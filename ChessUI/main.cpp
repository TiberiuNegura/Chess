#include "ChessUIQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessUIQt w;
    w.show();
    w.StartGame();

    QObject::connect(&w, &ChessUIQt::Exit, &a, &QApplication::quit);
    return a.exec();
}
