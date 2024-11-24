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
    auto setSize(int) -> void;//设置size值
    //[[nodiscard]]  用于指示函数的返回值不应该被忽略
    [[nodiscard]] auto getSize() const -> int;//外部获取size值
private slots:
    //[[maybe_unused]] 是一个属性，用来告诉编译器某个函数、变量或参数可能在某些编译单元中不会被使用，
    //因此即使编译器检测到该函数、变量或参数没有被使用，也不会发出未使用的警告
    [[maybe_unused]] void on_sizeSlider_valueChanged(int value);//滑动条槽函数
private:
    Ui::SetWin *ui;
    //对变量进行列表初始化
    int CarrierSize{}; // CarrierSize大小参数
    QLabel *sizeNum{};//显示size值标签
};

#endif //QT_SETWIN_H
