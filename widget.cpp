#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QGraphicsPolygonItem>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(1280, 720);

    updateTimeGlobalTimer = new QTimer();
    updateTimeGlobalTimer->setInterval(40);
    connect(updateTimeGlobalTimer, SIGNAL(timeout()), this, SLOT(updateTimeGlobal()));
    updateTimeGlobalTimer->start();

    updateDisplayTimeTimer = new QTimer();
    updateDisplayTimeTimer->setInterval(20);
    connect(updateDisplayTimeTimer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
    updateDisplayTimeTimer->start();

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(-640, -360, 1280, 720);


    player = new rectObject(-12, -12, 25, 25, 0, 0, 3, Qt::black, Qt::red);

    srand(time(0));
    for(int i = 0; i < 5; ++i)
    {
        rectObject *stoneObj;
        int x, y;
        x = rand() % 1280 - 640;
        y = rand() % 720 - 360;
        stoneObj = new rectObject(x, y, 25, 25, 3, 3, 5, Qt::black, Qt::green);
        stone.append(stoneObj);
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateDisplay()
{
    scene->clear();
    for(int i = 0; i < stone.size(); ++i)
    {
        stone[i]->paint(scene);
    }
    player->paint(scene);
    /*QPolygon polygon;
    polygon << QPoint(0, 0) << QPoint(0, 5) << QPoint(5, 5) << QPoint(5, 0);
    QGraphicsPolygonItem *pol;
    pol = scene->addPolygon(polygon, QPen(Qt::green), QBrush(Qt::green));*/
}

void Widget::updateTimeGlobal()
{
    /*updateGame();
    updateDisplay();*/
    loops = 0;
    while(GetTickCount() > next_game_tick && loops < max_frameskip)
    {
        updateGame();
        next_game_tick += skip_ticks;
        loops++;
    }
    interpolation = float(GetTickCount() + skip_ticks - next_game_tick) / float(skip_ticks);
    if(interpolation < 0)
    {
        updateDisplayTimeTimer->setInterval(1);
    }
    else
    {
        updateDisplayTimeTimer->setInterval(interpolation);
    }
    //updateDisplayTime->setInterval(interpolation);

    float intfps;
    intfps = 1000 / interpolation;
    QString fps;
    fps.setNum(intfps);
    ui->label_2->setText(fps);

    /*QString x, y;
    x.setNum(player->getX());
    y.setNum(player->getY());
    x = x + ' ' + y;
    ui->label_3->setText(x);*/
}

void Widget::moveUp(int speed)
{
    for(int i = 0; i < stone.size(); ++i)
    {
        stone[i]->setY(stone[i]->getY() + speed);
    }
}

void Widget::moveDown(int speed)
{
    for(int i = 0; i < stone.size(); ++i)
    {
        stone[i]->setY(stone[i]->getY() - speed);
    }
}

void Widget::moveLeft(int speed)
{
    for(int i = 0; i < stone.size(); ++i)
    {
        stone[i]->setX(stone[i]->getX() + speed);
    }
}

void Widget::moveRight(int speed)
{
    for(int i = 0; i < stone.size(); ++i)
    {
        stone[i]->setX(stone[i]->getX() - speed);
    }
}

void Widget::updateGame()
{
    if(GetAsyncKeyState('W'))
    {
        //player->setY(player->getY() - player->getSpeed());
        moveUp(player->getSpeed());
    }
    if(GetAsyncKeyState('S'))
    {
        moveDown(player->getSpeed());
    }
    if(GetAsyncKeyState('A'))
    {
        moveLeft(player->getSpeed());
    }
    if(GetAsyncKeyState('D'))
    {
        moveRight(player->getSpeed());
    }
}

rectObject::rectObject(int x, int y, int width, int height, int cX, int cY, int sp, QColor pen, QColor brush)
{
    this->topX = x;
    this->topY = y;
    this->width = width;
    this->height = height;
    this->downX = x + width;
    this->downY = y - height;
    this->centerX = cX;
    this->centerY = cY;
    this->speed = sp;
    this->penC = pen;
    this->brushC = brush;
}

rectObject::getHeight()
{
    return this->height;
}

rectObject::getWidth()
{
    return this->width;
}

rectObject::getX()
{
    return this->topX;
}

rectObject::getY()
{
    return this->topY;
}

rectObject::getCenterX()
{
    return this->centerX;
}

rectObject::getCenterY()
{
    return this->centerY;
}

void rectObject::setX(int x)
{
    this->topX = x;
    this->downX = x + this->width;
}

void rectObject::setY(int y)
{
    this->topY = y;
    this->downY = y - this->height;
}

void rectObject::setSpeed(int s)
{
    this->speed = s;
}

void rectObject::setCenterX(int cX)
{
    this->centerX = cX;
}

void rectObject::setCenterY(int cY)
{
    this->centerY = cY;
}

rectObject::getSpeed()
{
    return this->speed;
}

void rectObject::paint(QGraphicsScene *scene)
{
    QBrush brush(this->brushC);
    QPen pen(this->penC);
    rect = scene->addRect(this->topX, this->topY, this->width, this->height, pen, brush);
}
