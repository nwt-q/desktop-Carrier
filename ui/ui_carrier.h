/********************************************************************************
** Form generated from reading UI file 'Carrier.ui'
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

class Ui_Carrier
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Carrier)
    {
        if (Carrier->objectName().isEmpty())
            Carrier->setObjectName("Carrier");
        Carrier->resize(2800, 2400);
        Carrier->setCursor(QCursor(Qt::ArrowCursor));
        Carrier->setMouseTracking(true);
        centralwidget = new QWidget(Carrier);
        centralwidget->setObjectName("centralwidget");
        Carrier->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Carrier);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 2800, 21));
        Carrier->setMenuBar(menubar);
        statusbar = new QStatusBar(Carrier);
        statusbar->setObjectName("statusbar");
        Carrier->setStatusBar(statusbar);

        retranslateUi(Carrier);

        QMetaObject::connectSlotsByName(Carrier);
    } // setupUi

    void retranslateUi(QMainWindow *Carrier)
    {
        Carrier->setWindowTitle(QCoreApplication::translate("Carrier", "Carrier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Carrier: public Ui_Carrier {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARRIER_H
