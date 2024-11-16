/********************************************************************************
** Form generated from reading UI file 'carrier.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARRIER_H
#define UI_CARRIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Haro
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Haro)
    {
        if (Haro->objectName().isEmpty())
            Haro->setObjectName("Haro");
        Haro->resize(2800, 2400);
        Haro->setCursor(QCursor(Qt::ArrowCursor));
        Haro->setMouseTracking(true);
        centralwidget = new QWidget(Haro);
        centralwidget->setObjectName("centralwidget");
        Haro->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Haro);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 2800, 21));
        Haro->setMenuBar(menubar);
        statusbar = new QStatusBar(Haro);
        statusbar->setObjectName("statusbar");
        Haro->setStatusBar(statusbar);

        retranslateUi(Haro);

        QMetaObject::connectSlotsByName(Haro);
    } // setupUi

    void retranslateUi(QMainWindow *Haro)
    {
        Haro->setWindowTitle(QCoreApplication::translate("Haro", "Haro", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Haro: public Ui_Haro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARRIER_H
