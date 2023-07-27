#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qgridlayout.h>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QClipboard>

#include "GridButton.h"

#include "IGame.h"
#include "IPiece.h"
#include "IGameListener.h"

class ChessUIQt : public QMainWindow, public IGameListener
{
    Q_OBJECT

public:
    ChessUIQt(QWidget *parent = nullptr);
    ~ChessUIQt() override;


    void Init(QGridLayout* mainGridLayout);
    void InitializeMessage(QGridLayout* mainGridLayout);
    void InitializeButtons(QGridLayout* mainGridLayout);
    void InitializeTimers(QGridLayout* mainGridLayout);
    void InitializeHistory(QGridLayout* mainGridLayout);
    void InitializeBoard(QGridLayout* mainGridLayout);

    //Modify if necessary with your history representation
    void UpdateHistory();
    void UpdateBoard(const MatrixPtr& newBoard);
    void HighlightPossibleMoves(const PositionList& possibleMoves);

    void StartGame();
    void ShowPromoteOptions();

    QString GetTurnMessage();

    QString GameTurnToString();
    QString GameStateToString();

    
    void OnGameOver() override;
    void OnCheck(std::string msg) override;
    void OnPawnEvolve() override;
    void OnTieRequest() override;
    void OnMovePiece(Position start, Position end) override;
    void OnRestart() override;

    void SetGame(IGamePtr game);

public slots:
    void OnButtonClicked(const Position& position);

    void OnSaveButtonClicked();
    void OnLoadButtonClicked();
    void OnRestartButtonClicked();
    void OnDrawButtonClicked();
    char PieceToChar(IPiecePtr piece) const;
    void OnCopyButtonClicked();
    void OnHistoryClicked(QListWidgetItem* item);
    

signals:
    void Exit();

private:
    std::array<std::array<GridButton*, 8>, 8> m_grid;
    std::optional<Position> m_selectedCell;
    QLabel* m_MessageLabel;
    QListWidget* m_MovesList;
    QLabel* m_BlackTimer, *m_WhiteTimer;
    IGamePtr m_game;
};
