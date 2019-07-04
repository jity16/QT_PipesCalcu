#ifndef BOARD_H
#define BOARD_H
#include "pipe.h"
#include "node.h"
#include <QWidget>
#include <map>
#include <QGroupBox>
class Board: public QWidget{
    Q_OBJECT
public:

    explicit Board(QWidget *parent = nullptr);

    void clearBoard();
    void initBoard(int,int,int,int,int,int);//获得对话框输入后进行初始构建
    int getPipes();


    QVector<int> getInPipes();
    QVector<int> getOutPipes();
    QVector<double> getPipesLength();
signals:

public slots:
    void getLeftClicked(int index,QMouseEvent *event);

protected:



private:
    QVector<Pipe *> pipes;
    QVector<Pipe *> inPipes;
    QVector<Pipe *> outPipes;
    QVector<Node *> nodes;

    int num = 8;
    QVector<int> inpipe;
    QVector<int>  outpipe;
    int offset_x = 50;
    int offset_y = 50;

    QVector<double> pipeslen;//存储网格管道的length



};

#endif // BOARD_H
