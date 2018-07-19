#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent,int port):QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}


void TcpServer::incomingConnection(int socketDescriptor)
{
    TcpClientSocket *tcpclientsocket = new TcpClientSocket();
    qDebug()<<"someone connect!!!";

    tcpclientsocket->setSocketDescriptor(socketDescriptor);

    Tcpclientsocketlist.append(tcpclientsocket);

    connect(tcpclientsocket,&TcpClientSocket::updataserver,this,&TcpServer::slotupdateserver);
    connect(tcpclientsocket,&TcpClientSocket::clientdisconnected,this,&TcpServer::slotclientdisconnect);
}

void TcpServer::slotupdateserver(QString msg, int length)
{
    emit updateMsgx(msg,length);
    qDebug()<<"sssssssssssssssssssssss";
    for(int i = 0; i <Tcpclientsocketlist.count();i++)
    {
        QTcpSocket *item = Tcpclientsocketlist.at(i);
        item->write(msg.toUtf8().data());
    }
}


void TcpServer::slotclientdisconnect(int descriptor)
{
    for(int i = 0; i < Tcpclientsocketlist.count(); i++)
    {
        QTcpSocket *item = Tcpclientsocketlist.at(i);
        if(item->socketDescriptor() == descriptor)
        {
            qDebug()<<item<<"disconnect!!!";
            Tcpclientsocketlist.removeAt(i);
            return;
        }
    }
    return;
}
