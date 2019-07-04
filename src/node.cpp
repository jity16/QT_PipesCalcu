#include "node.h"
#include <QMouseEvent>
#include <QApplication>
#include <QEvent>
bool Node::isTriggered(){
    return this->triggered;
}
void Node::setTriggered(bool b){
    this->triggered = b;
}

Node::Node(int x,int y, QWidget *parent):QWidget(parent)
{
    QCursor cursor;
    cursor.setShape(Qt::OpenHandCursor);
    setCursor(cursor);
    this->x = x;
    this->y = y;
}
void Node::paintEvent(QPaintEvent *event){//绘图事件（适应widget大小）
    QPainter painter;
    painter.begin(this);
    nodeBrush[0]= QBrush(QColor(255,222,173),Qt::SolidPattern);//初始颜色
    nodeBrush[2]= QBrush(QColor(216,191,216),Qt::SolidPattern);//高亮颜色
        painter.setBrush(nodeBrush[0]);
    if(isTriggered())
        painter.setBrush(nodeBrush[2]);
    painter.drawEllipse(QPoint(8,8),8,8);
    painter.end();
}
void Node::enterEvent(QEvent *event){//鼠标移入
    QCursor cursor;
    cursor.setShape(Qt::PointingHandCursor);
    QApplication::setOverrideCursor(cursor);
    this->setTriggered(true);
    this->repaint();
}
void Node::leaveEvent(QEvent *event){//鼠标移出
    this->setTriggered(false);
    this->repaint();
}

