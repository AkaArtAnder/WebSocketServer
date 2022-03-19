#include "../includes/web_socket_server.h"
#include "../includes/logger.hpp"

#include <QDebug>
#include <QHostAddress>

namespace webSocketServer
{   
    WebSocketServer::WebSocketServer(const quint16& serverPort) : 
        QWebSocketServer("WebServer", QWebSocketServer::NonSecureMode)
    {
        qInstallMessageHandler(logger::logMessage);

        if (this -> listen(QHostAddress::Any, serverPort))
        {
            qDebug() << "Server listen port: " + QString::number(serverPort);
        }
        else
        {
            qDebug() << "Error run server";
            this -> close();
            exit(-1);
        }
    }
} // namespace webSocketServer
