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
	show();
	centerOnScreen();
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
	InitializePanel(mainGridLayout);
	InitializeTitleBar(mainGridLayout);
	mainWidget->setLayout(mainGridLayout);

	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	this->setCentralWidget(mainWidget);

}

void ChessUIQt::InitializeTitleBar(QGridLayout* mainGridLayout)
{

	// Title bar
	QWidget* titleBar = new QWidget();
	titleBar->setFixedHeight(40); // Set a fixed height for the title bar
	//titleBar->setStyleSheet("background-color: #333;"); // Set the background color for dark theme

	QGridLayout* titleBarGrid = new QGridLayout(titleBar);

	// Title text
	QLabel* title = new QLabel();
	title->setPixmap(QPixmap("res/logo.png"));
	QFont titleFont = title->font();
	titleFont.setPointSize(16);
	titleFont.setBold(true);
	title->setFont(titleFont);
	title->setStyleSheet("color: #FFF;"); // Set the text color for dark theme

	// Minimize button
	QPushButton* minimizeButton = new QPushButton(titleBar);
	minimizeButton->setFixedSize(30, 30); // Set a fixed size for the button
	minimizeButton->setIcon(QIcon("res/minimize.png")); // Set the custom icon
	minimizeButton->setStyleSheet(
		"QPushButton {"
		"   background-color: transparent;" // Normal background color
		"   border: none;"
		"}"
		"QPushButton:hover {"
		"   background-color: #4a5c56;" // Highlighted background color on hover
		"}"
	);
	connect(minimizeButton, &QPushButton::clicked, this, &QWidget::showMinimized);

	// Expand button
	m_expandButton = new QPushButton(titleBar);
	m_expandButton->setFixedSize(30, 30); // Set a fixed size for the button
	m_expandButton->setIcon(QIcon("res/expand.png")); // Set the custom icon
	m_expandButton->setStyleSheet(
		"QPushButton {"
		"   background-color: transparent;" // Normal background color
		"   border: none;"
		"}"
		"QPushButton:hover {"
		"   background-color: #4a5c56;" // Highlighted background color on hover
		"}"
	);
	connect(m_expandButton, &QPushButton::clicked, this, &ChessUIQt::toggleFullScreen);

	// Close button
	QPushButton* exitButton = new QPushButton(titleBar);
	exitButton->setFixedSize(30, 30); // Set a fixed size for the button
	exitButton->setIcon(QIcon("res/exit.png")); // Set the custom icon
	exitButton->setStyleSheet(
		"QPushButton {"
		"   background-color: transparent;" // Normal background color
		"   border: none;"
		"}"
		"QPushButton:hover {"
		"   background-color: #4a5c56;" // Highlighted background color on hover
		"}"
	);
	connect(exitButton, &QPushButton::clicked, this, &ChessUIQt::CloseApp);
	//	&QWidget::close

	// Status message label
	m_StatusMessage = new QLabel();
	m_StatusMessage->setStyleSheet("color: #FFF; font-size: 16px; font-weight: bold;"); // Set the text color for dark theme

	// Add widgets to the title bar layout
	titleBarGrid->addWidget(title, 0, 0);
	titleBarGrid->addWidget(m_StatusMessage, 0, 1);
	titleBarGrid->addWidget(minimizeButton, 0, 2);
	titleBarGrid->addWidget(m_expandButton, 0, 3);
	titleBarGrid->addWidget(exitButton, 0, 4);

	titleBarGrid->setSpacing(0);
	titleBarGrid->setContentsMargins(0, 0, 0, 0);


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

	playerPieces->setMinimumWidth(600);
	playerPieces->setFlow(QListWidget::LeftToRight);
	playerPieces->setStyleSheet("QListWidget::item, QListWidget{background-color:transparent; border: none;}");
	playerPieces->setMaximumHeight(40);
	playerPieces->setIconSize({ 30, 30 });
	playerPieces->setSpacing(0);

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
	button->setContentsMargins(0, 0, 0, 0);
	button->setIcon(ButtonIcon);
	button->setIconSize({40, 40});
	button->setStyleSheet("border: none; padding: 7px 7px; margin: 0px; margin: 10px 0px;");

	return *button;
}

