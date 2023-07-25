#pragma once
#include <QPushButton>

#include "Enums.h"
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
	void setHighlighted(EHighlight highlighted);
	void setSelected(bool selected);

signals:
	void Clicked(const std::pair<int, int>& position);

protected:
	void paintEvent(QPaintEvent* event) override;


private:
	Position m_Position;
	EType m_PieceType;
	EColor m_PieceColor;
	EHighlight m_Highlighted;
	bool m_Selected;
};
