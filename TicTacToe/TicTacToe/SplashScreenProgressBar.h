#pragma 
//--------------------------------------------------------------------
// 文件名:		SplashScreenProgressBar.h
// 内  容:		加载界面以及进度条
// 说  明:		
// 创建日期:	2024/6/8
// 创建人:		Evildoer
// 版权所有:	
//--------------------------------------------------------------------
#include <QtWidgets/QSplashScreen>
#include <QtWidgets/QProgressBar>
#include <QtGui/QPixmap>
#include <QtCore/QList>

namespace Evildoer
{
	class SplashScreenProgressBar :	public QSplashScreen
	{	
		Q_OBJECT
	public:
		SplashScreenProgressBar(QPixmap& pixmap,int time,bool showProgressBar = true);
		~SplashScreenProgressBar();

		void				SetProgress(int value);
		void				SetMessage(QString msg);
	private:
		QProgressBar*		m_pProgressBar;
		int					m_iIndex;
		bool				m_bShowProgressBar;

	private slots:
		void			UpdataProgress();
		void			ProgressChanged(int);
	};
}
