#include "ChessUIQt.h"
#include "ChessUIQt.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QtWidgets/QApplication>
#include <QDebug>
#include <QFileDialog>

ChessUIQt::ChessUIQt(QWidget *parent)
	: QMainWindow(parent)
{
	QGridLayout* mainGridLayout = new QGridLayout();
	Init(mainGridLayout);
}

ChessUIQt::~ChessUIQt()
{
	//No delete?
	//https://doc.qt.io/qt-6/objecttrees.html
}

void ChessUIQt::Init(QGridLayout* mainGridLayout)
{
	//Widget containing everything
	QWidget* mainWidget = new QWidget();
	InitializeBoard(mainGridLayout);
	InitializeMessage(mainGridLayout);
	InitializeButtons(mainGridLayout);
	InitializeTimers(mainGridLayout);
	InitializeHistory(mainGridLayout);
	mainWidget->setLayout(mainGridLayout);
	this->setCentralWidget(mainWidget);
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

	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			m_grid[row][column] = new GridButton({ row,column }, EType::EMPTY, EColor::NONE);
			chessGridLayout->addWidget(m_grid[row][column], row, column, 1, 1);
			chessGridLayout->setSpacing(0);
			connect(m_grid[row][column], &GridButton::Clicked, this, &ChessUIQt::OnButtonClicked);
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

		auto possibleMoves = m_game->GetMoves(start);
		try
		{
			m_game->MovePiece(start, position);
			m_MessageLabel->setText(GetTurnMessage());

		}
		catch (OutOfBoundsException e)
		{
			m_MessageLabel->setText(GetTurnMessage() + e.what());
		}
		catch (EmptyPositionException e)
		{
			m_MessageLabel->setText(GetTurnMessage() + e.what());
		}
		catch (PieceNotFoundException e)
		{
			m_MessageLabel->setText(GetTurnMessage() + e.what());
		}
		catch (IllegalMoveException e)
		{
			m_MessageLabel->setText(GetTurnMessage() + e.what());
		}
		catch (CheckException e)
		{
			OnCheck(e.what());
		}
		catch (GameOverException e)
		{
			m_MessageLabel->setText(e.what());
		}
		UpdateBoard();
		m_grid[m_selectedCell.value().first][m_selectedCell.value().second]->setSelected(false);
		m_selectedCell.reset();
	}
	else 
	{
		UpdateBoard();
		m_selectedCell = position;
		m_grid[position.first][position.second]->setSelected(true);

		HighlightPossibleMoves(m_game->GetMoves(position));
	}
}

void ChessUIQt::OnSaveButtonClicked()
{
	QString defaultFileName = "Chess game.txt";
	QString desktopPath = QDir::homePath() + "/Downloads";
	QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", desktopPath + "/" + defaultFileName, "Text Files (*.txt);;All Files (*)");

	QFile newFile(filePath);
	if(!newFile.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream outStream(&newFile);
	outStream << QString::fromStdString(m_game->GetFenString());

	newFile.close();
}

void ChessUIQt::OnLoadButtonClicked()
{
	QString desktopPath = QDir::homePath() + "/Downloads";
	QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", desktopPath, "Text Files (*.txt);;All Files (*)");
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream in(&file);
	QString line = in.readLine();
	m_game = IGame::Produce(line.toStdString());
	UpdateBoard();

}

void ChessUIQt::OnRestartButtonClicked()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Restart proposal", "Are you sure you want to restart??", QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes)
	{
		m_game->Restart();
		UpdateBoard();
	}
	
}

void ChessUIQt::OnDrawButtonClicked()
{
	m_game->MakeTieRequest();
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

void ChessUIQt::UpdateBoard()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			m_grid[i][j]->setPiece(m_game->GetBoard()->GetElement({ i, j }));
			m_grid[i][j]->setSelected(false);
			m_grid[i][j]->setHighlighted(EHighlight::NONE);
		}
	}
	m_MessageLabel->setText(GetTurnMessage());
}

void ChessUIQt::HighlightPossibleMoves(const PositionList& possibleMoves)
{
	for (const auto& position : possibleMoves) 
	{
		auto possibleMove = m_grid[position.first][position.second];
		if (m_game->GetBoard()->GetElement(position))
			possibleMove->setHighlighted(EHighlight::OCCUPIED_POS); // highlight opponent piece
		else
			possibleMove->setHighlighted(EHighlight::EMPTY_POS); // highlight empty 
	}
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
		if (item == "Rook")
			m_game->EvolvePawn(EType::ROOK);
		else if (item == "Bishop")
			m_game->EvolvePawn(EType::BISHOP);
		else if (item == "Queen")
			m_game->EvolvePawn(EType::QUEEN);
		else if (item == "Horse")
			m_game->EvolvePawn(EType::HORSE);

		QMessageBox notification;
		notification.setText("You selected " + item);
		notification.exec();
	}
}

QString ChessUIQt::GetTurnMessage()
{
	return m_game->GetTurn() == EColor::BLACK ? "Black's turn\n" : "White's turn\n";
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

void ChessUIQt::OnGameOver()
{
	if (m_game->BlackWon())
		m_MessageLabel->setText("Black won the game!\n");
	else if (m_game->WhiteWon())
		m_MessageLabel->setText("White won the game!\n");
	else if (m_game->IsTie())
		m_MessageLabel->setText("Tie!");
}

void ChessUIQt::OnCheck(std::string msg)
{
	QString s = GetTurnMessage();
	s.append(msg);	
	m_MessageLabel->setText(s);
}

void ChessUIQt::OnPawnEvolve()
{
	ShowPromoteOptions();
	m_MessageLabel->setText(GetTurnMessage());
}

void ChessUIQt::OnTieRequest()
{
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


void ChessUIQt::OnMovePiece(Position start, Position end)
{
	UpdateBoard();
}

void ChessUIQt::OnRestart()
{
	QGridLayout* mainGridLayout = new QGridLayout();
	Init(mainGridLayout);
	UpdateBoard();
}

void ChessUIQt::SetGame(IGamePtr game)
{
	m_game = game;
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