#pragma once
#include <QtCore/QObject>
#include <QtCore/QVector>
#include <QtCore/QRect>

#include "Enum.h"
namespace Evildoer
{
	class TicTacToeUI;
	class GameState;
	class GameTime;

	enum Player
	{
		None,
		Human,
		AI
	};
	struct PlayerInfo
	{
		Player player;
		QRect  rect;
	};


	class TicTacToe:public QObject
	{
		Q_OBJECT
	public:
		TicTacToe();
		~TicTacToe();

		void init(TicTacToeUI* gameUi,int w,int h);

		void changeGameState(GameStateType newState);
		//int  runGameLoop();//通过事件驱动，状态切换，游戏逻辑，故不需要update

		void showWelcomScreen();
		void startNewGame();

		void initBoardMap();

		void enablePlayerInput();

		void playerTurn(int x, int y);
		void aiTurn();

		void makeMove(int x, int y, Player play);

		void showGameOver();

		void setValidMove(bool value);

		const QVector<QVector<PlayerInfo>>& getBoard()const;

		GameResult GetGameResult()const;
	private:
		bool isFull();
		bool checkWin(Player player,const QVector<QVector<PlayerInfo>>& board = QVector<QVector<PlayerInfo>>());//board代表是否用来计算最优
		void calculateBestMove(int& x, int& y);
		void simpleRandomMove(int& x, int& y);
		int evaluate(const QVector<QVector<PlayerInfo>>& board);
		int minimax(const QVector<QVector<PlayerInfo>>& board,bool maximizingPlayer, int depth);
		QVector<QVector<PlayerInfo>> copyBoard()const;
	private:
		QVector<QVector<PlayerInfo>>	m_vecBoard;
		std::unique_ptr<GameState>		m_pCurrentState;

		GameStateType					m_eGameStateType;

		TicTacToeUI*					m_pGameUI;
		GameTime*						m_pGameTime;
		GameResult						m_eGameResult;
		bool							m_bValidMove;
		int								m_iScreenWidth;
		int								m_iScreenHeight;
	signals:
		void gameStateChanged(GameStateType state);

	};

}

