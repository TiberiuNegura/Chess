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
	mainWidget->setStyleSheet("background-color: #302e2b;");
	InitializeBoard(mainGridLayout);
	InitializePlayers(mainGridLayout, EColor::BLACK);
	InitializePlayers(mainGridLayout, EColor::WHITE);
	InitializeButtons(mainGridLayout);
	InitializeHistory(mainGridLayout);
	InitializeTitleBar(mainGridLayout);
	mainWidget->setLayout(mainGridLayout);

	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	//resize(size() * 1.8);
	this->setCentralWidget(mainWidget);
}

void ChessUIQt::InitializeTitleBar(QGridLayout* mainGridLayout)
{
	// Title bar
	QWidget* titleBar = new QWidget();
	titleBar->setFixedHeight(40); // Set a fixed height for the title bar
	titleBar->setStyleSheet("background-color: #333;"); // Set the background color for dark theme

	QGridLayout* titleBarGrid = new QGridLayout(titleBar);

	// Title text
	QLabel* title = new QLabel("Chess Game");
	QFont titleFont = title->font();
	titleFont.setPointSize(16);
	titleFont.setBold(true);
	title->setFont(titleFont);
	title->setStyleSheet("color: #FFF;"); // Set the text color for dark theme

	// Minimize button
	QPushButton* minimizeButton = new QPushButton(titleBar);
	minimizeButton->setFixedSize(30, 30); // Set a fixed size for the button
	minimizeButton->setIcon(QIcon("res/minimize.png")); // Set the custom icon
	minimizeButton->setIconSize(QSize(30, 30)); // Set the icon size
	minimizeButton->setStyleSheet(
		"QPushButton {"
		"   background-color: transparent;" // Normal background color
		"}"
		"QPushButton:hover {"
		"   background-color: #4a5c56;" // Highlighted background color on hover
		"}"
	);
	connect(minimizeButton, &QPushButton::clicked, this, &QWidget::showMinimized);

	// Expand button
	QPushButton* expandButton = new QPushButton(titleBar);
	expandButton->setFixedSize(30, 30); // Set a fixed size for the button
	expandButton->setIcon(QIcon("res/expand.png")); // Set the custom icon
	expandButton->setIconSize(QSize(30, 30)); // Set the icon size
	expandButton->setStyleSheet(
		"QPushButton {"
		"   background-color: transparent;" // Normal background color
		"}"
		"QPushButton:hover {"
		"   background-color: #4a5c56;" // Highlighted background color on hover
		"}"
	);
	connect(expandButton, &QPushButton::clicked, this, &QWidget::showFullScreen);

	// Close button
	QPushButton* exitButton = new QPushButton(titleBar);
	exitButton->setFixedSize(30, 30); // Set a fixed size for the button
	exitButton->setIcon(QIcon("res/exit.png")); // Set the custom icon
	exitButton->setIconSize(QSize(30, 30)); // Set the icon size
	exitButton->setStyleSheet(
		"QPushButton {"
		"   background-color: transparent;" // Normal background color
		"}"
		"QPushButton:hover {"
		"   background-color: #4a5c56;" // Highlighted background color on hover
		"}"
	);
	connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

	// Status message label
	m_StatusMessage = new QLabel();
	m_StatusMessage->setStyleSheet("color: #FFF; font-size: 14px;"); // Set the text color for dark theme

	// Add widgets to the title bar layout
	titleBarGrid->addWidget(title, 0, 0);
	titleBarGrid->addWidget(m_StatusMessage, 0, 1);
	titleBarGrid->addWidget(minimizeButton, 0, 2);
	titleBarGrid->addWidget(expandButton, 0, 3);
	titleBarGrid->addWidget(exitButton, 0, 4);

	// Set spacing and margins
	titleBarGrid->setSpacing(10);
	titleBarGrid->setContentsMargins(10, 0, 10, 0);

	// Add the title bar to the mainGridLayout
	mainGridLayout->addWidget(titleBar, 0, 0, 1, 2);
}


