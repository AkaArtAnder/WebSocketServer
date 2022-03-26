#include "../includes/web_socket_server.h"
#include "../includes/logger.hpp"
#include "../includes/common.hpp"

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

		auto tempSocket = this -> nextPendingConnection();

		QObject::connect(
			tempSocket,
			&QWebSocket::textMessageReceived,
			this,
			&webSocketServer::WebSocketServer::ReadTextDataFrame
		);

		QObject::connect(
			tempSocket,
			&QWebSocket::disconnected,
			this,
			&webSocketServer::WebSocketServer::DisconnectInfo
		);

	}

	void WebSocketServer::ReadTextDataFrame(const QString &message)
	{
		qDebug() << "New message from client";
		qDebug() << message;

		auto clientSocket = qobject_cast<QWebSocket *>(QObject::sender());

		clientSocket -> sendTextMessage("Hello client");
	}

	void WebSocketServer::DisconnectInfo()
	{
		qDebug() << "Disconnected client";
		auto clientSocket = qobject_cast<QWebSocket *>(QObject::sender());
		clientSocket -> deleteLater();
	}

} // namespace webSocketServer
