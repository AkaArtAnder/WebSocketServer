#include "../includes/web_socket_server.h"
#include "../includes/logger.hpp"

namespace webSocketServer
{
	WebSocketServer::WebSocketServer(const quint16 &serverPort) :
		QWebSocketServer("WebServer", QWebSocketServer::NonSecureMode)
	{
		qInstallMessageHandler(logger::logMessage);//Перенаправление логов через callback

		if (this -> listen(QHostAddress::Any, serverPort))
		{
			qDebug() << "Server listen port: " + QString::number(serverPort);
			qDebug() << "Supported versions web socket protocol: " << this -> supportedVersions();
			qDebug() << "Server Url: " << (this -> serverUrl()).toString();
			InitSigSlotConn();
		}
		else
		{
			qDebug() << "Error run server";
			this -> close();
			exit(-1);
		}
	}

	void WebSocketServer::InitSigSlotConn()
	{
		QObject::connect(
			this,
			&webSocketServer::WebSocketServer::newConnection,
			this,
			&webSocketServer::WebSocketServer::InputConnectionHandling
		);

		QObject::connect(
			this,
			&webSocketServer::WebSocketServer::acceptError,
			this,
			&webSocketServer::WebSocketServer::ShowErrorInputConnection
		);
	}

	void WebSocketServer::ShowErrorInputConnection(QAbstractSocket::SocketError socketError)
	{
		qDebug() << "Error new input connect: " << this -> errorString();
	}

	void WebSocketServer::InputConnectionHandling()
	{
		qDebug() << "New connection";

		std::shared_ptr<QWebSocket> temp(this -> nextPendingConnection());
		clientSocket_ = temp;

		QObject::connect(
			clientSocket_.get(),
			&QWebSocket::textMessageReceived,
			this,
			&webSocketServer::WebSocketServer::ReadTextDataFrame
		);
	}

	void WebSocketServer::ReadTextDataFrame(const QString& message)
	{
		qDebug() << "New message from client";
		qDebug() << message;

		clientSocket_ -> sendTextMessage("Hello client");
	}

} // namespace webSocketServer
