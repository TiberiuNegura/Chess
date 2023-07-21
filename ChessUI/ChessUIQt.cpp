#include "ChessUIQt.h"
#include "ChessUIQt.h"
#include <QInputDialog>
#include <QMessageBox>


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
    m_MessageLabel->setText("Waiting for white player");
    m_MessageLabel->setAlignment(Qt::AlignCenter);
    m_MessageLabel->setStyleSheet("font-size: 20px; font-weight: bold;");

    mainGridLayout->addWidget(m_MessageLabel, 0, 1, 1, 1);
}

void ChessUIQt::InitializeButtons(QGridLayout* mainGridLayout)
{
    QPushButton* saveButton = new QPushButton("Save");
    QPushButton* loadButton = new QPushButton("Load");
    QPushButton* restartButton = new QPushButton("Restart");
    QPushButton* drawButton = new QPushButton("Draw");

    QWidget* buttonContainer = new QWidget();
    QGridLayout* btnGrid = new QGridLayout();

    btnGrid->addWidget(saveButton, 0, 0);
    btnGrid->addWidget(loadButton, 0, 1);
    btnGrid->addWidget(restartButton, 0, 2);
    btnGrid->addWidget(drawButton, 0, 3);

    connect(saveButton, &QPushButton::pressed, this, &ChessUIQt::OnSaveButtonClicked);
    connect(loadButton, &QPushButton::pressed, this, &ChessUIQt::OnLoadButtonClicked);
    connect(restartButton, &QPushButton::pressed, this, &ChessUIQt::OnRestartButtonClicked);
    connect(drawButton, &QPushButton::pressed, this, &ChessUIQt::OnDrawButtonClicked);

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
    QGridLayout* chessGridLayout;
    chessGridLayout = new QGridLayout();
    QWidget* board = new QWidget();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_grid[i][j] = new GridButton({ i,j }, PieceType::none, PieceColor::none);
            chessGridLayout->addWidget(m_grid[i][j], i, j, 1, 1);
            connect(m_grid[i][j], &GridButton::Clicked, this, &ChessUIQt::OnButtonClicked);
        }
    }

    board->setLayout(chessGridLayout);
    mainGridLayout->addWidget(board, 1, 1, 1, 1);
}

void ChessUIQt::OnButtonClicked(const std::pair<int, int>&position)
{
    //At second click
    if (m_selectedCell.has_value()) {
        //TODO COMPLETE ME...
        // game.MakeMove(...);
        Position start;
        start.first = m_selectedCell->first;
        start.second = m_selectedCell->second;
        m_game->MovePiece(start, position);

        //Unselect prev. pressed button
        m_grid[m_selectedCell.value().first][m_selectedCell.value().second]->setSelected(false);
        m_selectedCell.reset();
    }
    //At first click
    else {
        m_selectedCell = position;
        m_grid[position.first][position.second]->setSelected(true);

        //TODO Show possible moves here
        //HighlightPossibleMoves(game.GetPossibleMoves(...))
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
    //TODO ...
}

void ChessUIQt::OnDrawButtonClicked()
{
    //TODO MODIFY ME

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Draw proposal", "Do you accept a draw?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        //TODO ...
        //game.Draw(...);
    }
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

void ChessUIQt::UpdateBoard(const std::array<std::array<std::pair<PieceType, PieceColor>, 8>, 8>& newBoard)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_grid[i][j]->setPiece(newBoard[i][j]);
            m_grid[i][j]->setSelected(false);
            m_grid[i][j]->setHighlighted(false);
        }
    }

}

void ChessUIQt::HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves)
{
    for (const auto& position : possibleMoves) {
        m_grid[position.first][position.second]->setHighlighted(true);
    }
}

void ChessUIQt::StartGame()
{
    //TODO MODIFY ME OR DELETE ME
    UpdateBoard(Helper::getDefaultBoard());
}

void ChessUIQt::ShowPromoteOptions()
{
    QInputDialog dialog;
    QList<QString> options;
    options.append("Rook");
    options.append("Bishop");
    options.append("Queen");
    options.append("Knight");

    dialog.setComboBoxItems(options);
    dialog.setModal(true);

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Pawn promote"),
        tr("Promote pawn to: "), options, 0, false, &ok);

    if (ok && !item.isEmpty())
    {
        //TODO
        //game.promotePawn(parseQStringToPieceType(item))

        //TODO DELETE ME...
        QMessageBox notification;
        notification.setText("You selected " + item);
        notification.exec();
    }
}

