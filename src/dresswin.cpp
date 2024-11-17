//
// Created by NWT on 2024/11/16.
//
#include "../include/dresswin.h"
#include "../ui/ui_dresswin.h"
#define site(x) (msg_y + x * 230 + 210)
#define sitem(x) (msg_y + x * 240 + 210)
#define sitep(x) (msg_y + x * 240)
#define MaxHight (-230*Costumes_amount+460)
#define Dummy ":/images/appearance/body/dummy.png"
#define Choose ":/images/icon/choose.png"

DressWin::DressWin(QWidget *parent)  : QWidget(parent),ui(new Ui::DressWin){
    ui->setupUi(this);

    QBitmap bmp(this->size());//设置圆角边框

    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),50,50);
    setMask(bmp);
    setWindowOpacity(0.95);//设置透明度
    setStyleSheet("background-color:white;");

    Qt::WindowFlags m_flags = windowFlags();//保持窗口置顶1
    setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);//保持窗口置顶2

    //更换皮肤
    this->setWindowIcon(QIcon(":/images/icon/dress.png")); //设置窗口图标
    initBtn();
}

void DressWin::initBtn() {
    //类似于QML的设计方式更改样式
    setStyleSheet("QPushButton{border:none;"
                  "background-color:rgb(200,200,200)"
                  ";border-radius: 15px;"
                  "border-style:outset;}"
                  "QPushButton::hover{background-color:rgb(170,200,255);}"
                  "QPushButton:checked{background-color:rgb(100,120,230);}");

    bodyBox =  new QButtonGroup;
    earsBox =  new QButtonGroup;

    //将俩选项设置为互斥选项,这样其中的只能存在一个被按下的状态
    bodyBox->setExclusive(true);
    earsBox->setExclusive(true);

    for(int i = 0; i < Costumes_amount; ++i){

        bodyBtn[i] = new QPushButton(this);
        bodyBtn[i]->setFixedSize(80,40);
        bodyBtn[i]->move(80,site(i));
        bodyBtn[i]->setIcon(QIcon(Choose));  //=> 放置图标
        bodyBtn[i]->setCheckable(1);  // 设置按键为可选状态
        bodyBox->addButton(bodyBtn[i],i); //将按键添加到 bodyBox中

        earsBtn[i] = new QPushButton(this);
        earsBtn[i]->setFixedSize(80,40);
        earsBtn[i]->move(280,site(i));
        earsBtn[i]->setIcon(QIcon(Choose));
        earsBtn[i]->setCheckable(1);
        earsBox->addButton(earsBtn[i],i);
    }
//    connect(bodyBox,
//            static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
//            this,[&](int id){
//                bodyid = id;
//            });
//    connect(earsBox,
//            static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
//            this,[&](int id){
//                earsid = id;
//            });
}

int DressWin::getBodyid() const {
    return bodyid;
}

int DressWin::getEarsid() const {
    return earsid;
}

void DressWin::wheelEvent(QWheelEvent *event) {
    QWidget::wheelEvent(event);
    static int speed = 40;//滚动速度
    auto angleDelta = static_cast<QWheelEvent*>(event)->angleDelta();  //这里要引入头文件

    if(angleDelta.y() > 0){
        if(msg_y < 0) msg_y += speed;
    }
    else{
        if(msg_y > MaxHight)
            msg_y -= speed;
    }
    for(int i = 0;i < Costumes_amount; i++){
        bodyBtn[i]->move(80,sitem(i));
        earsBtn[i]->move(280,sitem(i));
    }
    update();//调用绘画事件函数-paintEvent来更新画面
}

void DressWin::paintEvent(QPaintEvent *) {
    static QPixmap dummy(Dummy);
    QPainter painter(this);
    for(int i = 0; i < Costumes_amount; i++)
        painter.drawPixmap(0,sitep(i),240,240,body[i]);
    for(int i = 0;i < Costumes_amount;i++){
        painter.drawPixmap(200,sitep(i),240,240,dummy);
        painter.drawPixmap(200,sitep(i),240,240,ears[i]);
    }
}

void DressWin::accept(std::vector<QPixmap> &body, std::vector<QPixmap> &ears, int bodyid, int earsid) {
    this->body = body;
    this->ears = ears;
    this->bodyid = bodyid;
    this->earsid = earsid;
    bodyBtn[bodyid]->setChecked(1);
    earsBtn[earsid]->setChecked(1);
}

DressWin::~DressWin()
{
    delete ui;
}