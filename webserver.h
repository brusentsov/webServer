/** @file
    @brief WebServer class
*/

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDateTime>

class WebServer : public QTcpServer
{
    Q_OBJECT
public:

    /**
        @brief constructor of WebServer
    */
    explicit WebServer(QObject *parent = 0);

    /**
        @brief set socket descriptor and connect signals readyRead() and disconnected()
        @param handle - socket descriptor
    */
    void incomingConnection(qintptr handle);

public slots:
    /**
        @brief calculate response and writess it to socket
    */
    void onReadyRead();

    /**
        @brief delete socket
    */
    void onDisconnected();

private :
    QString jsonDoc;
    QString dataFile;
    QString filename;
};

#endif // WEBSERVER_H
