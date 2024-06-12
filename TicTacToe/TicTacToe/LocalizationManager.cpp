#include "LocalizationManager.h"
#include <QtCore/QFile>
#include <QtCore/QJsonArray>

namespace Evildoer
{
	QString LocalizationManager::LANGUAGE = "zh";

    LocalizationManager* LocalizationManager::m_sInstance = nullptr;

	LocalizationManager& LocalizationManager::GetSingleton()
	{
		if(m_sInstance == nullptr)
			m_sInstance = new LocalizationManager();
		return *m_sInstance;
	}

	LocalizationManager::LocalizationManager()
	{

	}

	LocalizationManager::~LocalizationManager()
	{

	}

	bool LocalizationManager::Initialize()
	{
		QFile loadFile("config/locale_" + LANGUAGE + ".json");

		if (!loadFile.open(QIODevice::ReadOnly)) 
		{
			return false;
		}

		QByteArray locateData = loadFile.readAll();
		
		m_localeDoc = QJsonDocument::fromJson(locateData);
		m_localeObj = m_localeDoc.object();
		return true;
	}

	bool LocalizationManager::HasLocaleString(QString key)
	{
		return m_localeObj.contains(key);
	}

	QString LocalizationManager::GetLocaleString(QString key)
	{
		if(m_localeObj.contains(key))
			return m_localeObj[key].toString();
		return QString();
	}

	QStringList LocalizationManager::GetLocaleStringList(QString key)
	{
		QJsonArray arr = m_localeObj[key].toArray();
		QStringList strList;
		for(int i = 0 ;i < arr.size(); i++)
		{
			strList.push_back(arr[i].toString());
		}
		return strList;
	}
}

