/**
******************************************************************************
* @file    dresswin.h
* @brief   This file contains all the function prototypes for
*          the dresswin.cpp file
******************************************************************************
* @attention Created by NWT on 2024/11/16.
*
* Copyright (c) 2024
* All rights reserved.
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
*/
#ifndef QT_DRESSWIN_H
#define QT_DRESSWIN_H
#include <QWidget>
#include <QPainter>
#include <QButtonGroup>
#include <QPushButton>
#include <QWheelEvent>

const int NUM = 8;//装扮数量

namespace Ui {
    class DressWin;
}
/**
 *
 * @author EvLast
 * @version 1.1.0
 * @since Haro
 */
class DressWin : public QWidget {
    Q_OBJECT
public:
    explicit DressWin(QWidget *parent = nullptr);
    ~DressWin();
    int getBodyid() const;
    int getEarsid() const;
    void wheelEvent(QWheelEvent *event) override;
    void paintEvent(QPaintEvent *) override; //绘画事件
    void accept(std::vector<QPixmap>& body,std::vector<QPixmap>& ears,int bodyid,int earsid);
private:
    void initBtn();//初始化按钮
//signals:

//private slots:

private:
    Ui::DressWin * ui;
    QButtonGroup *bodyBox,*earsBox; //按钮组 => 用于捕获点击事件
    std::vector<QPixmap> body,ears; //各部件对应图片容器 => 将图片放容器中
    QPushButton *bodyBtn[NUM],*earsBtn[NUM];//各部件对应按钮容器
    int msg_y = 0;  //鼠标中键滑动轴对应y坐标
    int Costumes_amount = NUM;  //装扮数量
    int bodyid,earsid; //身体和耳朵对应装扮序号
};


#endif //QT_DRESSWIN_H
