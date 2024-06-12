#pragma once
namespace Evildoer
{
	enum GameStateType
	{
		GameStart,
		PlayerTurn,
		AITurn,
		GameOver,
		TypeNum
	};

	enum GameResult 
	{
		PLAYER_WINS,
		AI_WINS,
		DRAW,
		CONTINUE
	};
}

