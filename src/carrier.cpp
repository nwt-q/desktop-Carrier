//
// Created by NWT on 2024/11/16.
//

#include "../include/carrier.h"
#include "../ui/ui_carrier.h"

#define Dat "D:/CLion_Job/Carrier/resources/file/file.dat"  //基本数据存放区域
#define Fly ":/images/movement/fly/%1.png"
#define Error ":/images/movement/error/%1.png"
#define Blink ":/images/movement/blink/%1.png"
#define Heart ":/images/movement/heart/%1.png"
#define Question ":/images/movement/question/%1.png"
#define CloseEyes ":/images/movement/closeEyes/%1.png"
#define Wink ":/images/movement/wink/%1.png"

Carrier::Carrier(QWidget *parent) : QMainWindow(parent)
, ui(new Ui::Carrier) {

    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);//去掉窗口标题
    setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    Qt::WindowFlags m_flags = windowFlags();//保持窗口置顶1
    setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);//保持窗口置顶2
    InitPos();

    timer = new QTimer;
    timer->start(40);//动画速度
    connect(timer,&QTimer::timeout,this,&Carrier::eyesMovement);//关联眼部动作

    imageLoad();//载入部位图片
    eyesMovementLoad();//载入表情图片
    specialMovementLoad();//载入特殊动作图片

    bodyImage = new QLabel(this);//身体图片指针
    eyesImage = new QLabel(this);//眼部图片指针
    stripeImage = new QLabel(this);//屏幕遮盖条纹图片指针
    earsImage = new QLabel(this);//耳朵图片指针


    imageSet(bodyImage,body[bodyid]);

    imageSet(eyesImage,eyes);

    if(size > 140){
        imageSet(stripeImage,stripe);
        stripeImage->show();
    } else stripeImage->hide();

    imageSet(earsImage,ears1[earsid]);

    initBtn();//初始化按钮
    update();
    initSystemTray();//初始化系统托盘
}

Carrier::~Carrier() {
    delete ui;
    //清理各类指针申请的空间

    delete earsImage;
    delete bodyImage;
    delete eyesImage;
    delete stripeImage;

    delete closeBtn;
    delete dressBtn;
    delete moreBtn;
    delete minBtn;
    delete setBtn;
    delete musicBtn;
    delete gameBtn;
    delete calenBtn;

    delete dressWindow;
    delete setWindow;
    delete calenWindow;
}

//对坐标进行初始化
void Carrier::InitPos() {
    int coordX,coordY;//桌面坐标
    QFile file(Dat);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    if(file.isOpen()) // 读取体型、 装扮编号参数、相对桌面坐标  => 保留用户设置操作  => 数据持久化
        in >> size >> bodyid >> earsid >> coordX >> coordY;
    else{  // 如果数据为空 => 全部数据初始化
        size = 400;
        bodyid = 0;
        earsid = 0;
        coordX = x();
        coordY = y();
    }
    file.close();
    move(coordX,coordY);
}

void Carrier::eyesMovementLoad() {
    faceNum.push_back(9);//帧数-例：9代表9帧
    faceNum.push_back(0);//起始位置-例：0代表该表情第一张图片下标
    for(int i = 1; i<=faceNum[0]; i++)//表情1-眨眼
        movement.push_back(QPixmap(QString(Blink).arg(i)));
    faceNum.push_back(12);
    faceNum.push_back(9);
    for(int i = 1; i<=faceNum[2]; i++)//表情2-心动
        movement.push_back(QPixmap(QString(Heart).arg(i)));
    faceNum.push_back(16);
    faceNum.push_back(21);
    for(int i = 1; i<=faceNum[4]; i++)//表情3-疑惑
        movement.push_back(QPixmap(QString(Question).arg(i)));
    faceNum.push_back(15);
    faceNum.push_back(37);
    for(int i = 1; i<=faceNum[6]; i++)//表情4-闭眼
        movement.push_back(QPixmap(QString(CloseEyes).arg(i)));
    faceNum.push_back(9);
    faceNum.push_back(52);
    for(int i = 1; i<=faceNum[8]; i++)//表情5-单眨眼
        movement.push_back(QPixmap(QString(Wink).arg(i)));

    face = -1;//表情序号初始化为-1，不生效
    faceSum = 5;//表情数量
}


