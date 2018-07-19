#include "scanserialportinfo.h"
#include <QDebug>

ScanSerialPortInfo::ScanSerialPortInfo(QObject *parent) : QObject(parent)
{
    InitSerialInfo();
}

void ScanSerialPortInfo::InitSerialInfo()
{
    m_listcomboName.clear();
    QString path = "HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
    QSettings* settings = new QSettings(path, QSettings::NativeFormat);
    QStringList key = settings->allKeys();
    int num = (int)key.size();
    QString value;
    for(int i = 0; i < num; i++)
    {
        value = GetComName(i,"value");
        m_listcomboName << value;
    }
    removeListSame();
    delete settings;
    qDebug() << m_listcomboName;
}

QString ScanSerialPortInfo::GetComName(int index, QString keyorvalue)
{
    QString commresult;
    HKEY hKey;

    if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_READ, &hKey) != 0)
    {
        QString error="无法打开注册表!";//无法打开注册表时返回error
        return error;
    }

    QString keymessage;//键名
    QString message;
    QString valuemessage;//键值

    indexnum = index;//要读取键值的索引号
    keysize = sizeof(keyname);
    valuesize = sizeof(keyvalue);

    if (::RegEnumValue(hKey, indexnum, keyname, &keysize, 0, &type, (BYTE*)keyvalue, &valuesize) == 0)//列举键名和值
    {
        for(int i = 0 ; i < keysize; i++)
        {
            message = keyname[i];
            keymessage.append(message);
        }// 读取键名

        for (int j = 0; j < valuesize; j++)
        {
             if (keyvalue[j] != 0x00)
             {
                 valuemessage.append(keyvalue[j]);
             }

        }//for(intj=0;j<valuesize;j++)读取键值

        if(keyorvalue == "key")
        {
             commresult = keymessage;
        }

        if(keyorvalue == "value")
        {
           commresult = valuemessage;
        }
    }
    else
    {
         commresult = "nokey";

    }

    ::RegCloseKey(hKey);//关闭注册表
    return commresult;
}

QStringList ScanSerialPortInfo::GetSerialName()
{
    return this->m_listcomboName;
}

void ScanSerialPortInfo::timerScanSerial()
{

}

void ScanSerialPortInfo::removeListSame()
{
    for (int i = 0; i < m_listcomboName.count(); i++)
    {
        for (int k = i + 1; k <  m_listcomboName.count(); k++)
        {
            if ( m_listcomboName.at(i) ==  m_listcomboName.at(k))
            {
                m_listcomboName.removeAt(k);
                k--;
            }
        }
    }
}
