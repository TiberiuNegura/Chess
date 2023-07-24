#include "ChessUIQt.h"
#include "ChessUIQt.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QtWidgets/QApplication>
#include <QDebug>

ChessUIQt::ChessUIQt(QWidget *parent)
	: QMainWindow(parent)
{
   
	//Widget containing everything
	QWidget* mainWidget = new QWidget();
	QGridLayout* mainGridLayout = new QGridLayout();
	InitializeBoard(mainGridLayout);
	InitializeMessage(mainGridLayout);
	InitializeButtons(mainGridLayout);
	InitializeTimers(mainGridLayout);
	InitializeHistory(mainGridLayout);
	mainWidget->setLayout(mainGridLayout);
	this->setCentralWidget(mainWidget);


	m_game = IGame::Produce();
}

ChessUIQt::~ChessUIQt()
{
	//No delete?
	//https://doc.qt.io/qt-6/objecttrees.html
}

void ChessUIQt::InitializeMessage(QGridLayout * mainGridLayout)
{
	m_MessageLabel = new QLabel();
	m_MessageLabel->setAlignment(Qt::AlignCenter);
	m_MessageLabel->setStyleSheet("font-size: 20px; font-weight: bold; ");

	mainGridLayout->addWidget(m_MessageLabel, 0, 1, 1, 1);
}

void ChessUIQt::InitializeButtons(QGridLayout* mainGridLayout)
{
	QPushButton* saveButton = new QPushButton("Save");
	QPushButton* loadButton = new QPushButton("Load");
	QPushButton* restartButton = new QPushButton("Restart");
	QPushButton* drawButton = new QPushButton("Draw");
	QPushButton* copyButton = new QPushButton("Copy");

	QWidget* buttonContainer = new QWidget();
	QGridLayout* btnGrid = new QGridLayout();


	btnGrid->addWidget(saveButton, 0, 0);
	btnGrid->addWidget(loadButton, 0, 1);
	btnGrid->addWidget(restartButton, 0, 2);
	btnGrid->addWidget(drawButton, 0, 3);
	btnGrid->addWidget(copyButton, 1, 0, 1, 4);
	

	connect(saveButton, &QPushButton::pressed, this, &ChessUIQt::OnSaveButtonClicked);
	connect(loadButton, &QPushButton::pressed, this, &ChessUIQt::OnLoadButtonClicked);
	connect(restartButton, &QPushButton::pressed, this, &ChessUIQt::OnRestartButtonClicked);
	connect(drawButton, &QPushButton::pressed, this, &ChessUIQt::OnDrawButtonClicked);
	connect(copyButton, &QPushButton::pressed, this, &ChessUIQt::OnCopyButtonClicked);

	buttonContainer->setLayout(btnGrid);
	mainGridLayout->addWidget(buttonContainer, 0, 0, 1, 1);
}

void ChessUIQt::InitializeTimers(QGridLayout* mainGridLayout)
{
	QWidget* timerContainer = new QWidget();
	QGridLayout* timerGrid = new QGridLayout();

	QLabel* blackTimerLbl = new QLabel("Black timer: ");
	m_BlackTimer = new QLabel("00:00:00");

	QPushButton* pauseTimerBtn = new QPushButton(" Pause | Resume");
	//TODO Create slot and connect button

	QLabel* whiteTimerLbl = new QLabel("    White timer: ");
	m_WhiteTimer = new QLabel("00:00:00");

	timerContainer->setFixedWidth(400);

	timerGrid->addWidget(blackTimerLbl, 0, 0);
	timerGrid->addWidget(m_BlackTimer, 0, 1);
	timerGrid->addWidget(pauseTimerBtn, 0, 2);
	timerGrid->addWidget(whiteTimerLbl, 0, 3);
	timerGrid->addWidget(m_WhiteTimer, 0, 4);

	timerContainer->setLayout(timerGrid);
	mainGridLayout->addWidget(timerContainer, 2, 0, 1, 2, Qt::AlignCenter);
}