QWidget* ChessUIQt::InitializeButtons()
{
	QWidget* buttonContainer = new QWidget;

	buttonContainer->setStyleSheet(
		"QPushButton {"
		"   background-color: #21201d;" // Normal background color
		"   color: white; "
		"}"
		"QPushButton:hover {"
		"   background-color: #d234eb;" // Highlighted background color on hover
		"}"
	);

	QPushButton* saveButton = new QPushButton();
	QPushButton* loadButton = new QPushButton();
	QPushButton* restartButton = new QPushButton();
	QPushButton* drawButton = new QPushButton();
	QPushButton* copyButton = new QPushButton();

	QGridLayout* btnGrid = new QGridLayout();


	SetIcon(saveButton, "res/save.png");
	SetIcon(loadButton, "res/load.png");
	SetIcon(restartButton, "res/restart.png");
	SetIcon(drawButton, "res/draw.png");
	SetIcon(copyButton, "res/copy.png");

	saveButton->setStyleSheet("border: none; padding: 7px 7px; margin: 0px; margin: 10px 0px; border-top-left-radius: 15px; border-bottom-left-radius: 15px;");
	copyButton->setStyleSheet("border: none; padding: 7px 7px; margin: 0px; margin: 10px 0px; border-top-right-radius: 15px; border-bottom-right-radius: 15px;");

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
	btnGrid->setContentsMargins(0, 0, 0, 0);

	buttonContainer->setLayout(btnGrid);
	return buttonContainer;
}

QWidget* ChessUIQt::InitializeTimers()
{
	QWidget* timerContainer = new QWidget();

	QGridLayout* timerGrid = new QGridLayout();
	timerGrid->setSpacing(0);
	timerGrid->setContentsMargins(0, 0, 0, 0);

	m_pauseTimerBtn = new QPushButton("START");
	connect(m_pauseTimerBtn, &QPushButton::pressed, this, &ChessUIQt::OnPauseButtonClicked);

	timerContainer->setStyleSheet(
		"QPushButton {"
		"   background-color: #21201d;" // Normal background color
		"   color: white; "
		"}"
		"QPushButton:hover {"
		"   background-color: #d234eb;" // Highlighted background color on hover
		"}"
		"font-family: Segoe UI;"
	);

	


	m_BlackTimer = new QLabel("00:00");
	m_BlackTimer->setStyleSheet("color: white; font-size: 25px; background-color: #21201d; border-top-left-radius: 15px;");
	m_BlackTimer->setAlignment(Qt::AlignCenter);

	m_WhiteTimer = new QLabel("00:00");
	m_WhiteTimer->setStyleSheet("color: white; font-size: 25px; background-color: #21201d; border-top-right-radius: 15px;");
	m_WhiteTimer->setAlignment(Qt::AlignCenter);
	

	m_pauseTimerBtn->setStyleSheet("border: none; padding: 7px 7px; font-size: 22px; width: 80px;");

	timerGrid->addWidget(m_BlackTimer, 0, 1, 1, 2);
	timerGrid->addWidget(m_pauseTimerBtn, 0, 3);
	timerGrid->addWidget(m_WhiteTimer, 0, 4, 1, 2);



	timerContainer->setLayout(timerGrid);
	return timerContainer;
}


