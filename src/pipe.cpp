#include "pipe.h"
#include <QMouseEvent>
#include <QWidget>
#include <QCursor>
#include <QApplication>
#include <QPainter>
#include <QRect>
#include <QDebug>
Pipe::Pipe(int index,QWidget *parent):QWidget(parent)
{
    QCursor cursor;
    cursor.setShape(Qt::OpenHandCursor);
    setCursor(cursor);
    this->index = index;
}
bool Pipe::isDeleted(){
    return this->deleted;
}
void Pipe::setDeleted(bool b){
    this->deleted = b;
    if(b = false){
        this->length = 1.0;
    }
    else if(b = true){
        this->length = 0.0;
    }
}
bool Pipe::isTriggered(){
    return this->triggered;
}
void Pipe::setTriggered(bool b){
    this->triggered = b;
}

double Pipe::getLength(){
    return this->length;
}

void Pipe::paintEvent(QPaintEvent *event){//绘图事件（适应widget大小）
    QPainter painter;
    painter.begin(this);
    brush[0]= QBrush(QColor(121,205,205),Qt::SolidPattern);
    brush[1]= QBrush(QColor(245,245,220),Qt::SolidPattern);
    brush[2]= QBrush(QColor(238,180,180),Qt::SolidPattern);
    if(!isDeleted())
        painter.setBrush(brush[0]);
    else
        painter.setBrush(brush[1]);
    if(isTriggered())
        painter.setBrush(brush[2]);
    painter.drawRoundRect(0,0,this->width(),this->height(),25,25);
    painter.end();
}
//增加个音乐也不错！
void Pipe::mousePressEvent(QMouseEvent *event){//鼠标点击事件
    if(event->button() == Qt::LeftButton){//左键删除
        QCursor cursor;
        if(this->isDeleted()){//如果已经被删除，显示禁止标志
            cursor.setShape(Qt::ForbiddenCursor);
            QApplication::setOverrideCursor(cursor);
        }
        else{
            cursor.setShape(Qt::ClosedHandCursor);
            QApplication::setOverrideCursor(cursor);
            this->setDeleted(true);
            dele =new QSound(":/Bgm/operate.wav");
            dele ->play();
            this->repaint();
        }
    }
    else if(event->button() == Qt::RightButton){//右键增加

        if(!this->isDeleted()){//如果已经存在，显示禁止标志
            QCursor cursor;
            cursor.setShape(Qt::ForbiddenCursor);
            QApplication::setOverrideCursor(cursor);
        }
        else{
            QCursor cursor;
            cursor.setShape(Qt::PointingHandCursor);
            QApplication::setOverrideCursor(cursor);
            this->setDeleted(false);
            click=new QSound(":/Bgm/click.wav");
            click->play();
            this->repaint();
        }
    }
}
void Pipe::mouseDoubleClickEvent(QMouseEvent *event){//鼠标双击事件

}
void Pipe::mouseReleaseEvent(QMouseEvent *event){//鼠标释放事件
    Q_UNUSED(event);
    QApplication::restoreOverrideCursor();

}
void Pipe::wheelEvent(QWheelEvent *event){//鼠标滚轮事件

}
void Pipe::enterEvent(QEvent *event){//鼠标移入
    this->setTriggered(true);
    this->repaint();
}
void Pipe::leaveEvent(QEvent *event){//鼠标移出
    this->setTriggered(false);
    this->repaint();
}
