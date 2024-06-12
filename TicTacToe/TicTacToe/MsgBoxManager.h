#pragma 
//--------------------------------------------------------------------
// �ļ���:		MsgBoxManager.h
// ��  ��:		��Ϣ���ڹ�����
// ˵  ��:		
// ��������:	2024/6/6
// ������:		Evildoer
// ��Ȩ����:	
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

