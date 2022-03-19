/**
 * @file web_socket_server.h
 * @author RTNDR
 * @brief Сервер, поддерживающий протокол WebSocket
 * @version 0.1
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <QWebSocketServer>

namespace webSocketServer
{
	/**
	 * @brief Класс, реализующий функционал сервера по протоколу WebSocket
	 *
	 */
	class WebSocketServer : public QWebSocketServer
	{
		Q_OBJECT

		private:
			/* data */
		public:
			/**
			 * @brief Конструктор сервера
			 * 
			 * @param serverPort прослушиваемый порт
			 */
			WebSocketServer(const quint16& serverPort);

			/**
			 * @brief Деструктор
			 * 
			 */
			~WebSocketServer() = default;
	};
} // namespace webSocketServer