void ChessUIQt::InitializePlayers(QGridLayout * mainGridLayout, EColor color)
{
	QString path, name;
	color == EColor::BLACK ? path = "res/black.png" : path = "res/white.png";
	color == EColor::BLACK ? name = "Black" : name = "White";


	QWidget* player = new QWidget();
	QGridLayout* playerGrid = new QGridLayout();

	QLabel* profilePicture = new QLabel();
	QPixmap pic(path);
	profilePicture->setPixmap(pic.scaled(60, 60));
	


	QLabel* profileName = new QLabel();
	profileName->setText(name);
	profileName->setStyleSheet("color: white; font-size: 18px; font-weight: bold;");

	if (color == EColor::BLACK)
		m_blackPieces = new QListWidget();
	else
		m_whitePieces = new QListWidget();

	QListWidget* playerPieces;
	color == EColor::BLACK ? playerPieces = m_blackPieces : playerPieces = m_whitePieces;
	playerPieces->setFlow(QListWidget::LeftToRight);
	playerPieces->setStyleSheet("QListWidget::item, QListWidget{background-color:transparent; border: none;}");
	playerPieces->setMaximumHeight(20);

	
	playerGrid->addWidget(profilePicture, 0, 0, 2, 1);
	playerGrid->addWidget(profileName, 0, 1, Qt::AlignTop);
	playerGrid->addWidget(playerPieces, 1, 1, Qt::AlignCenter);


	player->setLayout(playerGrid);
	if (color == EColor::BLACK)
		mainGridLayout->addWidget(player, 1, 0, Qt::AlignLeft);
	else 
		mainGridLayout->addWidget(player, 3, 0, Qt::AlignLeft);


}

QPushButton& SetIcon(QPushButton* button, QString path)
{
	QPixmap pixmap(path);
	QIcon ButtonIcon(pixmap);
	button->setIcon(ButtonIcon);
	button->setIconSize({40, 40});
	button->setStyleSheet("border: none; margin: 4px 2px; padding: 7px 7px;");

	return *button;
}

void ChessUIQt::InitializeButtons(QGridLayout* mainGridLayout)
{
	QPushButton* saveButton = new QPushButton();
	QPushButton* loadButton = new QPushButton();
	QPushButton* restartButton = new QPushButton();
	QPushButton* drawButton = new QPushButton();
	QPushButton* copyButton = new QPushButton();

	QWidget* buttonContainer = new QWidget();
	buttonContainer->setStyleSheet(
		"QPushButton {"
		"   background-color: #21201d;" // Normal background color
		"   color: white; "
		"}"
		"QPushButton:hover {"
		"   background-color: #d234eb;" // Highlighted background color on hover
		"}"
	);
	QGridLayout* btnGrid = new QGridLayout();


	SetIcon(saveButton, "res/save.png");
	SetIcon(loadButton, "res/load.png");
	SetIcon(restartButton, "res/restart.png");
	SetIcon(drawButton, "res/draw.png");
	SetIcon(copyButton, "res/copy.png");

	btnGrid->addWidget(saveButton, 0, 0);
	btnGrid->addWidget(loadButton, 0, 1);
	btnGrid->addWidget(restartButton, 0, 2);
	btnGrid->addWidget(drawButton, 0, 3);
	btnGrid->addWidget(copyButton, 0, 4);
	

	connect(saveButton, &QPushButton::pressed, this, &ChessUIQt::OnSaveButtonClicked);
	connect(loadButton, &QPushButton::pressed, this, &ChessUIQt::OnLoadButtonClicked);
	connect(restartButton, &QPushButton::pressed, this, &ChessUIQt::OnRestartButtonClicked);
	connect(drawButton, &QPushButton::pressed, this, &ChessUIQt::OnDrawButtonClicked);
	connect(copyButton, &QPushButton::pressed, this, &ChessUIQt::OnCopyButtonClicked);

	btnGrid->setSpacing(0);
	buttonContainer->setLayout(btnGrid);
	mainGridLayout->addWidget(buttonContainer, 1, 1);
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
	mainGridLayout->addWidget(timerContainer, 2, 0, Qt::AlignCenter);
}

