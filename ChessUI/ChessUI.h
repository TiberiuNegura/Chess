#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChessUI.h"

class ChessUI : public QMainWindow
{
    Q_OBJECT

public:
    ChessUI(QWidget *parent = nullptr);
    ~ChessUI();

private:
    Ui::ChessUIClass ui;
};
