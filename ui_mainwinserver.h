/********************************************************************************
** Form generated from reading UI file 'mainwinserver.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINSERVER_H
#define UI_MAINWINSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWinServer
{
public:
    QWidget *centralWidget;
    QLabel *PictureLable;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWinServer)
    {
        if (MainWinServer->objectName().isEmpty())
            MainWinServer->setObjectName(QStringLiteral("MainWinServer"));
        MainWinServer->resize(552, 420);
        centralWidget = new QWidget(MainWinServer);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PictureLable = new QLabel(centralWidget);
        PictureLable->setObjectName(QStringLiteral("PictureLable"));
        PictureLable->setGeometry(QRect(80, 110, 91, 71));
        PictureLable->setMinimumSize(QSize(91, 0));
        MainWinServer->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWinServer);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 552, 23));
        MainWinServer->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWinServer);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWinServer->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWinServer);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWinServer->setStatusBar(statusBar);

        retranslateUi(MainWinServer);

        QMetaObject::connectSlotsByName(MainWinServer);
    } // setupUi

    void retranslateUi(QMainWindow *MainWinServer)
    {
        MainWinServer->setWindowTitle(QApplication::translate("MainWinServer", "MainWinServer", Q_NULLPTR));
        PictureLable->setText(QApplication::translate("MainWinServer", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWinServer: public Ui_MainWinServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINSERVER_H