void Carrier::eyesMovement() {
    //各种静态变量，用于计数、记录状态等↓
    static int flag = 0,second1 = 0,second2 = 0,earSwitch = 1;
    //控制随机眨眼
    int valve = rand() % 200;

    //控制眨眼动作
    if(face < 0 && spMove < 0){  //控制眨眼动作
        second1++;
        if(second1 >= valve && valve > 100){ // 控制随机眨眼是速度
            face = 0;
            second1 = 0;
        }
    }

    second2++; //控制耳朵的动画
    if(second2 > 40 && earSwitch){
        earsImage->setPixmap(ears2[earsid].scaled(size,size));
        earSwitch = 0;
        second2 = 0;
    }
    else if(second2 > 10 && !earSwitch){
        earsImage->setPixmap(ears1[earsid].scaled(size,size));
        earSwitch = 1;
        second2 = 0;
    }

    //控制表情变化
    if(face != -1){
        int num = faceNum[face * 2],start = faceNum[face * 2 + 1];
        flag++;
        if(flag < num)
            eyesImage->setPixmap(movement[start + flag].scaled(size,size));
        else
            eyesImage->setPixmap(movement[start - flag + (num - 1) * 2 ].scaled(size,size));

        if(flag >= (num - 1) * 2){
            flag = 0;
            face = -1;
            eyesImage->setPixmap(eyes.scaled(size,size));
        }
    }
    //从换装窗口中获取bodyid、earsid 参数
    if(!dressWindow->isHidden()){
        if(bodyid!=dressWindow->getBodyid()){
            bodyid = dressWindow->getBodyid();
            bodyImage->setPixmap(body[bodyid].scaled(size,size));
            saveData();
        }
        if(earsid != dressWindow->getEarsid()){
            earsid = dressWindow->getEarsid();
            earsImage->setPixmap(ears1[earsid].scaled(size,size));
            saveData();
        }
    }
    if(!setWindow->isHidden()){//从设置窗口中获取size参数
        if(size!=setWindow->getSize()){
            size = setWindow->getSize();

            imageSet(bodyImage,body[bodyid]);
            imageSet(eyesImage,eyes);
            if(size > 140){
                imageSet(stripeImage,stripe);
                stripeImage->show();
            }
            else
                stripeImage->hide();
            imageSet(earsImage,ears1[earsid]);

            saveData();
            reInitBtn();
        }
    }
    if(spMove>-1)//特殊动作
        specialMovement();
}

void Carrier::specialMovementLoad() { //用于加载特殊图片
    for(int i = 1;i <= 11;i++)
        spMovement.push_back(QPixmap(QString(Error).arg(i)));
    for(int i = 1;i <= 22;i++)
        spMovement.push_back(QPixmap(QString(Fly).arg(i)));

    spMove = -1;
}

void Carrier::specialMovement() {
    static int flag = 0;

    //动作-error
    if(spMove == 0){
        if(flag % 20 == 0 && flag <= 200)
            eyesImage->setPixmap(spMovement[flag/20].scaled(size,size));
        else if(flag>300){
            eyesImage->setPixmap(eyes.scaled(size,size));
            flag=0;
            spMove=-1;
            return ;
        }
    }
    flag++;
}

void Carrier::saveData() {
    QFile file(Dat);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << size << bodyid << earsid << x() << y();//存储体型、装扮编号参数、窗口坐标
    file.close();
}

void Carrier::mousePressEvent(QMouseEvent *event) {
    static int flag = 0;
    //获取鼠标点击事件=> 判断鼠标点击事件类型对点击事件进行判断
    /// 左键随机标签
    if(event->button() == Qt::LeftButton ) { //鼠标右键被按下
        moveLeftTop = event->pos();
        if(face < 0 && spMove < 0){//随机播放表情
            face = rand() % ( faceSum - 1 ) + 1;
            flag++;
            if(flag == 10){//触发蓝屏
                flag = 0;
                spMove = 0;
                face = -1;
            }
        }
    }
    // 右键隐藏菜单
    ///鼠标右键被按下
    if(event->button() == Qt::RightButton ) {
        ///转换模式 => 隐藏状态
        if(btnSwitch_1){ //隐藏按钮
            btnSwitch_1=0;
            btnSwitch_2=0;
        } else btnSwitch_1=1; //显示按钮
        //讲菜单隐藏
        dressWindow->hide();
        //设置隐藏
        setWindow->hide();
        //日历隐藏
        calenWindow->hide();
        //选择模式
        btnSwitchRole();
    }
}

