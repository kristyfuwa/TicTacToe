#include "TicTacToe.h"
#include "TicTacToeUI.h"
#include <QtWidgets/QApplication>
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	
	Evildoer::TicTacToe game;

	Evildoer::TicTacToeUI ui(&game);

	game.init(&ui,460,700);
	ui.show();

	return app.exec();
}