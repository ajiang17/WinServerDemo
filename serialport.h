#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QString>
#include <windows.h>
#include <QMutex>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = 0);

    void InitSerialName(QString name);

    void doReadData(); // 读数据
    void doSendData(QString &data); // 发送数据
    void setFlage(bool flage = true);

    void AnalyticalData(QByteArray array);  // 数据解析


    QString GetPortName(); // 获得串口名
    bool GetIsOpen();   // 获取是否已经打开串口

    // 打开串口
    bool OpenSerial();
    void CloseSerial(); // 关闭串口

public:

    QStringList m_comlist ; // 存放串口名
    QString m_portName;
    bool m_isOpen;
    QMutex m_mutex;

signals:
    void Readsignal(QByteArray temp);
    void Failsignal(QString protname);
    void SendDataSig(QString &data);

public slots:

private:


    QSerialPort * m_serialport;
    bool m_isStop;

};

#endif // SERIALPORT_H