QWidget* ChessUIQt::InitializeHistory()
{
	QWidget::adjustSize();
	m_MovesList = new QListWidget();
	m_MovesList->setSizeAdjustPolicy(QListWidget::AdjustToContents);

	m_MovesList->setContentsMargins(0, 0, 0, 0);
	m_MovesList->setSpacing(0);

	// Set a custom style for the history list
	m_MovesList->setStyleSheet(
		"QListWidget {"
		"   background-color: #262522;" // Set the background color for dark theme
		"   border: none;" // Add a thin border
		"   color: white;" // Set the text color to white
		"	border-bottom-left-radius: 15px;"
		"	border-bottom-right-radius: 15px;"
		"}"

		"QListWidget::item {"
		"   padding: 0px;" // Add padding to the list items
		"}"

		"QListWidget::item:hover {"
		"   background-color: #d234eb;" // Highlighted background color on hover
		"}"

		"QListWidget::item:selected {"
		"   background-color: #d234eb" // Highlighted background color on hover
		"}"

		"QListWidget QScrollBar:vertical {"
		"	border: none;"
		"	background: rgb(45, 45, 68);"
		"	width: 14px;"
		"	margin: 15px 0 15px 0;"
		"	border-radius: 0px;"
		"}"

		"QScrollBar::handle:vertical {	"
		"	background-color: rgb(80, 80, 122);"
		"	min-height: 30px;"
		"	border-radius: 7px;"
		"}"

		"QScrollBar::handle:vertical:hover{	"
		"	background-color: #d234eb;"
		"}"

		"QScrollBar::handle:vertical:pressed {	"
		"	background-color: #8e2b9e;"
		"}"

		"QScrollBar::sub-line:vertical {"
		"	border: none;"
		"	background-color: rgb(59, 59, 90);"
		"	height: 15px;"
		"	border-top-left-radius: 7px;"
		"	border-top-right-radius: 7px;"
		"	subcontrol-position: top;"
		"	subcontrol-origin: margin;"
		"}"

		"QScrollBar::sub-line:vertical:hover {	"
		"	background-color: #d234eb"
		"}"

		"QScrollBar::sub-line:vertical:pressed {	"
		"	background-color: #8e2b9e;"
		"}"

		"QScrollBar::add-line:vertical {"
		"	border: none;"
		"	background-color: rgb(59, 59, 90);"
		"	height: 15px;"
		"	border-bottom-left-radius: 7px;"
		"	border-bottom-right-radius: 7px;"
		"	subcontrol-position: bottom;"
		"	subcontrol-origin: margin;"
		"}"

		"QScrollBar::add-line:vertical:hover {	"
		"	background-color: #d234eb"
		"}"
		"QScrollBar::add-line:vertical:pressed {	"
		"	background-color: #8e2b9e;"
		"}"

		"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
		"	background: none;"
		"}"

		"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
		"	background: none;"
		"}"

	);

	QFont listFont;
	listFont.setFamily("Segoe UI");
	listFont.setPointSize(20);
	m_MovesList->setFont(listFont); 
	

	connect(m_MovesList, &QListWidget::itemActivated, this, &ChessUIQt::OnHistoryClicked);

	return m_MovesList;
}

void ChessUIQt::InitializePanel(QGridLayout* mainGridLayout)
{
	QWidget* container = new QWidget;

	QGridLayout* layout = new QGridLayout();

	QWidget* buttons = InitializeButtons();
	QWidget* timers = InitializeTimers();
	QWidget* history = InitializeHistory();

	layout->addWidget(buttons, 0, 0);
	layout->addWidget(timers, 1, 0);
	layout->addWidget(history, 2, 0);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	container->setLayout(layout);
	container->setContentsMargins(0, 0, 0, 0);

	mainGridLayout->addWidget(container, 1, 1, 2, 1);
}

void ChessUIQt::InitializeBoard(QGridLayout* mainGridLayout)
{
	QGridLayout* chessGridLayout = new QGridLayout();
	chessGridLayout->setSpacing(0);
	chessGridLayout->setContentsMargins(0, 0, 0, 0);

	QWidget* board = new QWidget();


	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			m_grid[row][column] = new GridButton({ row,column }, EType::EMPTY, EColor::NONE);
			chessGridLayout->addWidget(m_grid[row][column], row, column, 1, 1);
			connect(m_grid[row][column], &GridButton::Clicked, this, &ChessUIQt::OnButtonClicked);
		}
	}
	board->setLayout(chessGridLayout);
	mainGridLayout->addWidget(board, 2, 0);
}

void ChessUIQt::OnButtonClicked(const Position& position)
{
	//At second click
	if (m_selectedCell.has_value()) {
		Position start({ m_selectedCell.value().first , m_selectedCell.value().second });

		auto possibleMoves = m_game->Status()->GetMoves(start);
		try
		{
			std::string source, target, turn;
			m_game->MovePiece(start, position);
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

		HighlightPossibleMoves(m_game->Status()->GetMoves(position));
	}
}

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

		m_game->SaveFEN(filePath.toStdString());

	}
	else if (saveOptionDialog.clickedButton() == saveAsPgnButton) {
		// Save as PGN
		QString defaultFileName = "Chess game.pgn";
		QString desktopPath = QDir::homePath() + "/Downloads";
		QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", desktopPath + "/" + defaultFileName, "PGN Files (*.pgn)");

		m_game->SavePGN(filePath.toStdString());
	}
	else if (saveOptionDialog.clickedButton() == cancelButton) {
		// User clicked Cancel, do nothing or handle it as required
	}
}