void ChessUIQt::InitializeHistory(QGridLayout* mainGridLayout)
{
	m_MovesList = new QListWidget();
	m_MovesList->setMinimumWidth(250);
	m_MovesList->setMaximumWidth(350);
	connect(m_MovesList, &QListWidget::itemActivated, this, &ChessUIQt::OnHistoryClicked);
	mainGridLayout->addWidget(m_MovesList, 1, 0, 1, 1);
}

void ChessUIQt::InitializeBoard(QGridLayout* mainGridLayout)
{
	QGridLayout* chessGridLayout = new QGridLayout();

	QWidget* board = new QWidget();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			m_grid[i][j] = new GridButton({ i,j }, EType::EMPTY, EColor::NONE);
			chessGridLayout->addWidget(m_grid[i][j], i, j, 1, 1);
			chessGridLayout->setSpacing(0);
			connect(m_grid[i][j], &GridButton::Clicked, this, &ChessUIQt::OnButtonClicked);
		}
	}

	board->setStyleSheet("border: 1px solid gray;");
	board->setLayout(chessGridLayout);
	mainGridLayout->addWidget(board, 1, 1, 1, 1);
}

void ChessUIQt::OnButtonClicked(const std::pair<int, int>& position)
{
	//At second click
	if (m_selectedCell.has_value()) {
		Position start({ m_selectedCell.value().first , m_selectedCell.value().second });

		try
		{
			m_game->MovePiece(start, position);
			m_MessageLabel->setText(GetTurnMessage());

		}
		catch (OutOfBoundsException e)
		{
			m_MessageLabel->setText(GetTurnMessage() + "\n" + e.what());
		}
		catch (EmptyPositionException e)
		{
			m_MessageLabel->setText(GetTurnMessage() + "\n" + e.what());
		}
		catch (PieceNotFoundException e)
		{
			m_MessageLabel->setText(GetTurnMessage() + "\n" + e.what());
		}
		catch (IllegalMoveException e)
		{
			m_MessageLabel->setText(GetTurnMessage() + "\n" + e.what());
		}
		catch (CheckException e)
		{
			m_MessageLabel->setText(GetTurnMessage() + "\n" + e.what());
		}
		catch (GameOverException e)
		{
			m_MessageLabel->setText(e.what());
		}

		if (m_game->BlackWon())
			m_MessageLabel->setText("Black won the game!");
		else if (m_game->WhiteWon())
			m_MessageLabel->setText("White won the game!");
		else if (m_game->IsTie())
			m_MessageLabel->setText("Tie!");
		else if (m_game->IsPawnEvolving())
		{
			ShowPromoteOptions();
			m_MessageLabel->setText(GetTurnMessage());
		}

		UpdateBoard(m_game->GetBoard());
		m_grid[m_selectedCell.value().first][m_selectedCell.value().second]->setSelected(false);
		m_selectedCell.reset();
	}
	//At first click
	else 
	{
		m_selectedCell = position;
		m_grid[position.first][position.second]->setSelected(true);

		//TODO Show possible moves here
		HighlightPossibleMoves(m_game->GetMoves(position));
	}
}

void ChessUIQt::OnSaveButtonClicked()
{
	//TODO ...

}

void ChessUIQt::OnLoadButtonClicked()
{
	//TODO ...
}

void ChessUIQt::OnRestartButtonClicked()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Restart proposal", "Are you sure you want to restart??", QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes)
	{
		m_game = IGame::Produce();
		StartGame();
	}
}

void ChessUIQt::OnDrawButtonClicked()
{
	m_game->MakeTieRequest();
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Draw proposal", "Do you accept a draw?", QMessageBox::Yes | QMessageBox::No);

	if (reply == QMessageBox::Yes)
	{
		m_game->TieRequestResponse(true);
		m_MessageLabel->setText("Tie!");
	}
	else
		m_game->TieRequestResponse(false);

}

void ChessUIQt::OnCopyButtonClicked()
{
	QClipboard* clipboard = QGuiApplication::clipboard();
	QString config = "Game game({\n";
	MatrixPtr board = m_game->GetBoard();
	for (int row = 0; row < 8; row++)
	{
		config += QString("\t");
		for (int column = 0; column < 8; column++)
		{
			config += QString("'") + PieceToChar(board->GetElement({ row, column })) + QString("'");
			if (row != 7 || column != 7) config += ", ";
		}
		config += QString("\n");
	}
	config = config.removeLast();
	config += QString("\n}, ");
	config += GameTurnToString() + ", ";
	config += GameStateToString() + ");";
	clipboard->setText(config);
}

