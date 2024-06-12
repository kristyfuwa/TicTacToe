#pragma 
//--------------------------------------------------------------------
// 文件名:		MsgBoxManager.h
// 内  容:		消息窗口管理类
// 说  明:		
// 创建日期:	2024/6/6
// 创建人:		Evildoer
// 版权所有:	
//--------------------------------------------------------------------

#include<QtCore/QString>

namespace Evildoer
{
	//------------------------------------MsgBoxManager------------------------------------------------------------
    class MsgBoxManager
	{
	public:
		static MsgBoxManager& GetSingleton();
		~MsgBoxManager();

		int ShowOkMessageBox(QString msg,QString titleStr = QString(), QString okLbl = QString(),bool bModal = false,bool bFramelessWindowHint = false);
		int ShowYesNoMessageBox(QString msg,QString yesLbl = QString(),QString noLbl = QString(),QString titleStr = QString());
		int ShowSaveDiscardCancelMessageBox(QString msg,QString saveLbl = QString(),QString discardLbl = QString(),QString cancelLbl = QString(),QString titleStr = QString());

	private:
		MsgBoxManager();
		static MsgBoxManager *m_sInstance;

	};
}

