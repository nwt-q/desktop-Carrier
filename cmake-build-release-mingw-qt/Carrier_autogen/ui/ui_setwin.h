/********************************************************************************
** Form generated from reading UI file 'setwin.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETWIN_H
#define UI_SETWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetWin
{
public:
    QSlider *sizeSlider;
    QLabel *sizeLabel;
    QLabel *openLabel;
    QCheckBox *openBox;

    void setupUi(QWidget *SetWin)
    {
        if (SetWin->objectName().isEmpty())
            SetWin->setObjectName("SetWin");
        SetWin->resize(350, 200);
        sizeSlider = new QSlider(SetWin);
        sizeSlider->setObjectName("sizeSlider");
        sizeSlider->setGeometry(QRect(40, 120, 200, 21));
        sizeSlider->setCursor(QCursor(Qt::CrossCursor));
        sizeSlider->setMinimum(60);
        sizeSlider->setMaximum(1600);
        sizeSlider->setSingleStep(20);
        sizeSlider->setPageStep(20);
        sizeSlider->setTracking(true);
        sizeSlider->setOrientation(Qt::Horizontal);
        sizeLabel = new QLabel(SetWin);
        sizeLabel->setObjectName("sizeLabel");
        sizeLabel->setGeometry(QRect(250, 110, 81, 41));
        openLabel = new QLabel(SetWin);
        openLabel->setObjectName("openLabel");
        openLabel->setGeometry(QRect(60, 40, 221, 61));
        openBox = new QCheckBox(SetWin);
        openBox->setObjectName("openBox");
        openBox->setGeometry(QRect(40, 40, 21, 61));
        openBox->setCursor(QCursor(Qt::PointingHandCursor));

        retranslateUi(SetWin);

        QMetaObject::connectSlotsByName(SetWin);
    } // setupUi

    void retranslateUi(QWidget *SetWin)
    {
        SetWin->setWindowTitle(QCoreApplication::translate("SetWin", "Form", nullptr));
        sizeLabel->setText(QCoreApplication::translate("SetWin", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600; color:#000051;\">\345\260\272</span><span style=\" font-size:12pt; font-weight:600; color:#000051;\">\345\257\270</span></p></body></html>", nullptr));
        openLabel->setText(QCoreApplication::translate("SetWin", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600; color:#00006c;\">\345\274\200\346\234\272</span><span style=\" font-size:12pt; font-weight:600; color:#00006c;\">\350\207\252\345\220\257</span></p></body></html>", nullptr));
        openBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SetWin: public Ui_SetWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETWIN_H
