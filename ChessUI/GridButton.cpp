#include "GridButton.h"
#include "IPiece.h"
#include "IGame.h"
#include <QPainter>

void GridButton::mouseReleaseEvent(QMouseEvent* event)
{
	QPushButton::mouseReleaseEvent(event);
	emit(Clicked(m_Position));
}

void GridButton::updatePiece()
{
	std::string imagePath = "res/";

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
	setIconSize(pixmap.rect().size());
}

void GridButton::updateBackgroundColor()
{
	bool defaultColorBlack = (m_Position.first + m_Position.second) % 2;
	QString backColor = "";

	if (defaultColorBlack)
		backColor = "#769656";
	else if (!defaultColorBlack)
		backColor = "#efeed2";

	setStyleSheet("background-color: " + backColor + "; border: none;");
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