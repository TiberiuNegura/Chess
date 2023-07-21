#include "GridButton.h"

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
	case PieceColor::none:
		imagePath += "empty";
		break;
	case PieceColor::black:
		imagePath += "b";
		break;
	case PieceColor::white:
		imagePath += "w";
		break;
	}

	switch (m_PieceType)
	{
	case PieceType::none:
		break;
	case PieceType::king:
		imagePath += "k";
		break;
	case PieceType::rook:
		imagePath += "r";
		break;
	case PieceType::bishop:
		imagePath += "b";
		break;
	case PieceType::queen:
		imagePath += "q";
		break;
	case PieceType::knight:
		imagePath += "h";
		break;
	case PieceType::pawn:
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

void GridButton::setPiece(std::pair<PieceType, PieceColor> newPiece)
{
	m_PieceType = newPiece.first;
	m_PieceColor = newPiece.second;

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

GridButton::GridButton(const std::pair<int, int>& boardPosition, PieceType pieceType, PieceColor pieceColor, QWidget* parent):
	m_Position(boardPosition), m_PieceType(pieceType), m_PieceColor(pieceColor), m_Highlighted(false), m_Selected(false)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	updateBackgroundColor();

	updatePiece();
}