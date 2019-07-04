#ifndef NODE_H
#define NODE_H
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>
#include <QEvent>
class Node: public QWidget{
    Q_OBJECT
public:
    explicit Node(int x,int y,QWidget *parent = nullptr);

    bool isTriggered();
    void setTriggered(bool);


signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);//绘图事件
    void enterEvent(QEvent *event);//鼠标移入
    void leaveEvent(QEvent *event);//鼠标移出

private:
    int x;
    int y;
    QBrush nodeBrush[3];//brush[0]为初始管道颜色，brush[2]为高亮颜色
    bool triggered = false;
};

#endif // NODE_H
