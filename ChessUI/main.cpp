#include "ChessUIQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr w = std::make_shared<ChessUIQt>();
    IGamePtr game = IGame::Produce();
    w->SetGame(game);
    game->AddListener(w);

    w->show();
    w->UpdateBoard();

    QObject::connect(w.get(), &ChessUIQt::Exit, &a, &QApplication::quit);
    return a.exec();
}
