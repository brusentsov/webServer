#include "webserver.h"
#include "convert.h"
#include <QByteArray>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

WebServer::WebServer(QObject *parent) :
    QTcpServer(parent)
{
    if(listen(QHostAddress::LocalHost, 8080)) {
        qDebug() << "Listening...";
    } else {
        qDebug() << "ERROR on start : " << errorString();
    }
    filename = "/home/brusentcov/builds_qt/lab8/data/data.txt";
    dataFile = createDataJson(filename);
    qDebug() << "dataFile : " << dataFile;
}

void WebServer::incomingConnection(qintptr handle)
{
    QTcpSocket * socket = new QTcpSocket();
    socket->setSocketDescriptor(handle);

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void WebServer::onReadyRead()
{
    QTcpSocket * socket = qobject_cast<QTcpSocket*>(sender());
    QString request = socket->readLine(2000);
    QString response = "HTTP/1.1 200 OK\r\n\r\n";

    qDebug() << "request : " << request;

    QStringList requestFields = request.split(" ");
    if (requestFields.at(0) == "GET" && requestFields.at(2) == "HTTP/1.1\r\n") {
        QString key;
        QString arg1;
        QString arg2;
        QString command = requestFields.at(1);
        QStringList afterSlash = command.split("/");

        qDebug() << "afterSlash size : " << afterSlash.size();
        if (afterSlash.size() == 3) {
            qDebug() << "afterSlash.at(2) : " << afterSlash.at(2);
        }
        if (afterSlash.size() == 2) {
            QStringList keys = command.split("?");
            if (keys.size() == 2) {
                key = keys.at(1);
                qDebug() << "key : " << key;
                QStringList args = key.split("=");
                if (args.size() == 2) {
                    arg1 = args.at(0);  //name
                    arg2 = args.at(1);  //value
                }
            }
        }

        qDebug() << "command : " << command;

        if (command == "/") {
            response += getServerInfo();
        }

        else if (command == "/file") {
            response += dataFile;
        }

        else if (command == "/file/data") {
            response += createDataNumbersJson(filename);
        }

        else if (command == "/favourites") {
            response += getFavourites();
        }

        else if (afterSlash.size() == 3) {  // /favourites/2
            QString number = afterSlash.at(2);
            if (number.toInt() == 0) {
                response = "HTTP/1.1 404 Not found\r\n\r\n";
            } else {
                int value = number.toInt();
                if (value <= getFavouritesSize() && value > 0) {
                    QString object = getIdObject(number);
                    response += object;
                } else {
                    response = "HTTP/1.1 404 Not found\r\n\r\n";
                }
            }
        }

        else if (afterSlash.size() == 2) {          // /favourites?name=Tyler
            if (arg1 == "name") {
                QString json = getNameObjects(arg2);
                if(json != "failure") {
                    response += json;
                } else {
                    response = "HTTP/1.1 404 Not found\r\n\r\n";
                }
            } else {
                response = "HTTP/1.1 404 Not found\r\n\r\n";
            }
        }

        else {
            response = "HTTP/1.1 404 Not found\r\n\r\n";
        }
    }

    socket->write(response.toUtf8());
    socket->disconnectFromHost();
}

void WebServer::onDisconnected()
{
    QTcpSocket * socket = qobject_cast<QTcpSocket*>(sender());
    socket->close();
    socket->deleteLater();
}
