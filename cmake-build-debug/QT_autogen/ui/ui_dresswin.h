/********************************************************************************
** Form generated from reading UI file 'dresswin.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRESSWIN_H
#define UI_DRESSWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DressWin
{
public:

    void setupUi(QWidget *DressWin)
    {
        if (DressWin->objectName().isEmpty())
            DressWin->setObjectName("DressWin");
        DressWin->resize(450, 530);

        retranslateUi(DressWin);

        QMetaObject::connectSlotsByName(DressWin);
    } // setupUi

    void retranslateUi(QWidget *DressWin)
    {
        DressWin->setWindowTitle(QCoreApplication::translate("DressWin", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DressWin: public Ui_DressWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRESSWIN_H
