#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
{
    qDebug()<<"-----------------";
    connect(this,&TcpClientSocket::readyRead,this,&TcpClientSocket::receivedata);
    connect(this,&TcpClientSocket::disconnected,this,&TcpClientSocket::slotclientdisconnected);
    //connect(this,&TcpClientSocket::readyRead,&)
}

void TcpClientSocket::receivedata()
{
    //qDebug()<<"-----------------";
    int length = 10;
    QByteArray array = readAll();
    QString msg = array;
    qDebug()<<msg;
    emit updataserver(msg,length);
}

void TcpClientSocket::slotclientdisconnected()
{
    emit clientdisconnected(this->socketDescriptor());
}