void Carrier::btnSwitchRole() {
    //根据btnSwitch调整按钮是否显示
    closeBtn->setVisible(btnSwitch_1);
    dressBtn->setVisible(btnSwitch_1);
    moreBtn->setVisible(btnSwitch_1);
    minBtn->setVisible(btnSwitch_1);
    setBtn->setVisible(btnSwitch_2);
    musicBtn->setVisible(btnSwitch_2);
    gameBtn->setVisible(btnSwitch_2);
    calenBtn->setVisible(btnSwitch_2);

     //移动窗口坐标↓
    setWindow->move(x()+frameGeometry().width()/2
     -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-setWindow->frameGeometry().width(),
     y()+frameGeometry().height()/2-size/5
     -setWindow->frameGeometry().height()/2);

    //移动窗口坐标↓
    // musicWindow->move(x()+frameGeometry().width()/2
    // -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-musicWindow->frameGeometry().width(),
    // y()+frameGeometry().height()/2-size/5
    // -musicWindow->frameGeometry().height()/2);
    //移动窗口坐标↓
    calenWindow->move(x() + frameGeometry().width() / 2
                      - btnSize*(btnSwitch_1 + btnSwitch_2 + 1.5) / 4 - calenWindow->frameGeometry().width(),
                      y() + frameGeometry().height() / 2 - size / 5
                      - calenWindow->frameGeometry().height() / 2);
}


void Carrier::imageLoad() {
    //载入装扮图片
    body.push_back(QPixmap(QString(":/images/appearance/body/def_body.png")));
    body.push_back(QPixmap(QString(":/images/appearance/body/blue_body.png")));
    body.push_back(QPixmap(QString(":/images/appearance/body/pink_body.png")));
    body.push_back(QPixmap(QString(":/images/appearance/body/icefire_body.png")));
    body.push_back(QPixmap(QString(":/images/appearance/body/cat_body.png")));
    body.push_back(QPixmap(QString(":/images/appearance/body/Gundam_body.png")));
    body.push_back(QPixmap(QString(":/images/appearance/body/drill_body.png")));
    body.push_back(QPixmap(QString(":/images/appearance/body/angel_body.png")));

    ears1.push_back(QPixmap(QString(":/images/appearance/ears/def_ears1.png")));
    ears1.push_back(QPixmap(QString(":/images/appearance/ears/blue_ears1.png")));
    ears1.push_back(QPixmap(QString(":/images/appearance/ears/pink_ears1.png")));
    ears1.push_back(QPixmap(QString(":/images/appearance/ears/icefire_ears1.png")));
    ears1.push_back(QPixmap(QString(":/images/appearance/ears/cat_ears1.png")));
    ears1.push_back(QPixmap(QString(":/images/appearance/ears/Gundam_ears1.png")));
    ears1.push_back(QPixmap(QString(":/images/appearance/ears/drill_ears1.png")));
    ears1.push_back(QPixmap(QString(":/images/appearance/ears/angel_ears1.png")));

    ears2.push_back(QPixmap(QString(":/images/appearance/ears/def_ears2.png")));
    ears2.push_back(QPixmap(QString(":/images/appearance/ears/blue_ears2.png")));
    ears2.push_back(QPixmap(QString(":/images/appearance/ears/pink_ears2.png")));
    ears2.push_back(QPixmap(QString(":/images/appearance/ears/icefire_ears2.png")));
    ears2.push_back(QPixmap(QString(":/images/appearance/ears/cat_ears2.png")));
    ears2.push_back(QPixmap(QString(":/images/appearance/ears/Gundam_ears2.png")));
    ears2.push_back(QPixmap(QString(":/images/appearance/ears/drill_ears2.png")));
    ears2.push_back(QPixmap(QString(":/images/appearance/ears/angel_ears2.png")));
    eyes.load(":/images/appearance/eyes/def_eyes.png");
    stripe.load(":/images/appearance/stripe.png");
}

void Carrier::imageSet(QLabel *image, QPixmap map) {
    //根据size设定各图片大小和坐标
    image->setPixmap(map.scaled(size,size));//使用scaled修改图片大小，能避免图片因缩放模糊
    image->setScaledContents(true);
    image->resize(size,size);
    image->move(this->frameGeometry().width() / 2 - size / 2,
                this->frameGeometry().height() / 2 - size / 2);
    update();
}

