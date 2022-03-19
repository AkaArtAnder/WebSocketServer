/**
 * @file logger.hpp
 * @author RTNDR
 * @brief Файл, описывающий функцию, обеспечивающую логирование в файл
 * @version 0.1
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <QCoreApplication>
#include <QFile>
#include <QDateTime>
#include <QTextStream>

namespace logger
{
	/**
	 * @brief Функция перенаправления логов в указанный файл
	 * 
	 * @param type тип сообщения
	 * @param context default
	 * @param msg тело сообщения
	 */
	void logMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg)
	{
		QFile fMessFile(qApp->applicationDirPath() + "/Server.log");

		if (!fMessFile.open(QFile::Append | QFile::Text))
		{
			return;
		}

		QString sCurrDateTime = "[" +
								QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") + "]";
		QTextStream tsTextStream(&fMessFile);

		switch (type)
		{
		case QtDebugMsg:
			tsTextStream << QString("%1 Debug - %2").arg(sCurrDateTime).arg(msg) << "\n";
			break;

		case QtWarningMsg:
			tsTextStream << QString("%1 Warning - %2").arg(sCurrDateTime).arg(msg)<< "\n";
			break;

		case QtCriticalMsg:
			tsTextStream << QString("%1 Critical - %2").arg(sCurrDateTime).arg(msg)<< "\n";
			break;

		case QtInfoMsg:
			tsTextStream << QString("%1 Info - %2").arg(sCurrDateTime).arg(msg)<< "\n";
			break;
			
		case QtFatalMsg:
			tsTextStream << QString("%1 Fatal - %2").arg(sCurrDateTime).arg(msg)<< "\n";
			abort();
		}
		tsTextStream.flush();
		fMessFile.flush();
		fMessFile.close();
	}
} // namespace logger
