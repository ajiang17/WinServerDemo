#ifndef MAINWINSERVER_H
#define MAINWINSERVER_H

#include <QMainWindow>
#include "serialport.h"
#include "scanserialportinfo.h"
#include "printfeatures.h"
#include <QTimer>
#include <QList>
#include <QMutex>
#include <QMap>

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

protected:

    QList<QThread *> m_IdleThreadPool; // 空闲线程

    QMap<SerialPort *,QThread *> m_SerailThreadMap; // 串口实例--工做线程

signals:
    void starSerialThread(); // 启动子线程信号
    void UpdateSerial(QStringList AddThreadList, QStringList SubThreadList);  // 更新串口列表
private slots:
    void timerScanSerial(); // 扫描串口
private:
    Ui::MainWinServer *ui;
    QTimer *m_timer;     // 启动定时
    QStringList m_ports;  // 存放串口名
    QMutex m_mutex;
    QThread * SurveillanceThread;  // 监视线程
    int m_printNum;   // 打印数量
    PrintFeatures *printer; // 打印功能实例
};

#endif // MAINWINSERVER_H
