#include "GridButton.h"
#include "IPiece.h"
#include "IGame.h"

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

	if (defaultColorBlack && !m_Highlighted)
		backColor = "#464e53";
	if (defaultColorBlack && m_Highlighted)
		backColor = "#3f4224";
	if (!defaultColorBlack && !m_Highlighted)
		backColor = "#d6d6d6";
	if (!defaultColorBlack && m_Highlighted)
		backColor = "#f8ff94";

	if (m_Selected)
		backColor = "#ff9494";

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

void GridButton::setHighlighted(bool highlighted)
{
	m_Highlighted = highlighted;
	updateBackgroundColor();
}

void GridButton::setSelected(bool selected)
{
	m_Selected = selected;
	updateBackgroundColor();
}

GridButton::GridButton(const Position& boardPosition, EType pieceType, EColor pieceColor, QWidget* parent)
	: m_Position(boardPosition)
	, m_PieceType(pieceType)
	, m_PieceColor(pieceColor)
	, m_Highlighted(false)
	, m_Selected(false)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	updateBackgroundColor();

	updatePiece();
}