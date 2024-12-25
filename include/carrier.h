//
// Created by NWT on 2024/11/16.
//

#ifndef QT_CARRIER_H
#define QT_CARRIER_H

#include"dresswin.h"
#include "setwin.h"
#include <QFunctionPointer>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QFile>
#include<QTimer>
#include <QLabel>
#include <QCalendarWidget>
#include <QDir>
#include <QResource>
#include <random>


QT_BEGIN_NAMESPACE
namespace Ui { class Carrier; }
QT_END_NAMESPACE

class Carrier : public QMainWindow{
    Q_OBJECT
public:
    explicit Carrier(QWidget *parent = nullptr);
    ~Carrier() override;
    void InitPos();//初始化坐标
    void initBtn();//初始化按钮
    void reInitBtn();//修改大小时再次初始化按钮
    void initSystemTray();//初始化系统托盘
    void imageLoad();//各部位图片载入, 事件绑定
    inline void imageSet(QLabel *image,const QPixmap& map);//设置各部位图片
    void eyesMovementLoad();//眼部动作载入
    void eyesMovement(); //眼部动作事件
    void specialMovementLoad();//特殊动作载入
    void specialMovement();//特殊动作事件
    void saveData();//存储数据
    void mousePressEvent(QMouseEvent *event) override;//鼠标点击事件-虚函数
    void mouseMoveEvent(QMouseEvent *event) override;//鼠标移动事件-虚函数
    void btnSwitchRole();//根据btnSwitch切换按钮状态
    void gameBtnPush(); //游戏选择
    void checkAndAdjustWindowGeometry(); // 屏幕检查
    static inline std::mt19937& generator();
    template<typename T, std::enable_if_t<std::is_integral_v<T>>* = nullptr>
    T my_rand(T min, T max);
private:
    //对成员进行列表初始化
    Ui::Carrier *ui;
    DressWin *dressWindow{};//换装窗口指针
    SetWin *setWindow{};//设置大小窗口指针

    int size{}; //设置体型大小
    int bodyid{},earsid{}; //身体和耳朵对应装扮序号
    int face{}; //表情序号
    int faceSum{}; //表情数量
    int spMove{};//特殊动作序号
    int btnSize{};//按钮大小
    int btnSwitch_1{},btnSwitch_2{}; //菜单按钮显示开关
    QPoint moveLeftTop;//坐标点
    QTimer *timer;  //定时器

    QLabel *bodyImage,*earsImage,*eyesImage,*stripeImage;//各部件对应标签
    std::vector<QPixmap> body,ears1,ears2;//各部件对应图片容器
    std::vector<QPixmap> movement;//表情图片容器
    std::vector<QPixmap> spMovement;//特殊动作图片容器
    QPixmap eyes,stripe;//眼睛和眼部遮罩
    std::vector<int> faceNum;//每个表情对应帧数与起始位置

    QPushButton *closeBtn{};//关闭按钮
    QPushButton *dressBtn{};//换装按钮
    QPushButton *moreBtn{};//展开更多按钮
    QPushButton *minBtn{};//最小化按钮
    QPushButton *setBtn{};//设置按钮
    QPushButton *musicBtn{};//音乐按钮
    QPushButton *gameBtn{};//游戏按钮
    QPushButton *calenBtn{};//日历按钮

    QSystemTrayIcon* pSystemTray{};//系统托盘

    QCalendarWidget *calenWindow{};//日历窗口指针

};


#endif //QT_CARRIER_H
