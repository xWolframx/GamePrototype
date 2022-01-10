#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QTime>
#include <windows.h>
#include <QVector>
#include <ctime>
#include <cstdlib>

namespace Ui {
class Widget;
}

class rectObject
{
public:
    rectObject(int x, int y, int width, int height, int cX, int cY, int sp, QColor pen, QColor brush);
    ~rectObject();
    void paint(QGraphicsScene *scene);
    void setX(int x);
    void setY(int y);
    void setSpeed(int s);
    void setCenterX(int cX);
    void setCenterY(int cY);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    int getCenterX();
    int getCenterY();
    int getSpeed();

protected:
    int topX;
    int topY;
    int downX;
    int downY;
    int width, height;
    int centerX;
    int centerY;
    int speed;
    QColor brushC;
    QColor penC;
    QGraphicsRectItem *rect;

};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void updateGame();
    void moveUp(int speed);
    void moveDown(int speed);
    void moveLeft(int speed);
    void moveRight(int speed);
    //QVector<rectObject> *stone;

protected:
    const int ticks_per_second = 25;
    const int skip_ticks = 1000 / ticks_per_second;
    const int max_frameskip = 5;
    DWORD next_game_tick = GetTickCount();
    int loops;
    float interpolation;

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QTimer *updateTimeGlobalTimer;
    QTimer *updateDisplayTimeTimer;

    rectObject *player;
    QVector<rectObject*> stone;

private slots:
    void updateTimeGlobal();
    void updateDisplay();
};

#endif // WIDGET_H
