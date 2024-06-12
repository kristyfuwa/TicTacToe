#include "TicTacToe.h"
#include "GameState.h"
#include "TicTacToeUI.h"
#include "LocalizationManager.h"

#define MAX_DEPTH 4//深度3或4对于找到最优解已经足够
namespace Evildoer
{

	TicTacToe::TicTacToe() :m_bValidMove(false), m_pGameUI(nullptr), m_pGameTime(nullptr), m_eGameStateType(TypeNum), m_eGameResult(CONTINUE)
	{
		m_vecBoard.resize(3);
		for (int i = 0; i < 3; ++i)
			m_vecBoard[i].resize(3);
	}

	TicTacToe::~TicTacToe()
	{
		delete m_pGameTime;
	}

	void TicTacToe::init(TicTacToeUI* gameUi,int w,int h)
	{
		m_iScreenWidth = w;
		m_iScreenHeight = h;
		m_pGameUI = gameUi;
		LocalizationManager::GetSingleton().Initialize();
		changeGameState(GameStart);
	}

	void TicTacToe::changeGameState(GameStateType newState)
	{
		if (newState != m_eGameStateType)
		{
			m_eGameStateType = newState;
			switch (newState)
			{
			case Evildoer::GameStart:
				m_pCurrentState = std::make_unique<StartGameState>();
				break;
			case Evildoer::PlayerTurn:
				m_pCurrentState = std::make_unique<PlayerTurnGameState>();
				break;
			case Evildoer::AITurn:
				m_pCurrentState = std::make_unique<AITurnGameState>();
				break;
			case Evildoer::GameOver:
				m_pCurrentState = std::make_unique<GameOverState>();
				break;
			case Evildoer::TypeNum:
				m_pCurrentState = nullptr;
				break;
			default:
				break;
			}
		}

		m_pCurrentState->enter(*this);
		emit gameStateChanged(m_eGameStateType);
	}

	void TicTacToe::playerTurn(int x, int y)
	{
		if (m_eGameStateType == PlayerTurn && m_bValidMove)
		{
			makeMove(x, y, Human);
			if (!checkWin(Human)&& !isFull())
				changeGameState(AITurn);
			else
				changeGameState(GameOver);
		}
	}

	void TicTacToe::aiTurn()
	{
		int x = -1;
		int y = -1;
		calculateBestMove(x, y);
		if (x != -1 && y != -1)
			makeMove(x, y, AI);
		if (checkWin(AI))
			changeGameState(GameOver);
		else if (isFull())
			changeGameState(GameOver);
		else
			changeGameState(PlayerTurn);
		
	}

