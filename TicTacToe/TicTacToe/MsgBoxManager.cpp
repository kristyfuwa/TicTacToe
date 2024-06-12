#include "MsgBoxManager.h"

#include <QtWidgets/QApplication>
#include <QtGui/QPainter>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTextEdit>

#include "LocalizationManager.h"

namespace Evildoer
{	
	//------------------------------------------------------------------------------------------------
	MsgBoxManager* MsgBoxManager::m_sInstance = nullptr;

	MsgBoxManager& MsgBoxManager::GetSingleton()
	{
		if(m_sInstance == nullptr)
			m_sInstance = new MsgBoxManager();
		return *m_sInstance;
	}

	MsgBoxManager::~MsgBoxManager()
	{
	}

	MsgBoxManager::MsgBoxManager()
	{
	}


	int MsgBoxManager::ShowOkMessageBox(QString msg, QString titleStr /*= QString()*/, QString okLbl /*= QString()*/, bool bModal /*= false*/, bool bFramelessWindowHint /*= false*/)
	{
		QMessageBox msgBox;
		if (titleStr.isEmpty())
			msgBox.setWindowTitle(LocalizationManager::GetSingleton().GetLocaleString("MessageBoxTitleLbl"));
		else
			msgBox.setWindowTitle(titleStr);

		if (okLbl.isEmpty())
			okLbl = LocalizationManager::GetSingleton().GetLocaleString("MessageBoxOkLbl");
		if(bModal)
			msgBox.setWindowModality(Qt::ApplicationModal);
		if(bFramelessWindowHint)
			msgBox.setWindowFlags(Qt::FramelessWindowHint);
		QString s = LocalizationManager::GetSingleton().GetLocaleString(msg);
		if (s.isEmpty())
			msgBox.setText(msg);
		else
			msgBox.setText(s);
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		msgBox.button(QMessageBox::Ok)->setText(okLbl);
		return msgBox.exec();
	}

	int MsgBoxManager::ShowYesNoMessageBox(QString msg, QString yesLbl, QString noLbl, QString titleStr)
	{
		QMessageBox msgBox;
		if(titleStr.isEmpty())
			msgBox.setWindowTitle(LocalizationManager::GetSingleton().GetLocaleString("MessageBoxTitleLbl"));
		else
			msgBox.setWindowTitle(titleStr);
		QString s = LocalizationManager::GetSingleton().GetLocaleString(msg);
		if (s.isEmpty())
			msgBox.setText(msg);
		else
			msgBox.setText(s);
		msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if(yesLbl.isEmpty())
			yesLbl = LocalizationManager::GetSingleton().GetLocaleString("MessageBoxYesLbl");
		if(noLbl.isEmpty())
			noLbl = LocalizationManager::GetSingleton().GetLocaleString("MessageBoxNoLbl");
		
		msgBox.button(QMessageBox::Yes)->setText(yesLbl);
		msgBox.button(QMessageBox::No)->setText(noLbl);		

		return msgBox.exec();
	}

	int MsgBoxManager::ShowSaveDiscardCancelMessageBox(QString msg,QString saveLbl,QString discardLbl,QString cancelLbl,QString titleStr)
	{
		QMessageBox msgBox;
		if(titleStr.isEmpty())
			msgBox.setWindowTitle(LocalizationManager::GetSingleton().GetLocaleString("MessageBoxTitleLbl"));
		else
			msgBox.setWindowTitle(titleStr);
		QString s = LocalizationManager::GetSingleton().GetLocaleString(msg);
		if (s.isEmpty())
			msgBox.setText(msg);
		else
			msgBox.setText(s);
		msgBox.setStandardButtons(QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);

		if(saveLbl.isEmpty())
			saveLbl = LocalizationManager::GetSingleton().GetLocaleString("MessageBoxSaveLbl");
		if(discardLbl.isEmpty())
			discardLbl = LocalizationManager::GetSingleton().GetLocaleString("MessageBoxDiscardLbl");
		if(cancelLbl.isEmpty())
			cancelLbl = LocalizationManager::GetSingleton().GetLocaleString("MessageBoxCancelLbl");

		msgBox.button(QMessageBox::Save)->setText(saveLbl);
		msgBox.button(QMessageBox::Cancel)->setText(cancelLbl);
		msgBox.button(QMessageBox::Discard)->setText(discardLbl);

		return msgBox.exec();
	}
}

