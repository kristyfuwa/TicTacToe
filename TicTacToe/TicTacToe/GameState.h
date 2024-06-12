#pragma once
#include "TicTacToe.h"

namespace Evildoer
{
	class GameState
	{
	public:
		virtual void enter(TicTacToe& game) = 0;
		virtual GameStateType getType()const = 0;
		virtual ~GameState() {}

	};

	class StartGameState :public GameState
	{
	public:
		void enter(TicTacToe& game)override
		{
			game.showWelcomScreen();
		}

		GameStateType getType()const override
		{
			return GameStart;
		}
	};

	class PlayerTurnGameState :public GameState
	{
	public:
		void enter(TicTacToe& game)override
		{
			game.enablePlayerInput();
		}

		GameStateType getType()const override
		{
			return PlayerTurn;
		}
	};

	class AITurnGameState :public GameState
	{
	public:
		void enter(TicTacToe& game)override
		{
			game.aiTurn();
		}

		GameStateType getType()const override
		{
			return AITurn;
		}
	};

	class GameOverState :public GameState
	{
	public:
		void enter(TicTacToe& game)override
		{
			game.showGameOver();
		}


		GameStateType getType()const override
		{
			return GameOver;
		}
	};
}


