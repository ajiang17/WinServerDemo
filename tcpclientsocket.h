#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QTcpSocket>

class TcpClientSocket: public QTcpSocket
{
    Q_OBJECT
public:
    TcpClientSocket(QObject *parent = 0);
protected slots:
    void receivedata();
    void slotclientdisconnected();

signals:
    void updataserver(QString,int);
    void clientdisconnected(int);
};

#endif // TCPCLIENTSOCKET_H
