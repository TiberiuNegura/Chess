#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qgridlayout.h>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QClipboard>
#include <QProcess>
#include <QApplication>

#include "GridButton.h"

#include "IGame.h"
#include "IPiece.h"
#include "IGameListener.h"

class ChessUIQt : public QMainWindow, public IGameListener, public std::enable_shared_from_this<ChessUIQt>
{
	Q_OBJECT

public:
	ChessUIQt(QWidget *parent = nullptr);
	~ChessUIQt() override;


	void Init(QGridLayout* mainGridLayout);
	void InitializeTitleBar(QGridLayout* mainGridLayout);
	void InitializePlayers(QGridLayout* mainGridLayout, EColor color);
	void InitializeButtons(QGridLayout* mainGridLayout);
	void InitializeTimers(QGridLayout* mainGridLayout);
	void InitializeHistory(QGridLayout* mainGridLayout);
	void InitializeBoard(QGridLayout* mainGridLayout);
	void UpdateHistory();
	void UpdateBoard();
	void HighlightPossibleMoves(const PositionList& possibleMoves);

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
	void OnPieceCapture(EType pieceType, EColor pieceColor) override;
	void SetGame(IGamePtr game);

public slots:
	void OnButtonClicked(const Position& position);

	void OnSaveButtonClicked();
	void OnLoadButtonClicked();
	void OnRestartButtonClicked();
	void OnDrawButtonClicked();
	char PieceToChar(IPiecePtr piece) const;
	void OnCopyButtonClicked();
	void BoardLock(bool enable);
	void OnHistoryClicked(QListWidgetItem* item);
	void centerOnScreen();
	

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

signals:
	void Exit();

private:
	QWidget* FromMatrixToChessMove(Position start, Position end) const;
	void toggleFullScreen();

private:
	std::array<std::array<GridButton*, 8>, 8> m_grid;
	std::optional<Position> m_selectedCell;
	QGridLayout* m_blackGrid, *m_whiteGrid;
	QListWidget* m_MovesList, *m_blackPieces, *m_whitePieces;
	QLabel* m_BlackTimer, *m_WhiteTimer, *m_StatusMessage;
	IGamePtr m_game;
	QPoint m_dragStartPos;
	QPushButton* m_expandButton;
};