void ChessUIQt::OnLoadButtonClicked()
{
	auto status = m_game->Status();
	QString desktopPath = QDir::homePath() + "/Downloads";
	QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", desktopPath, "PGN Files(*.pgn);; FEN Files(*.fen);;All Files (*)");

	m_whitePieces->clear();
	m_blackPieces->clear();
	m_MovesList->clear();

	bool success = m_game->LoadFromFormat(filePath.toStdString());
		
	
	QString pieces[] = { "p", "r", "b", "h", "q", "k", "empty" };


	TypeList whitePieces = m_game->Status()->GetMissingPieces(EColor::BLACK);
	TypeList blackPieces = m_game->Status()->GetMissingPieces(EColor::WHITE);

	for (auto& pieceType : whitePieces)
	{
		QListWidgetItem* capturedPiece = new QListWidgetItem();
		QString imagePath = "res/b";
		imagePath.push_back(QString(pieces[(int)pieceType] + ".png"));
		QPixmap pixmap(imagePath);
		capturedPiece->setIcon(QIcon(pixmap));
		m_whitePieces->addItem(capturedPiece);
	}
	for (auto& pieceType : blackPieces)
	{
		QListWidgetItem* capturedPiece = new QListWidgetItem();
		QString imagePath = "res/w";
		imagePath.push_back(QString(pieces[(int)pieceType] + ".png"));
		QPixmap pixmap(imagePath);
		capturedPiece->setIcon(QIcon(pixmap));
		m_blackPieces->addItem(capturedPiece);
	}

	// Create history list
	MovesList moves = m_game->Status()->GetMovesList();
	
	int color = -1;
	for (auto& move : moves)
	{
		QListWidgetItem* item = new QListWidgetItem();
		QWidget* design = FromMatrixToChessMove(move.first, move.second, ++color % 2);
		m_MovesList->addItem(item);
		m_MovesList->setItemWidget(item, design);
	}

	if (status->IsGameOver())
		OnGameOver();

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

void ChessUIQt::OnPauseButtonClicked()
{
	if (!m_game->Status()->IsStarted())
	{
		m_game->Start();
		m_pauseTimerBtn->setText("PAUSE");
		return;
	}

	if (m_game->Status()->IsPaused())
	{
		m_game->Resume();
		m_pauseTimerBtn->setText("PAUSE");
	}
	else
	{
		m_game->Pause();
		m_pauseTimerBtn->setText("RESUME");
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
	MatrixPtr board = m_game->Status()->GetBoard();
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

void ChessUIQt::BoardLock(bool disabled)
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			m_grid[row][column]->setEnabled(disabled);
		}
	}
}

void ChessUIQt::OnHistoryClicked(QListWidgetItem* item)
{
	int index = m_MovesList->currentRow();
	if (index == m_MovesList->count() - 1)
		BoardLock(true);
	else
		BoardLock(false);

	m_game->PreviewPastConfig(index-1);
	UpdateBoard();
	
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

QWidget* ChessUIQt::FromMatrixToChessMove(Position start, Position end, int color)
{
	EColor turnColor = m_game->Status()->GetTurn();
	if (color == 0)
		turnColor = EColor::WHITE;
	else if (color == 1)
		turnColor = EColor::BLACK;

	std::string turn = turnColor == EColor::WHITE ? "Black" : "White";

	static QPixmap pixmap_white = QPixmap("res/white.png").scaled(30, 30);
	static QPixmap pixmap_black = QPixmap("res/black.png").scaled(30, 30);

	QLabel* turnPicture = new QLabel();
	turnPicture->setPixmap(turnColor == EColor::WHITE ? pixmap_white : pixmap_black);
	turnPicture->setStyleSheet("border: 1px solid black; padding: 0px; margin: 0px;");

	std::string source;
	source += toupper('a' + start.second);
	source += toupper('1' + (7 - start.first));

	QLabel* initialPos = new QLabel(QString::fromStdString(source));
	initialPos->setStyleSheet("color: white; font-family: Segoe UI; font-weight: bold; font-size: 18px; padding: 0px; margin: 0px;");
	
	static QPixmap pixmap = QPixmap("res/arrow.png").scaled(30, 30);

	QLabel* arrow = new QLabel();
	arrow->setPixmap(pixmap);
	arrow->setStyleSheet("border: none; padding: 0px; margin: 0px;");

	std::string target;
	target += toupper('a' + end.second);
	target += toupper('1' + (7 - end.first));
	QLabel* targetPos = new QLabel(QString::fromStdString(target));
	targetPos->setStyleSheet("color: white; font-family: Segoe UI; font-weight: bold; font-size: 18px; padding: 0px; margin: 0px;");

	QGridLayout* layout = new QGridLayout;
	layout->addWidget(turnPicture, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
	layout->addWidget(initialPos, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);
	layout->addWidget(arrow, 0, 2, Qt::AlignLeft | Qt::AlignVCenter);
	layout->addWidget(targetPos, 0, 3, Qt::AlignLeft | Qt::AlignVCenter);

	QWidget* item = new QWidget();
	item->setStyleSheet("background: transparent; padding: 0px; margin: 0px;");
	item->setLayout(layout);


	return item;
}

void ChessUIQt::toggleFullScreen()
{
	if (isFullScreen())
	{
		showNormal();
		m_expandButton->setIcon(QIcon("res/expand.png"));
	}
	else
	{
		showFullScreen();
		m_expandButton->setIcon(QIcon("res/restore.png"));
	}
}

void ChessUIQt::CloseApp()
{
	m_game->Stop();
	QWidget::close();
}

void ChessUIQt::centerOnScreen()
{
	// Get the available screen geometry
	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->availableGeometry();

	// Calculate the position to center the window on the screen
	int x = (screenGeometry.width() - width()) / 2;
	int y = (screenGeometry.height() - height()) / 2;

	// Set the window position
	move(x, y);
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
			m_grid[i][j]->setPiece(m_game->Status()->GetBoard()->GetElement({ i, j }));
			m_grid[i][j]->setSelected(false);
			m_grid[i][j]->setHighlighted(EHighlight::NONE);
		}
	}
	if (!m_game->Status()->IsGameOver())
		m_StatusMessage->setText(GetTurnMessage());
}

