#ifndef PRINTFEATURES_H
#define PRINTFEATURES_H
#include <Windows.h>
#include <QObject>
#include "qrencode.h"
#include <QPixmap>

class PrintFeatures: public QObject
{
    Q_OBJECT
public:
    explicit PrintFeatures(QObject *parent = 0);

    void Init(QString tempstr);

public:

    QPixmap Generate_QRcode(QString tempstr);
    void GenerateLogoQRcode(QString strName); // 生成带Logo的二维码
    int doPrint(); // 执行打印动作

    void ClearPrinter();

    QPixmap m_LogoMap;

private:

};

#endif // PRINTFEATURES_H
