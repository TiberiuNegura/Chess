#pragma once
#include <QPushButton>

#include "IPiece.h"

class GridButton : public QPushButton
{
	Q_OBJECT

public:
	GridButton(const std::pair<int, int>& boardPosition, EType pieceType = EType::EMPTY, EColor pieceColor = EColor::NONE, QWidget* parent = nullptr);
	~GridButton() = default;

	void mouseReleaseEvent(QMouseEvent* event) override;

	void updatePiece();
	void updateBackgroundColor();

	void setPiece(IPiecePtr newPiece);
	void setHighlighted(bool highlighted);
	void setSelected(bool selected);

signals:
	void Clicked(const std::pair<int, int>& position);

private:
	Position m_Position;
	EType m_PieceType;
	EColor m_PieceColor;
	bool m_Highlighted;
	bool m_Selected;
};