void ChessUIQt::InitializeHistory(QGridLayout* mainGridLayout)
{
	m_MovesList = new QListWidget();
	m_MovesList->setMinimumWidth(100);
	m_MovesList->setMaximumWidth(350);

	// Set a custom style for the history list
	m_MovesList->setStyleSheet(
		"QListWidget {"
		"   background-color: #262522;" // Set the background color for dark theme
		"   border: 1px solid #555555;" // Add a thin border
		"   color: white;" // Set the text color to white
		"}"
		"QListWidget::item {"
		"   padding: 5px;" // Add padding to the list items
		"}"
		"QListWidget::item:hover {"
		"   background-color: #4a5c56;" // Highlighted background color on hover
		"}"
	);

	QFont listFont;
	listFont.setFamily("Arial");
	listFont.setPointSize(12);
	m_MovesList->setFont(listFont);

	connect(m_MovesList, &QListWidget::itemActivated, this, &ChessUIQt::OnHistoryClicked);
	mainGridLayout->addWidget(m_MovesList, 2, 1);
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

	board->setStyleSheet("border: none;");
	board->setLayout(chessGridLayout);
	mainGridLayout->addWidget(board, 2, 0);
}

void ChessUIQt::OnButtonClicked(const std::pair<int, int>& position)
{
	//At second click
	if (m_selectedCell.has_value()) {
		Position start({ m_selectedCell.value().first , m_selectedCell.value().second });

		auto possibleMoves = m_game->GetMoves(start);
		try
		{
			std::string source, target, turn;
			turn = m_game->GetTurn() == EColor::WHITE ? "White" : "Black";
			m_game->MovePiece(start, position);
			m_MovesList->addItem(FromMatrixToChessMove(start, position));
		}
		catch (OutOfBoundsException e)
		{
		}
		catch (EmptyPositionException e)
		{
		}
		catch (PieceNotFoundException e)
		{
		}
		catch (IllegalMoveException e)
		{
		}
		catch (CheckException e)
		{
			OnCheck(e.what());
		}
		catch (GameOverException e)
		{

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

//void ChessUIQt::OnSaveButtonClicked()
//{
//	QString defaultFileName = "Chess game.txt";
//	QString desktopPath = QDir::homePath() + "/Downloads";
//	QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", desktopPath + "/" + defaultFileName, "Text Files (*.txt);;All Files (*)");
//
//	QFile newFile(filePath);
//	if(!newFile.open(QIODevice::WriteOnly | QIODevice::Text))
//		return;
//
//	QTextStream outStream(&newFile);
//	outStream << QString::fromStdString(m_game->GetFenString());
//
//	newFile.close();
//}

void ChessUIQt::OnSaveButtonClicked()
{
	QMessageBox saveOptionDialog;
	saveOptionDialog.setWindowTitle("Save Game");
	saveOptionDialog.setText("Choose how to save the game:");
	saveOptionDialog.setIcon(QMessageBox::Question);

	// Add custom buttons for FEN and PGN options
	QPushButton* saveAsFenButton = saveOptionDialog.addButton("Save as FEN", QMessageBox::AcceptRole);
	QPushButton* saveAsPgnButton = saveOptionDialog.addButton("Save as PGN", QMessageBox::AcceptRole);
	QPushButton* cancelButton = saveOptionDialog.addButton("Cancel", QMessageBox::RejectRole);

	// Execute the dialog and wait for user input
	saveOptionDialog.exec();

	// Check which button was clicked and perform the corresponding action
	if (saveOptionDialog.clickedButton() == saveAsFenButton) {
		// Save as FEN
		QString defaultFileName = "Chess game.fen";
		QString desktopPath = QDir::homePath() + "/Downloads";
		QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", desktopPath + "/" + defaultFileName, "FEN Files (*.fen)");

		if (!filePath.isEmpty()) {
			QFile newFile(filePath);
			if (!newFile.open(QIODevice::WriteOnly | QIODevice::Text))
				return;

			QTextStream outStream(&newFile);
			outStream << QString::fromStdString(m_game->GetFenString());

			newFile.close();
		}
	}
	else if (saveOptionDialog.clickedButton() == saveAsPgnButton) {
		// Save as PGN
		QString defaultFileName = "Chess game.pgn";
		QString desktopPath = QDir::homePath() + "/Downloads";
		QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", desktopPath + "/" + defaultFileName, "PGN Files (*.pgn)");

		if (!filePath.isEmpty()) {
			QFile newFile(filePath);
			if (!newFile.open(QIODevice::WriteOnly | QIODevice::Text))
				return;

			QTextStream outStream(&newFile);
			outStream << QString::fromStdString(m_game->GetPGN());

			newFile.close();
		}
	}
	else if (saveOptionDialog.clickedButton() == cancelButton) {
		// User clicked Cancel, do nothing or handle it as required
	}
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


	m_game->Restart();
	if (m_game)
		m_game->RemoveListener(this);
	m_whitePieces->clear();
	m_blackPieces->clear();
	m_MovesList->clear();
	
	m_game = IGame::Produce(line.toStdString());
	m_game->AddListener(shared_from_this());


	TypeList whitePieces = m_game->GetBlackMissingPieces();
	TypeList blackPieces = m_game->GetWhiteMissingPieces();
	QString pieces[] = { "p", "r", "b", "h", "q", "k", "empty" };
	QListWidgetItem* capturedPiece = new QListWidgetItem();

	QString imagePath = "res/b";
	for (auto& pieceType : whitePieces)
	{
		imagePath.push_back(QString(pieces[(int)pieceType] + ".png"));
		QPixmap pixmap(imagePath);
		capturedPiece->setIcon(QIcon(pixmap));
		m_whitePieces->addItem(capturedPiece);
	}

	imagePath = "res/w";
	for (auto& pieceType : blackPieces)
	{
		imagePath.push_back(QString(pieces[(int)pieceType] + ".png"));
		QPixmap pixmap(imagePath);
		capturedPiece->setIcon(QIcon(pixmap));
		m_blackPieces->addItem(capturedPiece);
	}

	UpdateBoard();
}

void ChessUIQt::OnRestartButtonClicked()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Restart proposal", "Are you sure you want to restart?", QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes)
	{
		m_game->Restart();
		m_MovesList->clear();
		m_whitePieces->clear();
		m_blackPieces->clear();	
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

void ChessUIQt::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		// Store the initial position of the mouse relative to the window
		m_dragStartPos = event->globalPos() - frameGeometry().topLeft();
	}
}

void ChessUIQt::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton) {
		// Calculate the new position of the window based on the mouse movement
		move(event->globalPos() - m_dragStartPos);
	}
}

