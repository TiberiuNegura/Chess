#include "ChessUIQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/ChessUI/res/logo2.png"));
    std::shared_ptr w = std::make_shared<ChessUIQt>();

    w->InitGame();
    w->UpdateBoard();

    QObject::connect(w.get(), &ChessUIQt::Exit, &a, &QApplication::quit);
    return a.exec();
}
