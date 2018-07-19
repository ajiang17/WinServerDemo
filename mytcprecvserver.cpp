#include "mytcprecvserver.h"

Mytcprecvserver::Mytcprecvserver(QObject *parent,int port):QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}

void Mytcprecvserver::incomingConnection(int socketDescriptor)
{
    TcpClientSocket *tcpclientsocket = new TcpClientSocket(this);

    tcpclientsocket->setSocketDescriptor(socketDescriptor);

    Tcpclientsocketlist.append(tcpclientsocket);

    connect(tcpclientsocket,&TcpClientSocket::updataserver,this,&Mytcprecvserver::slotupdateserver);
    connect(tcpclientsocket,&TcpClientSocket::clientdisconnected,this,&Mytcprecvserver::slotclientdisconnect);
}

void Mytcprecvserver::slotupdateserver(QString msg, int length)
{
    emit updateserver(msg,length);
    for(int i = 0; i <Tcpclientsocketlist.count();i++)
    {
        QTcpSocket *item = Tcpclientsocketlist.at(i);
        item->write(msg.toUtf8().data());
    }
}


void Mytcprecvserver::slotclientdisconnect(int descriptor)
{
    for(int i = 0; i < Tcpclientsocketlist.count(); i++)
    {
        QTcpSocket *item = Tcpclientsocketlist.at(i);
        if(item->socketDescriptor() == descriptor)
        {
            Tcpclientsocketlist.removeAt(i);
            return;
        }
    }
    return;
}