	void TicTacToe::calculateBestMove(int& x, int& y)
	{
		int bestValue = -1000;
		QVector<QPair<int, int>> emptyPos;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (m_vecBoard[i][j].player == None) {
					emptyPos.append({ i, j });
				}
			}
		}

		for (const auto& pos : emptyPos) {
			QVector<QVector<PlayerInfo>> tempBoard = copyBoard();
			tempBoard[pos.first][pos.second].player = AI;
			int moveValue = minimax(tempBoard, false, MAX_DEPTH); 

			if (moveValue > bestValue) {
				bestValue = moveValue;
				x = pos.first;
				y = pos.second;
			}
		}
	}

	void TicTacToe::simpleRandomMove(int& x, int& y)
	{
		QVector<QPair<int, int>> emptyPos;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (m_vecBoard[i][j].player == None)
					emptyPos.push_back(QPair<int, int>(i, j));
			}
		}

		if (!emptyPos.isEmpty())
		{
			qsrand(time(NULL));
			int index = qrand() % emptyPos.size();
			x = emptyPos[index].first;
			y = emptyPos[index].second;
			return;
		}
		x = -1;
		y = -1;
	}

	int TicTacToe::evaluate(const QVector<QVector<PlayerInfo>>& board)
	{
		if (checkWin(AI, board))
			return 10;
		if (checkWin(Human, board))
			return -10;
		return 0;
	}

	int TicTacToe::minimax(const QVector<QVector<PlayerInfo>>& board,bool maximizingPlayer, int depth)
	{
		if (depth == 0)
			return evaluate(board);
		int score = evaluate(board);
		if (score != 0)
			return score;
		QVector<QVector<PlayerInfo>> newBoard = board;
		int bestValue = maximizingPlayer ? -1000 : 1000;

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (newBoard[i][j].player == None) {
					newBoard[i][j].player = maximizingPlayer ? AI : Human;

					int value = minimax(newBoard, !maximizingPlayer, depth - 1);

					newBoard[i][j].player = None; 

					bestValue = maximizingPlayer ? std::max(bestValue, value) : std::min(bestValue, value);
				}
			}
		}
		return bestValue;
	}

	QVector<QVector<Evildoer::PlayerInfo>> TicTacToe::copyBoard() const
	{
		QVector<QVector<PlayerInfo>> copy(3, QVector<PlayerInfo>(3));
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				copy[i][j] = m_vecBoard[i][j];
			}
		}
		return copy;
	}

	void TicTacToe::makeMove(int x, int y, Player play)
	{
		m_vecBoard[x][y].player = play;
	}

	//int TicTacToe::runGameLoop()
	//{
	//	while (true)
	//	{
	//		m_pGameTime->Tick();
	//		update(m_pGameTime->GetDeltaTime());
	//		//render();
	//		if (m_pGameUI->isClose())
	//		{
	//			break;
	//		}
	//	}
	//	return 0;//若不适用本身的exec的话，则QT自身的事件循环，需使用QCoreApplication::processEvents()来触发
	//}

	void TicTacToe::showWelcomScreen()
	{
		startNewGame();
	}

	void TicTacToe::startNewGame()
	{
		initBoardMap();
	}

	void TicTacToe::initBoardMap()
	{
		int cellSize = qMin(m_iScreenWidth, m_iScreenHeight) / 3; // 计算每个格子的大小
		int offset = (m_iScreenHeight - m_iScreenWidth) / 2;//此处默认宽高比小于，即竖屏手机
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				PlayerInfo info;
				info.rect = QRect(j*cellSize, offset + cellSize * i, cellSize, cellSize);
				info.player = Player::None;
				m_vecBoard[i][j] = info;
			}
		}
	}

	void TicTacToe::enablePlayerInput()
	{

	}

	void TicTacToe::showGameOver()
	{
		if (checkWin(Human))
			m_eGameResult = PLAYER_WINS;
		else if (checkWin(AI))
			m_eGameResult = AI_WINS;
		else
			m_eGameResult = DRAW;
	}

	void TicTacToe::setValidMove(bool value)
	{
		m_bValidMove = value;
	}

	const QVector<QVector<Evildoer::PlayerInfo>>& TicTacToe::getBoard() const
	{
		return m_vecBoard;
	}

	Evildoer::GameResult TicTacToe::GetGameResult() const
	{
		return m_eGameResult;
	}

	bool TicTacToe::isFull()
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (m_vecBoard[i][j].player == None)
					return false;
			}
		}
		return true;
	}

	bool TicTacToe::checkWin(Player player, const QVector<QVector<PlayerInfo>>& board /*= QVector<QVector<PlayerInfo>>()*/)
	{
		const QVector<QVector<PlayerInfo>>& boardToCheck = board.isEmpty() ? m_vecBoard : board;
		for (int i = 0; i < 3; ++i)
		{
			// 检查行
			if (boardToCheck[i][0].player == player &&
				boardToCheck[i][1].player == player &&
				boardToCheck[i][2].player == player)
			{
				return true;
			}

			// 检查列
			if (boardToCheck[0][i].player == player &&
				boardToCheck[1][i].player == player &&
				boardToCheck[2][i].player == player)
			{
				return true;
			}
		}

		// 检查主对角线
		if (boardToCheck[0][0].player == player &&
			boardToCheck[1][1].player == player &&
			boardToCheck[2][2].player == player)
		{
			return true;
		}

		// 检查副对角线
		return boardToCheck[2][0].player == player &&
			boardToCheck[1][1].player == player &&
			boardToCheck[0][2].player == player;

	}


}