#include "printfeatures.h"
#include <stdio.h>
#include <QPrinter>
#include <QPainter>
#include <QDebug>

PrintFeatures::PrintFeatures(QObject *parent) : QObject(parent)
{

}

void PrintFeatures::Init(QString tempstr)
{
    GenerateLogoQRcode(tempstr);
}

// 绘制二维码
QPixmap PrintFeatures::Generate_QRcode(QString tempstr)
{
    QRcode *qrcode = new QRcode(); //QRcode data
    qrcode = QRcode_encodeString(tempstr.toStdString().c_str(), 2, QR_ECLEVEL_Q, QR_MODE_8, 1);
    qint32 temp_width = 237;
    qint32 temp_height = 237;
    qint32 qrcode_width = qrcode->width > 0 ? qrcode->width : 1;
    double scale_x = (double)temp_width / (double)qrcode_width;
    double scale_y =(double) temp_height /(double) qrcode_width;
    QImage img = QImage(temp_width,temp_height,QImage::Format_ARGB32);
    QPixmap map = QPixmap::fromImage(img);
    QPainter painter;
    painter.begin(&map);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, temp_width, temp_height);
    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    for( qint32 y = 0; y < qrcode_width; y ++)
    {
        for(qint32 x = 0; x < qrcode_width; x++)
        {
            unsigned char b = qrcode->data[y * qrcode_width + x];
            if(b & 0x01)
            {
                QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }
    painter.end();
    QRcode_free(qrcode);
    return map;
}

void PrintFeatures::GenerateLogoQRcode(QString strName)
{
    QImage resultImage;
    QPixmap qrcodemap;
    qrcodemap = Generate_QRcode(strName);
    QImage image = qrcodemap.toImage();
    QSize resultSize;
    resultSize.setWidth(image.width());
    resultSize.setHeight(image.height());
    resultImage = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    QImage logoimage("logo.png");
    QSize logoSize;
    logoSize.setWidth(image.width()*0.4);
    logoSize.setHeight(image.height()*0.4);
    QImage newImage = logoimage.scaled(logoSize);
    QPoint logoPoint((image.width() - newImage.width()) / 2,
                             (image.height() - newImage.height()) / 2);
    painter.drawImage(logoPoint, newImage);

    painter.setCompositionMode(QPainter::CompositionMode_DestinationAtop);
    painter.drawImage(0, 0, image);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);

    painter.fillRect(resultImage.rect(), Qt::white);
    painter.end();
    m_LogoMap = QPixmap::fromImage(resultImage);
    m_LogoMap.save("QRcode.jpg");
}

// 打印
int PrintFeatures::doPrint()
{
    qDebug() << "准备打印工作";

    QPrinter *printer = new QPrinter(QPrinter::ScreenResolution);
    QString printername = printer->printerName();

    if (printername.isEmpty())
    {
        qDebug() << "找不到打印机！";
        return -1;
    }

    QPainter painter(printer);
    QRect rect = painter.viewport();
    QSize s = m_LogoMap.size();
    s.scale(rect.size(), Qt::IgnoreAspectRatio);//根据rect的尺寸改变的是s的尺寸，并且保证s的长宽比
    painter.setViewport(rect.x(), rect.y(),
    s.width(), s.height());
    // 发送剩余打印数量
    m_LogoMap = m_LogoMap.scaled(QSize(64,64), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.setWindow(m_LogoMap.rect());
    painter.drawPixmap(QPoint(50,32), m_LogoMap);
    painter.end();

    delete printer;
    return 0;
}


// 做清理工作
void PrintFeatures::ClearPrinter()
{

}
