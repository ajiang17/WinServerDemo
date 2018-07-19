#include "mainwinserver.h"
#include "ui_mainwinserver.h"
#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QNetworkProxyFactory>


MainWinServer::MainWinServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWinServer),
    m_printNum(0)
{
//    ui->setupUi(this);
    Readregedit(true); // 开机启动
    //SetAppIcon();
    //SettrayIcon();

//    m_IdleThreadPool.clear();
//    m_SerailThreadMap.clear();

//    InitThreadPools(); // 初始化线程池
//    qDebug() << "主线程ID:" << QThread::currentThreadId();  //显示当前线程的数值
//    RunThread();

//    m_timer = new QTimer(this);
//    connect(m_timer,SIGNAL(timeout()),this,SLOT(timerScanSerial()));
//    m_timer->start(3000);  // 3秒扫描一次串口信息

//    // 更新状态并重新打开连接
//    connect(this, &MainWinServer::UpdateSerial, this, &MainWinServer::UpSerialThread);
    TCPIPInit();
    TCPIPConnection();
    server = new TcpServer(this,8888);
    connect(server,&TcpServer::updateMsgx,this,&MainWinServer::slotupdateserver);
    connect(server,&TcpServer::updateMsgx,this,&MainWinServer::sendtoPrinterMessage);
}
void MainWinServer::slotupdateserver(QString msg, int length)
{
    qDebug()<<"eeeeeeeeeeeeeeee"<<msg;
    StrSentToPrinter = "";
    StrSentToPrinter = msg;
}

MainWinServer::~MainWinServer()
{
    //m_timer->stop();
    //CloseThread();


    //delete m_timer;
    delete ui;
}

void MainWinServer::Readregedit(bool isAutoRun)
{
    // HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run  当前用户
    // HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run 系统用户
    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);

    //开机自动运行
    if(isAutoRun)
    {
         QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
         reg->setValue("printServer",strAppPath);
    }
    else
    {
      reg->setValue("printServer","");
    }

    delete reg;
}

// 打印功能，里面实现实时发送剩余打印数量
void MainWinServer::doPrint(QByteArray temp)
{
    m_mutex.lock();
    QString str;
    str.append(temp);
    printer = new PrintFeatures();
    printer->Init(str);
    // 获取打印数量
    qDebug() << "待打印数据为：" << str;
    // 执行打印动作
    printer->doPrint();
    QThread::sleep(2);
    delete printer;
    m_mutex.unlock();
}

// 根据串口数量新增或者减少监控线程
void MainWinServer::UpSerialThread(QStringList AddThreadList, QStringList SubThreadList)
{
    // 回收线程
    // 判断串口是否存在，不存在则停止线程并回收到线程池

   if (SubThreadList.isEmpty())
   {
       if (AddThreadList.isEmpty())
       {
           return;
       }

   }

   qDebug() << "进入了更新部分";
   if (!SubThreadList.isEmpty())
   {
       // 删除已经没有的串口
        QMap<SerialPort *,QThread *>::iterator it;
        for (it = m_SerailThreadMap.begin(); it != m_SerailThreadMap.end(); ++it)
        {
            if (SubThreadList.contains(it.key()->GetPortName()))
            {
                it.key()->setFlage(true);
                it.value()->terminate();
                delete it.key();
                delete it.value();
                m_SerailThreadMap.remove(it.key());
                QThread * pNewThread = new QThread(this);
                m_IdleThreadPool.append(pNewThread);
            }
        }
   }

   // 判断是否新增了串口，为新增串口增加线程扫描数据
   if (!AddThreadList.isEmpty())
   {
       qDebug() << "进入新增功能函数中....";
       for (int i = 0; i < AddThreadList.size(); i++)
       {
           qDebug() << AddThreadList.at(i);
           CreatNewWorkThread(AddThreadList.at(i));
       }
   }

   StartThread();
}

// 初始化线程池
void MainWinServer::InitThreadPools()
{
    for (int i = 0; i < MAXTHREADNUM; i++)
    {
        QThread * pNewThread = new QThread(this);
        m_IdleThreadPool.append(pNewThread);
    }
}

void MainWinServer::RunThread()
{
    ScanSerialPortInfo *serialinfo = new ScanSerialPortInfo(); // 串口信息
    QStringList portname;
    portname = serialinfo->GetSerialName();
    m_ports.clear();
    m_ports = portname;
    int size = portname.size();
    for (int i = 0; i < size; i++)
    {
        CreatNewWorkThread(portname.at(i));
    }

    //CreatNewWorkThread("COM5");
    StartThread();
    delete serialinfo;
}

// 为新串口创建线程
void MainWinServer::CreatNewWorkThread(QString name)
{
    SerialPort *port = new SerialPort();
    port->InitSerialName(name);
    QThread * thread = m_IdleThreadPool.at(0);
    m_IdleThreadPool.removeAt(0);
    port->moveToThread(thread);
    m_SerailThreadMap.insert(port,thread);
    connect(port, &SerialPort::Readsignal, this, &MainWinServer::doPrint);
    connect(port, &SerialPort::Failsignal, this, &MainWinServer::StopThread);
    connect(this, &MainWinServer::starSerialThread, port, &SerialPort::doReadData);
}

// 开始线程工做
void MainWinServer::StartThread()
{
    QMap<SerialPort *,QThread *>::iterator it;
    for (it = m_SerailThreadMap.begin(); it != m_SerailThreadMap.end(); ++it)
    {
        if (!it.value()->isRunning())
        {
             it.key()->setFlage(false);
             it.value()->start();
             emit starSerialThread();
        }
    }
}

