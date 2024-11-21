//
// Created by NWT on 2024/11/17.
//

#include "../include/setwin.h"
#include "../ui/ui_setwin.h"

SetWin::SetWin(QWidget *parent) :
        QWidget(parent),ui(new Ui::SetWin){
    ui->setupUi(this);

    // 设置开机自启动 与 Carrier大小
    QBitmap bmp(this->size());//设置圆角边框
    bmp.fill();
    QPainter painter(&bmp);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawRoundedRect(bmp.rect(),50,50);
    setMask(bmp);
    setWindowOpacity(0.95);//设置透明度
    setStyleSheet("background-color:white;");

    Qt::WindowFlags m_flags = windowFlags();//保持窗口置顶1
    setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);//保持窗口置顶2

    this->setWindowIcon(QIcon(":/images/icon/setting.png")); //设置窗口图标
    painter.end();
}

SetWin::~SetWin() {
    delete ui;
}

void SetWin::setSize(int size) {
    CarrierSize = size;

    QFont ft;
    ft.setPointSize(12);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::blue);
    sizeNum = new QLabel(this);
    sizeNum->move(120,100);
    sizeNum->resize(120,20);
    sizeNum->setFont(ft);
    sizeNum->setPalette(pa);
    sizeNum->setNum(CarrierSize);
    sizeNum->show();

    ui->sizeSlider->setValue(CarrierSize);
}

int SetWin::getSize() {
    return CarrierSize;
}

void SetWin::on_sizeSlider_valueChanged(int value) {
    //对滑块值进行实时更新
    CarrierSize = value;
    sizeNum->setNum(CarrierSize);
}
