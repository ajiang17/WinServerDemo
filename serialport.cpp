#include "serialport.h"
#include <QSettings>
#include <QFile>
#include <QDebug>

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{ 
    m_isStop = false;
    m_isOpen = false;


}

void SerialPort::InitSerialName(QString name)
{
    m_portName = name;


}

void SerialPort::doReadData()
{
    m_serialport = new QSerialPort();
    m_serialport->setPortName(m_portName);
    if (!OpenSerial())
    {
        delete m_serialport;
        emit Failsignal(m_portName);
        m_isStop = true;
    }



    while (false == m_isStop)
    {
        // 接收到的数据写入文件
        if (true == m_isStop)
        {
            //CloseSerial(port);
            if (m_serialport->isOpen())
            {
                m_serialport->close();
            }
            break;
        }


        bool bsucc = m_serialport->waitForReadyRead(10000);
        if(!bsucc)
        {
                qDebug() << m_serialport->portName() << ": waitForReadyRead timeout";
                //doSendData("");
                continue;
        }

        qDebug() << m_serialport->portName() << "子线程ID:" << QThread::currentThreadId();
        // 读取数据
        QByteArray temp = m_serialport->readAll();
        // 防止数据没有读取完整
        while (1)
        {
            bsucc = m_serialport->waitForReadyRead(10);
            if (!bsucc)
            {
                break;
            }
            temp += m_serialport->readAll();
        }
        qDebug() << "接收到非空数据";
        qDebug() << temp;
        QFile file("ReadData.txt");
        if (file.open(QIODevice::Append))
        {
            qint64 LineLen = file.write(temp);
            if (-1 == LineLen)
            {
               qDebug() << "write error!";
            }
            file.close();
        }
        // 数据解析
        QString str;
        str.prepend(temp);
        emit Readsignal(temp);
        doSendData(str);
        //emit SendDataSig(str);
        temp.clear();
    }

}

// 发送数据
void SerialPort::doSendData(QSerialPort *port,QString data)
{
    if (data.isEmpty())
    {
        port->write("hello");
    }
}

void SerialPort::doSendData(QString &data)
{
    if (data.isEmpty())
    {
        m_serialport->write("hello");
    }
    else
    {
        m_serialport->write(data.toLatin1(),data.size());
    }

}

void SerialPort::setFlage(bool flage)
{
    m_isStop = flage;
}

QString SerialPort::GetPortName()
{
    return m_portName;
}

// 是否打开
bool SerialPort::GetIsOpen()
{
    return m_isOpen;
}

// 打开串口
bool SerialPort::OpenSerial(QSerialPort *port)
{
    // 打开对应串口
    if (port->open(QIODevice::ReadWrite))
    {
        // 设置串口相应信息：波特率--停止位--数据位--校验位--流控制
        port->setBaudRate(QSerialPort::Baud115200);
        port->setParity(QSerialPort::NoParity);
        port->setStopBits(QSerialPort::OneStop);
        port->setDataBits(QSerialPort::Data8);
        port->setFlowControl(QSerialPort::NoFlowControl);
        qDebug() << "串口" << port->portName() << QThread::currentThreadId();
        //connect(m_port, SIGNAL(readyRead()), this, SLOT(ReadData()));
        m_isOpen = true;
        return true;
    }
    else
    {
        qDebug() << "串口" << port->portName() << "打开失败！";
        m_isOpen = false;
        return false;
    }

}

bool SerialPort::OpenSerial()
{
    // 打开对应串口
    if (m_serialport->open(QIODevice::ReadWrite))
    {
        // 设置串口相应信息：波特率--停止位--数据位--校验位--流控制
        if (!m_serialport->setBaudRate(QSerialPort::Baud115200))
        {
            qDebug() << "设置波特率不成功";
            return false;
        }
        if (!m_serialport->setParity(QSerialPort::NoParity))
        {
            qDebug() << "设置校验位不成功";
            return false;
        }
        if (!m_serialport->setStopBits(QSerialPort::OneStop))
        {
            qDebug() << "设置停止位不成功";
            return false;
        }
        if (!m_serialport->setDataBits(QSerialPort::Data8))
        {
            qDebug() << "设置数据位不成功";
            return false;
        }
        if (!m_serialport->setFlowControl(QSerialPort::NoFlowControl))
        {
            qDebug() << m_serialport->portName() <<"设置流控制不成功";
            return false;
        }

        m_serialport->setReadBufferSize(1024);
        //qDebug() << m_serialport->readBufferSize();
        qDebug() << "串口" << m_serialport->portName() << QThread::currentThreadId();
        //qDebug() << m_serialport->error();
        m_serialport->clearError();
        //connect(m_serialport, &QSerialPort::readyRead, this, &SerialPort::ReadData);
        //QObject::connect(this, &SerialPort::SendDataSig, this, &SerialPort::doSendData);
        m_isOpen = true;
        return true;
    }
    else
    {
        qDebug() << "串口" << m_serialport->portName() << "打开失败！";
        m_isOpen = false;
        return false;
    }

}

// 关闭串口
void SerialPort::CloseSerial(QSerialPort *port)
{
    if (port->isOpen())
    {
        port->close();
    }
}

// 读取数据
void SerialPort::ReadData()
{
    // 读取数据
    QByteArray temp = m_serialport->readAll();
    qDebug() << m_serialport->portName() << "子线程ID:" << QThread::currentThreadId();
    m_serialport->waitForReadyRead(10000);
    if (!temp.isEmpty())
    {
        qDebug() << temp;
        QFile file("ReadData.txt");
        if (file.open(QIODevice::Append))
        {
            qint64 LineLen = file.write(temp);
            if (-1 == LineLen)
            {
               qDebug() << "write error!";
            }
            file.close();
        }
        // 数据解析
        emit Readsignal(temp);
        temp.clear();
    }
}
