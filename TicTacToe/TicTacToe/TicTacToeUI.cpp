#include "TicTacToeUI.h"
#include "GameState.h"
#include "TicTacToe.h"
#include "MsgBoxManager.h"
#include "LocalizationManager.h"
#include <QtWidgets/QVBoxLayout>
#include <QApplication>

#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 40
#define BUTTON_SPACE 5
namespace Evildoer
{
	TicTacToeUI::TicTacToeUI(TicTacToe* game, QWidget* parent /*= nullptr*/):QWidget(parent),m_pGame(game),m_bClose(false), m_eGameStateType(TypeNum)
	{
		setWindowTitle(LocalizationManager::GetSingleton().GetLocaleString("GameTitle"));
		QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(hasHeightForWidth());
		setSizePolicy(sizePolicy);
		setFixedSize(460, 700);

		//game start
		startLabel = new QLabel(this);
		QPixmap pixmap("resource/background.png");
		if (!pixmap.isNull())
			startLabel->setPixmap(pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

		victorBackground = QPixmap("resource/victory.png");
		defeatBackground = QPixmap("resource/defeat.png");
		equalBackground  =	QPixmap("resource/equal.png");

		InitializeButton(singleModeButton, "resource/single_mode.png", "SingleMode", startLabel);
		InitializeButton(onlineModeButton, "resource/online_mode.png", "OnlineMode", startLabel);
		InitializeButton(exitButton, "resource/exit.png", "ExistGame", startLabel);
		InitializeButton(continueButton, "resource/continue.png", "", this);
		InitializeButton(backButton, "resource/back.png", "", this);


		continueButton->setIconSize(QSize(120, 40));
		backButton->setIconSize(QSize(120, 40));
		continueButton->setVisible(false);
		backButton->setVisible(false);

		connect(singleModeButton, &QPushButton::clicked, this, &TicTacToeUI::OnSingleGameClicked);
		connect(onlineModeButton, &QPushButton::clicked, this, &TicTacToeUI::OnOnlineGameClicked);
		connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);
		connect(continueButton, &QPushButton::clicked, this, &TicTacToeUI::OnContinueGame);
		connect(backButton, &QPushButton::clicked, this, &TicTacToeUI::OnBackGame);

		//gameoverLabel->setVisible(false);
		exitButton->setGeometry((width() - BUTTON_WIDTH) / 2.0f, height() - BUTTON_HEIGHT - BUTTON_SPACE, BUTTON_WIDTH, BUTTON_HEIGHT);
		onlineModeButton->setGeometry((width() - BUTTON_WIDTH) / 2.0f, height() - 2 * BUTTON_HEIGHT - 2 * BUTTON_SPACE, BUTTON_WIDTH, BUTTON_HEIGHT);
		singleModeButton->setGeometry((width() - BUTTON_WIDTH) / 2.0f, height() - 3 * BUTTON_HEIGHT - 3 * BUTTON_SPACE, BUTTON_WIDTH, BUTTON_HEIGHT);
		continueButton->setGeometry((width() / 2 - 120) / 2.0f, height() - BUTTON_HEIGHT- 4 * BUTTON_SPACE, 120, 40);
		backButton->setGeometry(width() / 2 + (width() / 2 - 120) / 2.0f, height() - BUTTON_HEIGHT - 4 * BUTTON_SPACE, 120, BUTTON_HEIGHT);

		connect(m_pGame, &TicTacToe::gameStateChanged, this, &TicTacToeUI::OnGameStateChanged);
	}

	TicTacToeUI::~TicTacToeUI()
	{

	}

	bool TicTacToeUI::isClose()
	{
		return m_bClose;
	}