void ChessUIQt::HighlightPossibleMoves(const PositionList& possibleMoves)
{
	for (const auto& position : possibleMoves) 
	{
		auto possibleMove = m_grid[position.first][position.second];
		if (m_game->Status()->GetBoard()->GetElement(position))
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
	do
	{
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
	} while (ok == false);
}

QString ChessUIQt::GetTurnMessage()
{
	return m_game->Status()->GetTurn() == EColor::BLACK ? "Black's turn\n" : "White's turn\n";
}

QString ChessUIQt::GameTurnToString()
{
	QString turn = "EColor::";
	turn += m_game->Status()->GetTurn() == EColor::WHITE ? "WHITE" : "BLACK";
	return turn;
}

QString ChessUIQt::GameStateToString()
{
	auto status = m_game->Status();
	QString state = "EGameState::";
	if (status->IsCheck())
		state += "Check";
	else if (status->IsTieRequest())
		state += "TieRequest";
	else if (status->IsPawnEvolving())
		state += "PawnEvolving";
	else if (status->IsTie())
		state += "Tie";
	else if (status->BlackWon())
		state += "BlackWon";
	else if (status->WhiteWon())
		state += "WhiteWon";
	else
		state += "Playing";
	return state;
}

void ChessUIQt::OnGameOver()
{
	auto status = m_game->Status();
	if (status->BlackWon())
		m_StatusMessage->setText("Black won the game!\n");
	else if (status->WhiteWon())
		m_StatusMessage->setText("White won the game!\n");
	else if (status->IsTie())
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
	auto status = m_game->Status();
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

	QListWidgetItem* item = new QListWidgetItem();
	QWidget* design = FromMatrixToChessMove(start, end);
	m_MovesList->addItem(item);
	m_MovesList->setItemWidget(item, design);
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
	QListWidget* playerPieces;
	pieceColor == EColor::BLACK ? playerPieces = m_whitePieces : playerPieces = m_blackPieces;

	QListWidgetItem* capturedPiece = new QListWidgetItem();
	QString imagePath;
	pieceColor == EColor::BLACK ? imagePath = "res/b" : imagePath = "res/w";
	QString pieces[] = {"p", "r", "b", "h", "q", "k", "empty"};
	imagePath.push_back(QString(pieces[(int)pieceType] + ".png"));
	QPixmap pixmap(imagePath);
	QIcon icon(pixmap);
	capturedPiece->setIcon(QIcon(pixmap));
	
	playerPieces->addItem(capturedPiece);
}

void ChessUIQt::SetGame(IGamePtr game)
{
	m_game = game;
}

static QString ConvertTime(int seconds)
{
	QString timeString = "";

	timeString.push_back(QString::number(seconds/60));
	timeString.push_back(":");
	if (seconds % 60 < 10)
		timeString.push_back("0");
	timeString.push_back(QString::number(seconds%60));

	return timeString;
}

void ChessUIQt::OnTimerTick(TimeSeconds whiteTimer, TimeSeconds blackTimer)
{
	m_WhiteTimer->setText(ConvertTime(whiteTimer.count()));
	m_BlackTimer->setText(ConvertTime(blackTimer.count()));
	qDebug() << whiteTimer.count() << " " << blackTimer.count();
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