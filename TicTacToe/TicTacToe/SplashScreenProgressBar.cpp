#include "SplashScreenProgressBar.h"

namespace Evildoer
{

	SplashScreenProgressBar::SplashScreenProgressBar(QPixmap& pixmap, int time, bool showProgressBar /*= true*/) : QSplashScreen(pixmap), m_iIndex(0), m_bShowProgressBar(showProgressBar)
	{
		m_pProgressBar = new QProgressBar(this);
		m_pProgressBar->setGeometry(0, pixmap.height() - 20, pixmap.width(), 15);
		m_pProgressBar->setStyleSheet("QProgressBar {birder:2px solid grey;border-radius:5px; color:black;background:rgb(220,219,215);font:15px;text-align:center; }QProgressBar::chunk {width:10px;margin:0.5px;background-color: rgb(172, 203, 143);}");
		m_pProgressBar->setRange(0, 100);
		m_pProgressBar->setValue(0);
		m_pProgressBar->setVisible(m_bShowProgressBar);
		connect(m_pProgressBar, SIGNAL(valueChanged(int)), this, SLOT(ProgressChanged(int))); //Öµ¸Ä

		QFont font;
		font.setPointSize(14);
		m_pProgressBar->setFont(font);
		if(!m_bShowProgressBar)
			SetMessage("Setting up the main window");
	}

	SplashScreenProgressBar::~SplashScreenProgressBar()
	{

	}

	void SplashScreenProgressBar::SetProgress(int value)
	{
		m_pProgressBar->setValue(value);
	}

	void SplashScreenProgressBar::SetMessage(QString msg)
	{
		Qt::Alignment bottomRight = Qt::AlignRight | Qt::AlignBottom;
		showMessage(msg, bottomRight, Qt::white);
	}


	void SplashScreenProgressBar::UpdataProgress()
	{
	
	}

	void SplashScreenProgressBar::ProgressChanged(int)
	{
		if (!m_bShowProgressBar)
		{
			if (m_iIndex >= 3)
				m_iIndex = 0;
			if (m_iIndex == 0)
				SetMessage("Setting up the main window .");
			else if (m_iIndex == 1)
				SetMessage("Setting up the main window ..");
			else if (m_iIndex == 2)
				SetMessage("Setting up the main window ...");
			m_iIndex++;
		}
		repaint();
	}

}


