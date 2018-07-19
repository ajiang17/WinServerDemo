#ifndef MAINWINSERVER_H
#define MAINWINSERVER_H

#include <QMainWindow>

#include "serialport.h"
#include "scanserialportinfo.h"
#include "printfeatures.h"
#include "tcpserver.h"

#include <QTimer>
#include <QList>
#include <QMutex>
#include <QMap>
#include <QTcpSocket>
#include <qtcpsocket.h>
#include <QHostAddress>
#include "mytcprecvserver.h"
#include <qsystemtrayicon.h>
#define MAXTHREADNUM 20  // 最大监控20个串口


namespace Ui {
class MainWinServer;
}

class MainWinServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWinServer(QWidget *parent = 0);
    ~MainWinServer();

    void InitCom(); // 初始化串口
    void Readregedit(bool isAutoRun); // 写注册表信息
    void doPrint(QByteArray temp); // 执行打印
    void UpSerialThread(QStringList AddThreadList, QStringList SubThreadList);
    void InitThreadPools(); // 初始化线程池
    void RunThread(); // 运行
    void CreatNewWorkThread(QString name); // 创建新线程
    void StartThread();  // 启动
    void CloseThread(); // 关闭所有线程
    void StopThread(QString protname); // 停止线程

    void TCPIPInit();               //初始化
    void TCPIPConnection();         //TCP/IP连接
    void SetAppIcon();              //设置APP的ICON
    void SettrayIcon();             //这只通知ICON
    void iconActivated(QSystemTrayIcon::ActivationReason);

protected:

    QList<QThread *> m_IdleThreadPool; // 空闲线程

    QMap<SerialPort *,QThread *> m_SerailThreadMap; // 串口实例--工做线程

signals:
    void starSerialThread(); // 启动子线程信号
    void UpdateSerial(QStringList AddThreadList, QStringList SubThreadList);  // 更新串口列表
private slots:
    void timerScanSerial(); // 扫描串口
    void sendtoPrinterMessage();     //TCP/IP通讯发送函数
    void readMessage();
    void slotconnectedsuccess();
    void displayError(QAbstractSocket::SocketError);
private:
    Ui::MainWinServer *ui;
    QTimer *m_timer;     // 启动定时
    QStringList m_ports;  // 存放串口名
    QMutex m_mutex;
    QThread * SurveillanceThread;  // 监视线程
    int m_printNum;   // 打印数量
    PrintFeatures *printer; // 打印功能实例
    QTcpSocket *tcpSocket;  //tcp服务Soecket
    QHostAddress *serverIP;
    QString message;  //存放从服务器接收到的字符串
    quint16 blockSize;  //存放文件的大小信息
    TcpServer *server;
    //Mytcprecvserver *server;
    QString StrSentToPrinter;

protected slots:
    void slotupdateserver(QString, int);
};

#endif // MAINWINSERVER_H