void ChessUIQt::OnHistoryClicked(QListWidgetItem* item)
{
	int index = m_MovesList->currentRow();
	
	//TODO ...
}

void ChessUIQt::UpdateHistory()
{
	m_MovesList->clear();

	//TODO modify me...
	int numMoves = 10;
	for (int i = 0; i < numMoves; i++) {
		m_MovesList->addItem("#1   Color: Black   Move: A1 A2");
	}
}

void ChessUIQt::UpdateBoard(const MatrixPtr& newBoard)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			m_grid[i][j]->setPiece(newBoard->GetElement({ i, j }));
			m_grid[i][j]->setSelected(false);
			m_grid[i][j]->setHighlighted(false);
		}
	}

}

void ChessUIQt::HighlightPossibleMoves(const PositionList& possibleMoves)
{
	for (const auto& position : possibleMoves) {
		m_grid[position.first][position.second]->setHighlighted(true);
	}
}

void ChessUIQt::StartGame()
{
	//TODO MODIFY ME OR DELETE ME
	m_MessageLabel->setText(GetTurnMessage());
	UpdateBoard(m_game->GetBoard());
}

void ChessUIQt::ShowPromoteOptions()
{
	QInputDialog dialog;
	QList<QString> options;
	options.append("Rook");
	options.append("Bishop");
	options.append("Queen");
	options.append("Horse");

	dialog.setComboBoxItems(options);
	dialog.setModal(true);

	bool ok;
	QString item = QInputDialog::getItem(this, tr("Pawn promote"),
		tr("Promote pawn to: "), options, 0, false, &ok);

	if (ok && !item.isEmpty())
	{
		//TODO
		m_game->EvolvePawn(item.toStdString());

		//TODO DELETE ME...
		QMessageBox notification;
		notification.setText("You selected " + item);
		notification.exec();
	}
}

QString ChessUIQt::GetTurnMessage()
{
	return m_game->GetTurn() == EColor::BLACK ? "Black turn" : "White turn";
}

QString ChessUIQt::GameTurnToString()
{
	QString turn = "EColor::";
	turn += m_game->GetTurn() == EColor::WHITE ? "WHITE" : "BLACK";
	return turn;
}

QString ChessUIQt::GameStateToString()
{
	QString state = "EGameState::";
	if (m_game->IsCheck())
		state += "Check";
	else if (m_game->IsTieRequest())
		state += "TieRequest";
	else if (m_game->IsPawnEvolving())
		state += "PawnEvolving";
	else if (m_game->IsTie())
		state += "Tie";
	else if (m_game->BlackWon())
		state += "BlackWon";
	else if (m_game->WhiteWon())
		state += "WhiteWon";
	else
		state += "Playing";
	return state;
}

char ChessUIQt::PieceToChar(IPiecePtr piece) const
{
	char pieceChar;
	if (!piece) return ' ';
	switch (piece->GetType())
	{
	case EType::ROOK:
		piece->GetColor() == EColor::WHITE ? pieceChar = 'R' : pieceChar = 'r';
		return pieceChar;
	case EType::HORSE:
		piece->GetColor() == EColor::WHITE ? pieceChar = 'H' : pieceChar = 'h';
		return pieceChar;
	case EType::BISHOP:
		piece->GetColor() == EColor::WHITE ? pieceChar = 'B' : pieceChar = 'b';
		return pieceChar;
	case EType::QUEEN:
		piece->GetColor() == EColor::WHITE ? pieceChar = 'Q' : pieceChar = 'q';
		return pieceChar;
	case EType::KING:
		piece->GetColor() == EColor::WHITE ? pieceChar = 'K' : pieceChar = 'k';
		return pieceChar;
	case EType::PAWN:
		piece->GetColor() == EColor::WHITE ? pieceChar = 'P' : pieceChar = 'p';
		return pieceChar;
	default:
		return ' ';
	}
}