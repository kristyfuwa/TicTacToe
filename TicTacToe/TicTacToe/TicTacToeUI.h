#pragma once
#include <QtWidgets/QWidget>
#include <QtCore/QVector>
#include <QtGui/QtEvents>
#include <QtGui/QPainter>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtGui/QPixmap>

#include "Enum.h"
namespace Evildoer
{
	class TicTacToe;

	class TicTacToeUI :public QWidget
	{
		Q_OBJECT
	public:
		TicTacToeUI(TicTacToe* game,QWidget* parent = nullptr);
		~TicTacToeUI();

		bool isClose();
	protected:
		virtual void mouseReleaseEvent(QMouseEvent *event);
		virtual	void paintEvent(QPaintEvent *event);
		virtual void closeEvent(QCloseEvent *event);
	protected slots:
		void	OnGameStateChanged(GameStateType state);
		void	OnSingleGameClicked();
		void	OnOnlineGameClicked();
		void    OnContinueGame();
		void    OnBackGame();


	private:
		void	InitializeButton(QPushButton*& button, const QString& iconName, const QString& toolTips, QWidget* parent);
	private:

		QLabel*						startLabel;
		QPushButton*				singleModeButton;
		QPushButton*				onlineModeButton;
		QPushButton*				exitButton;
		QPushButton*				continueButton;
		QPushButton*				backButton;

		QPixmap						victorBackground;
		QPixmap						defeatBackground;
		QPixmap						equalBackground;

		TicTacToe*		m_pGame;
		bool			m_bClose;
		GameStateType	m_eGameStateType;
	};

}

