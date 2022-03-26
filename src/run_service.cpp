#include "../includes/web_socket_server.h"

#include <QCoreApplication>

int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);

	webSocketServer::WebSocketServer server(8181);

	return app.exec();
}