void Carrier::initBtn() {
    closeBtn = new QPushButton(this);//关闭按钮
    dressBtn = new QPushButton(this);//换装按钮
    moreBtn = new QPushButton(this);//展开更多按钮
    minBtn = new QPushButton(this);//最小化按钮
    setBtn = new QPushButton(this);//设置按钮
    musicBtn = new QPushButton(this);//音乐按钮
    gameBtn = new QPushButton(this);//游戏按钮
    calenBtn = new QPushButton(this);//日历按钮

    closeBtn->setIcon(QIcon(":/images/icon/close.png"));
    dressBtn->setIcon(QIcon(":/images/icon/dress.png"));
    moreBtn->setIcon(QIcon(":/images/icon/more.png"));
    minBtn->setIcon(QIcon(":/images/icon/min.png"));
    setBtn->setIcon(QIcon(":/images/icon/setting.png"));
    musicBtn->setIcon(QIcon(":/images/icon/music.png"));
    gameBtn->setIcon(QIcon(":/images/icon/game.png"));
    calenBtn->setIcon(QIcon(":/images/icon/calendar.png"));

    reInitBtn();

    //设置按钮样式
    setStyleSheet("QPushButton{border:4px solid black;"
                  "background-color:rgb(200,210,255);border-radius: 10px;}"
                  "QPushButton::hover{background-color:rgb(170,200,255);}"
                  "QPushButton:pressed{background-color:rgb(60,70,200);}");

    dressWindow = new DressWin;//换装窗口
    dressWindow->accept(body,ears1,bodyid,earsid);

    setWindow =  new SetWin;//设置窗口
    setWindow->setSize(size);//为设置窗口传入size参数

    //musicWindow = new MusicWin;//音乐窗口

    calenWindow = new QCalendarWidget;//日历窗口
    calenWindow->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口标题栏
    calenWindow->setWindowIcon(QIcon(":/images/icon/calendar.png")); //设置窗口图标
    calenWindow->resize(600,400);


    //连接按钮信号与对应槽函数
    ///适当使用Lambda 表达式 减轻代码量
    /// 光闭窗口按钮
    connect(closeBtn,&QPushButton::clicked,this,[&](){
        dressWindow->close();
        setWindow->close();
        calenWindow->close();
        this->close();
    });
    /// 换装按钮
    connect(dressBtn,&QPushButton::clicked,this,[&](){
        if(dressWindow->isHidden()){
            ///设置相对位置移动
            dressWindow->move(x()+ frameGeometry().width() / 2 - 10
                              -btnSize * 0.6 - dressWindow->frameGeometry().width(),
                              y() + frameGeometry().height() / 2 - 150
                              -dressWindow->frameGeometry().height() / 2);
            dressWindow->show();
            calenWindow->hide();
            setWindow->hide();
            //musicWindow->hide();
            btnSwitch_2=0;  //更新菜单按钮状态
            btnSwitchRole();
        }
        else
            dressWindow->hide();
    });
    /// 更多按钮
    connect(moreBtn,&QPushButton::clicked,this,[&](){

        if(btnSwitch_2 == 0) btnSwitch_2=1;
        else btnSwitch_2=0;
        btnSwitchRole();
        //隐藏设置按钮
        setWindow->hide();
        //隐藏日历按钮
        calenWindow->hide();
        //换装按钮
        dressWindow->hide();
    });
    ///将窗口最小化
    connect(minBtn,&QPushButton::clicked,this,[&](){
        //this->setWindowState(Qt::WindowMinimized);//最小化窗口（已弃用）
        this->hide();
        dressWindow->hide();
        calenWindow->hide();
        setWindow->hide();
        //musicWindow->hide();

        btnSwitch_1=0;
        btnSwitch_2=0;
        btnSwitchRole();
    });

    ///设置按钮
    connect(setBtn,&QPushButton::clicked,this,[&](){
        if(setWindow->isHidden()){
            //移动窗口坐标↓
            setWindow->move(x() + frameGeometry().width() / 2
                            -btnSize*(btnSwitch_1+btnSwitch_2 + 1.5)/4-setWindow->frameGeometry().width(),
                            y()+frameGeometry().height()/2-size/5
                            -setWindow->frameGeometry().height()/2);

            setWindow->show();
            calenWindow->hide();
            //musicWindow->hide();
        } else setWindow->hide();
    });
    ///音乐按钮部分待做
    //connect(musicBtn,&QPushButton::clicked,this,&Carrier::musicBtnPush);

    connect(gameBtn,&QPushButton::clicked,this,&Carrier::gameBtnPush);

    connect(calenBtn,&QPushButton::clicked,this,[&](){
        if(calenWindow->isHidden()){
            //移动窗口坐标↓
            calenWindow->move(x() + frameGeometry().width()/2
                              -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-calenWindow->frameGeometry().width(),
                              y()+frameGeometry().height()/2-size/5
                              -calenWindow->frameGeometry().height()/2);

            calenWindow->show();
            //musicWindow->hide();
            setWindow->hide();
        }
        else calenWindow->hide();
    });

    btnSwitch_1 = 0;//初始化按钮显示
    btnSwitch_2 = 0;
    btnSwitchRole();
}