	void TicTacToeUI::mouseReleaseEvent(QMouseEvent *event)
	{
		QPoint pt = event->pos();
		if (event->button() == Qt::LeftButton && m_eGameStateType == PlayerTurn)
		{
			int offset = (height() - width()) / 2;//此处默认宽高比小于，即竖屏手机
			QRectF boardRect(0, offset, width(), width());
			if (!boardRect.contains(pt))
			{
				m_pGame->setValidMove(false);
				return;
			}
			auto boardMap = m_pGame->getBoard();
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					if (boardMap[i][j].rect.contains(pt) && boardMap[i][j].player == None)
					{
						m_pGame->setValidMove(true);
						m_pGame->playerTurn(i, j);
						return;
					}
				}
			}
			m_pGame->setValidMove(true);
		}
	}

	void TicTacToeUI::paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing); // 可选，抗锯齿

		switch (m_eGameStateType)
		{
		case Evildoer::GameStart:
		{
			continueButton->hide();
			backButton->hide();
			startLabel->show();
		}
			break;
		case Evildoer::PlayerTurn:
		case Evildoer::AITurn:
		{
			continueButton->hide();
			backButton->hide();
			startLabel->hide();
			auto boardMap = m_pGame->getBoard();
			int cellSize = qMin(width(), height()) / 3; // 计算每个格子的大小
			QRectF boardRect((width() - 3 * cellSize) / 2, (height() - 3 * cellSize) / 2, 3 * cellSize, 3 * cellSize); // 棋盘区域
			// 绘制棋盘背景
			QPixmap pixmap("resource/game_bk.png");
			QBrush background(pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
			painter.fillRect(rect(), background);

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					QRectF gridRect = boardMap[i][j].rect;
					Player player = boardMap[i][j].player;

					QBrush baordGround(Qt::white);
					painter.setBrush(Qt::white); // Own颜色
					painter.fillRect(gridRect, baordGround);

					// 设置线条颜色和宽度（这行可以移至循环外，如果确保每次循环都相同）
					QPen pen(Qt::gray, 4);
					painter.setPen(pen);
					// 绘制网格线
					painter.drawRect(gridRect);

					// 根据玩家类型绘制实心圆
					int circleDiameter = qMin(gridRect.width(), gridRect.height()); // 圆的直径等于格子的较短边
					QPointF center = QPointF(gridRect.center()); // 圆心位置

					if (player == Player::Human)
					{
						painter.setBrush(QColor(249, 61, 81)); // Own颜色
						painter.drawEllipse(center, circleDiameter / 2.0, circleDiameter / 2.0); // 绘制圆形
					}
					else if (player == Player::AI)
					{
						painter.setBrush(QColor(157, 212, 71)); // Ai颜色
						painter.drawEllipse(center, circleDiameter / 2.0, circleDiameter / 2.0); // 绘制圆形
					}
				}
			}

			QPen pen(Qt::white, 6); // 黑色线条，宽度5
			painter.setPen(pen);

			QFont font;
			font.setPointSize(15); // 示例字体大小
			painter.setFont(font);

			QString playerStateText = LocalizationManager::GetSingleton().GetLocaleString("CurrentGamePlayer");
			playerStateText.append(m_eGameStateType == AITurn ? QString("AI") : ("Own"));
			int labelW = 200;
			int lableH = 50;
			// 计算文本的边界矩形以居中对齐
			QRect rect((width() - labelW) / 2.0f, height() - lableH - 20, labelW, lableH);
			painter.drawText(rect.left(), rect.top(), playerStateText);

		}
			break;
		case Evildoer::GameOver:
		{
			continueButton->show();
			backButton->show();
			auto boardMap = m_pGame->getBoard();
			int cellSize = qMin(width(), height()) / 3; // 计算每个格子的大小
			QRectF boardRect((width() - 3 * cellSize) / 2, (height() - 3 * cellSize) / 2, 3 * cellSize, 3 * cellSize); // 棋盘区域
			// 绘制棋盘背景
			QPixmap pixmap("resource/game_bk.png");
			QBrush background(pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
			painter.fillRect(rect(), background);

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					QRectF gridRect = boardMap[i][j].rect;
					Player player = boardMap[i][j].player;

					QBrush baordGround(Qt::white);
					painter.setBrush(Qt::white); // Own颜色
					painter.fillRect(gridRect, baordGround);

					// 设置线条颜色和宽度（这行可以移至循环外，如果确保每次循环都相同）
					QPen pen(Qt::gray, 4);
					painter.setPen(pen);
					// 绘制网格线
					painter.drawRect(gridRect);

					// 根据玩家类型绘制实心圆
					int circleDiameter = qMin(gridRect.width(), gridRect.height()); // 圆的直径等于格子的较短边
					QPointF center = QPointF(gridRect.center()); // 圆心位置

					if (player == Player::Human)
					{
						painter.setBrush(QColor(249, 61, 81)); // Own颜色
						painter.drawEllipse(center, circleDiameter / 2.0, circleDiameter / 2.0); // 绘制圆形
					}
					else if (player == Player::AI)
					{
						painter.setBrush(QColor(157, 212, 71)); // Ai颜色
						painter.drawEllipse(center, circleDiameter / 2.0, circleDiameter / 2.0); // 绘制圆形
					}
				}
			}

			//QPixmap piecePixmap("resource/victory.png");
			//QImage image = piecePixmap.toImage().convertToFormat(QImage::Format_ARGB32);

			//QColor edgeColor(QColor(48,48,48));
			//for (int x = 0; x < image.width(); ++x)
			//{
			//	for (int y = 0; y < image.height(); ++y)
			//	{
			//		if (image.pixel(x, y) == edgeColor.rgb())
			//			image.setPixel(x, y, qRgba(0, 0, 0, 0));
			//	}
			//}

			//QPixmap processedPixmap = QPixmap::fromImage(image);
			GameResult ret = m_pGame->GetGameResult();
			if (ret == PLAYER_WINS)
			{
				painter.drawPixmap(0, 0, victorBackground);
			}
			else if (ret == AI_WINS)
			{
				painter.drawPixmap(0, 0, defeatBackground);
			}
			else if (ret = DRAW)
			{
				painter.drawPixmap(0, 0, equalBackground);
			}
			
		}
			break;
		case Evildoer::TypeNum:
			break;
		}
	}

	void TicTacToeUI::closeEvent(QCloseEvent *event)
	{
		m_bClose = true;
		QWidget::closeEvent(event);
	}

	void TicTacToeUI::OnGameStateChanged(GameStateType state)
	{
		m_eGameStateType = state;
		update();
	}

	void TicTacToeUI::OnSingleGameClicked()
	{
		m_pGame->changeGameState(PlayerTurn);
	}

	void TicTacToeUI::OnOnlineGameClicked()
	{
		MsgBoxManager::GetSingleton().ShowOkMessageBox("OnlineModeNotOpen");
	}

	void TicTacToeUI::OnContinueGame()
	{
		m_pGame->startNewGame();
		m_pGame->changeGameState(PlayerTurn);

	}

	void TicTacToeUI::OnBackGame()
	{
		m_pGame->changeGameState(GameStart);
	}

	void TicTacToeUI::InitializeButton(QPushButton*& button, const QString& iconName, const QString& toolTips, QWidget* parent)
	{
		button = new QPushButton(QIcon(iconName), "", parent);
		button->setStatusTip(LocalizationManager::GetSingleton().GetLocaleString(toolTips));
		button->setIconSize(QSize(150, 40));
	}

}