// 关闭所有线程
void MainWinServer::CloseThread()
{
    QMap<SerialPort *,QThread *>::iterator it;
    for (it = m_SerailThreadMap.begin(); it != m_SerailThreadMap.end(); ++it)
    {
        if (it.value()->isRunning())
        {
             it.key()->setFlage(true);
             it.value()->terminate();
             delete it.key();
             delete it.value();
        }
    }


    for (int i = 0; i < m_IdleThreadPool.size(); i++)
    {
        m_IdleThreadPool.at(i)->terminate();
        delete m_IdleThreadPool.at(i);
    }

    m_SerailThreadMap.clear();
    m_IdleThreadPool.clear();
}

// 停止线程
void MainWinServer::StopThread(QString protname)
{
    m_mutex.lock();
    QMap<SerialPort *,QThread *>::iterator it;
    for (it = m_SerailThreadMap.begin(); it != m_SerailThreadMap.end(); ++it)
    {
        if (protname.contains(it.key()->GetPortName()))
        {
            it.key()->setFlage(true);
            it.value()->terminate();
            delete it.key();
            delete it.value();
            m_SerailThreadMap.remove(it.key());
            QThread * pNewThread = new QThread(this);
            m_IdleThreadPool.append(pNewThread);
        }
    }
    m_mutex.unlock();
}

// 扫描串口
void MainWinServer::timerScanSerial()
{
    Sleep(2000);
    QStringList Newports;
    QStringList AddThreadList;
    QStringList SubThreadList;
    ScanSerialPortInfo *serialinfo = new ScanSerialPortInfo(); // 串口信息
    // 更新串口信息
    Newports.clear();
    Newports = serialinfo->GetSerialName();

    // 获取新增加的串口
    int size = Newports.size();
    for (int i = 0; i < size; i++)
    {
        if (!m_ports.contains(Newports.at(i)))
        {
            AddThreadList << Newports.at(i);
        }
    }

    // 获取已经减少的串口
    for (int i = 0; i < m_ports.size(); i++)
    {
        if (!Newports.contains(m_ports.at(i)))
        {
            SubThreadList << m_ports.at(i);
        }
    }

    m_ports.clear();

    for (int i = 0; i < size; i++)
    {
        m_ports << Newports.at(i);
    }

    if (AddThreadList.isEmpty())
    {
        if (SubThreadList.isEmpty())
        {
            delete serialinfo;
            return;
        }

    }

    delete serialinfo;
    emit UpdateSerial(AddThreadList, SubThreadList);
}

void MainWinServer::TCPIPInit()
{
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    tcpSocket = new QTcpSocket(this);
    serverIP = new QHostAddress();

    connect(tcpSocket,&QTcpSocket::readyRead,this,MainWinServer::readMessage);
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
}


void MainWinServer::TCPIPConnection()
{

    blockSize = 0;
    //tcpSocket->abort();//取消已有的连接
    QString strServIPAddr = "192.168.1.137";
    if(!serverIP->setAddress(strServIPAddr))
    {
        qDebug()<<"your server IP Adrress is Error";
    }
    tcpSocket->connectToHost(strServIPAddr,9100);
    connect(tcpSocket,&QTcpSocket::connected,this,&MainWinServer::slotconnectedsuccess);
}

void MainWinServer::readMessage()
{
    QDataStream in(tcpSocket);
    QByteArray array = tcpSocket->readAll();
    qDebug()<<array;
    //in.setVersion(QDataStream::Qt_4_6);
}

void MainWinServer::slotconnectedsuccess()
{
    qDebug()<<"Connect Success with printer!!";
    //StrSentToPrinter
    QString msg = "^XA\n^MD23\n^PW200\n^FO30,30\n^BQN,2,6\n^FDD03048F,LM,N0123456789,A12AABB,B0006qrcodeFS\n^XZ";
    //qDebug()<<msg;
    //tcpSocket->write(msg.toUtf8().data());
}


void MainWinServer::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString(); //输出错误信息
}

void MainWinServer::sendtoPrinterMessage()
{

    QString msg = "^XA\n^MD23\n~TA100\n^FO50,50\n^A0,10,10\n^FDZEBRA^FS\n^FO70,50\n^BQN,2,6\n^FDMM,A"+StrSentToPrinter +"^PLa255\n^FS\n^XZ";
    QString msg1;
    msg1.append("^XA\n");
    msg1.append("^MD23\n");
    msg1.append("^LH60,10\n");
    msg1.append("^FO50,50\n");
    msg1.append("^BQN,2,6\n");
    msg1.append("^FDMM,A");
    msg1.append(StrSentToPrinter);
    msg1.append("^FS\n");
    msg1.append("^XZ");
    qDebug()<<"---------------------------------------" + msg;
    qDebug()<<"---------------------------------------" + msg1;
    tcpSocket->write(msg1.toUtf8().data());
}
//111111111111111111111111111111111111
void MainWinServer::SetAppIcon()
{
    setWindowIcon(QIcon("logo.png"));
}
void MainWinServer::SettrayIcon()
{
    QSystemTrayIcon *trayIcon= new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("logo.png"));
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason )),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();
}
void MainWinServer::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    qDebug()<<"---------------------";
    switch(reason)
    {
        case QSystemTrayIcon::DoubleClick :
           setWindowState(Qt::WindowActive);
           //w.show();
           activateWindow();
           break;
        default:
           break;
    }
}
