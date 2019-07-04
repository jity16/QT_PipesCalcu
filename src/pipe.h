#ifndef PIPE_H
#define PIPE_H
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QEvent>
#include <QtMultimedia/QSound>
class Pipe: public QWidget{
    Q_OBJECT
public:
    explicit Pipe(int index,QWidget *parent = nullptr);

    bool isTriggered();
    bool isDeleted();

    void setTriggered(bool);
    void setDeleted(bool);//bool = true时，删除该管道,并将被删除的管道的长度设置为0
    double getLength();
    void setSize(int width);//修改管道宽度


signals:
    void LeftClicked(int index,QMouseEvent *event);

public slots:

protected:
    void paintEvent(QPaintEvent *event);//绘图事件
    void mousePressEvent(QMouseEvent *event);//鼠标按下事件
    void mouseDoubleClickEvent(QMouseEvent *event);//鼠标双击事件
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放事件
    void wheelEvent(QWheelEvent *event);//鼠标滚轮事件
    void enterEvent(QEvent *event);//鼠标移入
    void leaveEvent(QEvent *event);//鼠标移出

private:
    int index;
    QSound *click;
    QSound * dele;
    double length = 1.0; //管道长度，先默认为1.0
    QPoint offset;//存储鼠标指针位置与窗口位置的差值
    QBrush brush[3];//brush[0]为初始管道颜色，brush[1]为高亮颜色
    bool triggered = false;
    bool deleted = false;
};

#endif // PIPE_H