void Carrier::reInitBtn() {

    btnSize = size;

    if(btnSize < 300)//限制按钮大小
        btnSize = 300;
    //按钮的坐标和大小参数
    int btnX = this->frameGeometry().width() / 2 - btnSize * 3 / 5 - 5;
    int btnY = this->frameGeometry().height() / 2 - btnSize / 4;
    int btnWidth = btnSize / 5;
    int btnHeight = btnSize / 8;

    closeBtn->setGeometry(btnX,btnY,btnWidth,btnHeight);
    dressBtn->setGeometry(btnX,btnY + btnSize / 6,btnWidth,btnHeight);
    moreBtn->setGeometry(btnX,btnY + 2 * btnSize / 6,btnWidth,btnHeight);
    minBtn->setGeometry(btnX,btnY + 3 * btnSize / 6,btnWidth,btnHeight);

    setBtn->setGeometry(btnX - btnWidth * 1.2,btnY,btnWidth,btnHeight);
    musicBtn->setGeometry(btnX - btnWidth * 1.2,btnY + btnSize / 6,btnWidth,btnHeight);
    gameBtn->setGeometry(btnX - btnWidth * 1.2,btnY + 2 * btnSize / 6,btnWidth,btnHeight);
    calenBtn->setGeometry(btnX - btnWidth * 1.2,btnY + 3 * btnSize / 6,btnWidth,btnHeight);
    //图标大小
    QSize temp(btnSize / 8,btnSize / 8);
    closeBtn->setIconSize(temp);
    dressBtn->setIconSize(temp);
    moreBtn->setIconSize(temp);
    minBtn->setIconSize(temp);
    setBtn->setIconSize(temp);
    musicBtn->setIconSize(temp);
    gameBtn->setIconSize(temp);
    calenBtn->setIconSize(temp);
}

void Carrier::gameBtnPush() {
    //隐藏所有窗口
    this->hide();
    setWindow->hide();
    calenWindow->hide();

    //musicWindow->hide();
    QDir dir( "C:/Users/NWT/Desktop/cxk.exe");//获取相对路径
     QString temDir = dir.absolutePath();//通过相对路径获取绝对路径
     system(temDir.toLatin1());

    //↑通过cmd启动游戏，toLatin1()将QString类型转为char*类型
    //阻塞式启动，关闭后游戏窗口后才运行下面语段↓
    //隐藏按钮↓
    btnSwitch_1=0;
    btnSwitch_2=0;
    btnSwitchRole();

    this->show();
}

void Carrier::initSystemTray() {
    pSystemTray = new QSystemTrayIcon(this);
    pSystemTray->setIcon(QIcon(":/images/icon/close.png"));
    pSystemTray->setToolTip("Hello, I'm Carrier.");
    pSystemTray->show();
    /// 绑定点击系统托盘事件 => 触发效果隐藏
    connect(pSystemTray,&QSystemTrayIcon::activated,this,[&](){
        if(this->isHidden()) this->show();
    });

}

/// 移动的时候各按键应该跟随移动
void Carrier::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton)//鼠标左键按下并移动时，实现拖动窗口
    {
        this->move(event->globalPosition().toPoint()-moveLeftTop);
        //伴随移动 服装界面
        dressWindow->move(x()+frameGeometry().width()/2-10
                          -btnSize*0.6-dressWindow->frameGeometry().width(),
                          y()+frameGeometry().height()/2-150
                          -dressWindow->frameGeometry().height()/2);
        //伴随移动 设置界面 => 设置大小
        setWindow->move(x() + frameGeometry().width() / 2
                        -btnSize*(btnSwitch_1+btnSwitch_2 + 1.5)/4-setWindow->frameGeometry().width(),
                        y()+frameGeometry().height()/2-size/5
                        -setWindow->frameGeometry().height()/2);

        // musicWindow->move(x()+frameGeometry().width()/2
        // -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-musicWindow->frameGeometry().width(),
        // y()+frameGeometry().height()/2-size/5
        // -musicWindow->frameGeometry().height()/2);
        //日历界面
        calenWindow->move(x()+frameGeometry().width()/2
                          -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-calenWindow->frameGeometry().width(),
                          y()+frameGeometry().height()/2-size/5
                          -calenWindow->frameGeometry().height()/2);


        saveData();
    }
}
