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
#include <QDialog>
#include <QComboBox>

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

	void InitGame();

	void Init(QGridLayout* mainGridLayout);
	void InitializeTitleBar(QGridLayout* mainGridLayout);
	void InitializePlayers(QGridLayout* mainGridLayout, EColor color);
	QWidget* InitializeButtons();
	QWidget* InitializeTimers();
	QWidget* InitializeHistory();
	void InitializePanel(QGridLayout* mainGridLayout);
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
	void OnMovePiece(Position start, Position end, milliseconds elapsedTime) override;
	void OnRestart() override;
	void OnPieceCapture(EType pieceType, EColor pieceColor) override;
	void SetGame(IGamePtr game);
	void OnTimerTick(milliseconds whiteTimer, milliseconds blackTimer) override;


public slots:
	void OnButtonClicked(const Position& position);

	void OnSaveButtonClicked();
	void OnLoadButtonClicked();
	void OnRestartButtonClicked();
	void OnPauseButtonClicked();
	void OnDrawButtonClicked();
	char PieceToChar(IPiecePtr piece) const;
	void OnCopyButtonClicked();
	void BoardLock(bool enabled);
	void OnHistoryClicked(QListWidgetItem* item);
	void centerOnScreen();
	

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

	void RunMethod(std::function<void(void)> func);

signals:
	void Exit();

private:
	QWidget* FromMatrixToChessMove(Position start, Position end, int elapsedTime, int color = 2);
	void toggleFullScreen();
	void CloseApp();

private:
	std::array<std::array<GridButton*, 8>, 8> m_grid;
	std::optional<Position> m_selectedCell;
	QGridLayout* m_blackGrid, *m_whiteGrid;
	QListWidget* m_MovesList, *m_blackPieces, *m_whitePieces;
	QLabel* m_BlackTimer, *m_WhiteTimer, *m_StatusMessage;
	IGamePtr m_game;
	QPoint m_dragStartPos;
	QPushButton* m_expandButton, * m_pauseGameBtn;
};
