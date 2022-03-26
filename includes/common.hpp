/**
 * @file common.hpp
 * @author RTNDR
 * @brief Файл c дополнительными функциями
 * @version 0.1
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <QUuid>
#include <QString>

namespace common
{
	/**
	 * @brief Функция получения уникального идентификатора соединения
	 *
	 * @return уникальный идентификатор в виде строки
	 */
	QString GetUuid()
	{
		return QUuid::createUuid().toString(QUuid::Id128);
	}
} // namespace common
