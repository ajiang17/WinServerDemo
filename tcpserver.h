#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpclientsocket.h"
#include <QTcpServer>

class TcpServer:public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = 0,int port = 0);
    void slotupdateserver(QString , int );
    void slotclientdisconnect(int);
    QList<TcpClientSocket*>Tcpclientsocketlist;
signals:
    void updateMsgx(QString, int);
protected:
    void incomingConnection(int socketDescriptor);
    //void updateserver(QString, int);

};

#endif // TCPSERVER_H
