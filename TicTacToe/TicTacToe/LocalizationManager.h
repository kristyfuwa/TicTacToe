#pragma once
//--------------------------------------------------------------------
// �ļ���:		LocalizationManager.h
// ��  ��:		���ػ�����
// ˵  ��:		
// ��������:	2024/6/8
// ������:		Evildoer
//--------------------------------------------------------------------

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

namespace Evildoer
{
    class LocalizationManager
	{
	public:
		static QString LANGUAGE ;

		static LocalizationManager& GetSingleton();	
		~LocalizationManager();

		bool Initialize();

		bool HasLocaleString(QString key);

		QString GetLocaleString(QString key);

		QStringList GetLocaleStringList(QString key);

	private:
		LocalizationManager();
		static LocalizationManager* m_sInstance;

		QJsonDocument m_localeDoc;
		QJsonObject m_localeObj;

	};
}
