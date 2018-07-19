#ifndef SCANSERIALPORTINFO_H
#define SCANSERIALPORTINFO_H

#include <qt_windows.h>
#include <QSettings>

class ScanSerialPortInfo : public QObject
{
    Q_OBJECT
public:
    explicit ScanSerialPortInfo(QObject *parent = nullptr);

    void InitSerialInfo(); // 初始化串口信息
    QString GetComName(int index,QString keyorvalue); //读取键名
    QStringList GetSerialName();  // 返回读取到的串口信息
    void timerScanSerial();
    void removeListSame(); // 删除重复的项

signals:
    void UpdateSerial(QStringList AddThreadList, QStringList SubThreadList);  // 更新串口列表
public slots:

private:
    QStringList m_listcomboName;

    LPCWSTR subkey;
    wchar_t keyname[256]; //键名数组
    char keyvalue[256];  //键值数组
    DWORD keysize,type,valuesize;
    int indexnum;
};

#endif // SCANSERIALPORTINFO_H
