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
#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>
#include <QUrl>
#include <QWebSocket>

#include <memory>

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

			/**
			 * @brief Метод инициализации сигнально-слотовой системы сервера
			 * 
			 */
			void InitSigSlotConn();

			/**
			 * @brief Объект сокета
			 * 
			 * @warning Данный объект создан для тестирования
			 */
			std::shared_ptr<QWebSocket> clientSocket_;

		private Q_SLOTS:
			
			/**
			 * @brief Слот обработки входящего соединения
			 * 
			 */
			void InputConnectionHandling();

			/**
			 * @brief Слот отображения ошибок, возникающих при входящем соединении
			 *
			 * @param socketError тип возникающей ошибки 
			 */
			void ShowErrorInputConnection(QAbstractSocket::SocketError socketError);

			/**
			 * @brief Слот чтения текстовых данных из потока
			 *
			 * @todo Метод максимально усечен, необходимо разделить посылку ответа и прием сообщения 
			 * @param message принимаемые данные
			 */
			void ReadTextDataFrame(const QString& message);


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

