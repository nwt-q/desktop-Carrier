//
// Created by NWT on 2024/11/17.
//

#ifndef QT_SETWIN_H
#define QT_SETWIN_H
#include <QWidget>
#include <QPainter>
#include <QLabel>

namespace Ui {class SetWin;}

class SetWin : public QWidget{
    Q_OBJECT
public:
    explicit SetWin(QWidget *parent = nullptr);
    ~SetWin() override;
    void setSize(int);//设置size值
    int getSize();//外部获取size值
private slots:
    void on_sizeSlider_valueChanged(int value);//滑动条槽函数
private:
    Ui::SetWin *ui;
    int CarrierSize; // CarrierSize大小参数
    QLabel *sizeNum;//显示size值标签
};


#endif //QT_SETWIN_H
