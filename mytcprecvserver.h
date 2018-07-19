#ifndef MYTCPRECVSERVER_H
#define MYTCPRECVSERVER_H

#include "mainwinserver.h"
#include "tcpclientsocket.h"
#include <QTcpServer>


class Mytcprecvserver:public QTcpServer
{
    Q_OBJECT
public:
    Mytcprecvserver(QObject *parent = 0,int port = 0);
    QList<TcpClientSocket*>Tcpclientsocketlist;
    //~Mytcprecvserver();
protected:
    void incomingConnection(int socketDescriptor);

protected slots:
    void slotupdateserver(QString,int);
    void slotclientdisconnect(int);


public slots:
    //void ConnectSucess();
signals:
    void updateserver(QString, int);
};

#endif // MYTCPRECVSERVER_H
