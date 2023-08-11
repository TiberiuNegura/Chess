#include "GridButton.h"
#include "IPiece.h"
#include "IGame.h"
#include <QPainter>

#define BLACK_SQUARE_COLOR "#769656"
#define WHITE_SQUARE_COLOR "#efeed2"

void GridButton::mouseReleaseEvent(QMouseEvent* event)
{
	QPushButton::mouseReleaseEvent(event);
	emit(Clicked(m_Position));
}

void GridButton::updatePiece()
{

	std::string imagePath = ":/ChessUI/res/";

	switch (m_PieceColor)
	{
	case EColor::NONE:
		imagePath += "empty";
		break;
	case EColor::BLACK:
		imagePath += "b";
		break;
	case EColor::WHITE:
		imagePath += "w";
		break;
	}

	switch (m_PieceType)
	{
	case EType::EMPTY:
		break;
	case EType::KING:
		imagePath += "k";
		break;
	case EType::ROOK:
		imagePath += "r";
		break;
	case EType::BISHOP:
		imagePath += "b";
		break;
	case EType::QUEEN:
		imagePath += "q";
		break;
	case EType::HORSE:
		imagePath += "h";
		break;
	case EType::PAWN:
		imagePath += "p";
		break;
	default:
		break;
	}

	imagePath += ".png";

	QPixmap pixmap(QString::fromStdString(imagePath));
	QIcon ButtonIcon(pixmap);
	setIcon(ButtonIcon);
	setIconSize(pixmap.size());
}

void GridButton::updateBackgroundColor()
{
	bool defaultColorBlack = (m_Position.first + m_Position.second) % 2;
	QString backColor = "";

	defaultColorBlack == true ? backColor = BLACK_SQUARE_COLOR : backColor = WHITE_SQUARE_COLOR;

	QString styleSheet = "background-color: " + backColor + "; border: none;";


	setStyleSheet(styleSheet);
}

void GridButton::setPiece(IPiecePtr newPiece)
{
	if (!newPiece)
	{
		m_PieceType = EType::EMPTY;
		m_PieceColor = EColor::NONE;
	}
	else
	{
		m_PieceType = newPiece->GetType();
		m_PieceColor = newPiece->GetColor();
	}

	updatePiece();
}

void GridButton::setHighlighted(EHighlight highlighted) 
{
	m_Highlighted = highlighted;
	updateBackgroundColor();
}

void GridButton::setSelected(bool selected)
{
	m_Selected = selected;
	updateBackgroundColor();
}

void GridButton::paintEvent(QPaintEvent* event)
{
	QPushButton::paintEvent(event);
	QPainter painter(this);
	QColor penColor;
	QFont font = painter.font();

	font.setFamily("Segoe UI");
	font.setBold(true);
	painter.setFont(font);


	bool defaultColorBlack = (m_Position.first + m_Position.second) % 2;
	defaultColorBlack == true ? penColor = WHITE_SQUARE_COLOR : penColor = BLACK_SQUARE_COLOR;

	int textX = 5;
	int textY = 5;

	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setPen(penColor);

	if (m_Position.first == 7)
		painter.drawText(textX, textY, width() - 2 * textX, height() - 2 * textY, Qt::AlignBottom | Qt::AlignRight, QChar((char)'a' + m_Position.second));
	if (m_Position.second == 0)
		painter.drawText(textX, textY, width() - 2 * textX, height() - 2 * textY, Qt::AlignTop | Qt::AlignLeft, QString::number(8-m_Position.first));

	if (m_Highlighted == EHighlight::EMPTY_POS)
	{
		QBrush brush(Qt::black);
		painter.setPen(Qt::NoPen);
		painter.setOpacity(0.1);

		// Calculate the center of the button
		int centerX = width() / 2;
		int centerY = height() / 2;

		// Calculate the radius of the circle as a fraction of the button size
		int radius = qMin(width(), height()) / 6;

		// Draw the circle
		painter.setBrush(brush);
		painter.drawEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
	}
	else if (m_Highlighted == EHighlight::OCCUPIED_POS)
	{
		QPen pen(Qt::black); 
		pen.setWidth(5);     
		painter.setOpacity(0.1);

		int squareSize = qMin(width(), height());

		// Calculate the top-left corner of the square
		int x = (width() - squareSize) / 2;
		int y = (height() - squareSize) / 2;


		// Calculate the radius of the inscribed circle as half the square size
		int radius = squareSize / 2;

		// Calculate the center of the square
		int centerX = x + squareSize / 2;
		int centerY = y + squareSize / 2;

		// Draw the empty circle (no fill)
		painter.setPen(pen);
		painter.drawEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
	}

}

GridButton::GridButton(const Position& boardPosition, EType pieceType, EColor pieceColor, QWidget* parent)
	: m_Position(boardPosition)
	, m_PieceType(pieceType)
	, m_PieceColor(pieceColor)
	, m_Highlighted(EHighlight::NONE)
	, m_Selected(false)
{

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	updateBackgroundColor();
	updatePiece();

}