QString ChessUIQt::FromMatrixToChessMove(Position start, Position end) const
{
	std::string source, target, turn;
	turn = m_game->GetTurn() == EColor::WHITE ? "White" : "Black";

	source += toupper('a' + start.second);
	source += toupper('1' + (7 - start.first));
	
	target += toupper('a' + end.second);
	target += toupper('1' + (7 - end.first));
	
	std::string output = turn + ": " + source + " -> " + target;
	return QString::fromStdString(output);
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
	if (!m_game->IsGameOver())
		m_StatusMessage->setText(GetTurnMessage());
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
		m_StatusMessage->setText("Black won the game!\n");
	else if (m_game->WhiteWon())
		m_StatusMessage->setText("White won the game!\n");
	else if (m_game->IsTie())
		m_StatusMessage->setText("Tie!");
}

void ChessUIQt::OnCheck(std::string msg)
{
	QString s = GetTurnMessage();
	s.append(msg);	
}

void ChessUIQt::OnPawnEvolve()
{
	ShowPromoteOptions();
}

void ChessUIQt::OnTieRequest()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Draw proposal", "Do you accept a draw?", QMessageBox::Yes | QMessageBox::No);

	if (reply == QMessageBox::Yes)
	{
		m_game->TieRequestResponse(true);
		m_StatusMessage->setText("Tie!");
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


void ChessUIQt::OnPieceCapture(EType pieceType, EColor pieceColor)
{
	qDebug() << (int)pieceColor;
	QListWidget* playerPieces;
	pieceColor == EColor::BLACK ? playerPieces = m_whitePieces : playerPieces = m_blackPieces;

	QListWidgetItem* capturedPiece = new QListWidgetItem();
	QString imagePath;
	pieceColor == EColor::BLACK ? imagePath = "res/b" : imagePath = "res/w";
	QString pieces[] = {"p", "r", "b", "h", "q", "k", "empty"};
	imagePath.push_back(QString(pieces[(int)pieceType] + ".png"));
	QPixmap pixmap(imagePath);
	capturedPiece->setIcon(QIcon(pixmap));
	
	playerPieces->addItem(capturedPiece);
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