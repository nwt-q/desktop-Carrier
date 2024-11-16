/********************************************************************************
** Form generated from reading UI file 'musicwin.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICWIN_H
#define UI_MUSICWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicWin
{
public:

    void setupUi(QWidget *MusicWin)
    {
        if (MusicWin->objectName().isEmpty())
            MusicWin->setObjectName("MusicWin");
        MusicWin->resize(450, 450);
        MusicWin->setCursor(QCursor(Qt::ArrowCursor));

        retranslateUi(MusicWin);

        QMetaObject::connectSlotsByName(MusicWin);
    } // setupUi

    void retranslateUi(QWidget *MusicWin)
    {
        MusicWin->setWindowTitle(QCoreApplication::translate("MusicWin", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MusicWin: public Ui_MusicWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICWIN_H
