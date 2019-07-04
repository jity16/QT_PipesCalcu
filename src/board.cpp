#include "board.h"

Board::Board(QWidget *parent):QWidget(parent){
    for(int i = 0; i < 8; i ++){//画竖着的管子
        for(int j = 0; j < 7; j ++){
            Pipe *pipe = new Pipe(i*7 +j,this);
            pipe->setGeometry((offset_x+90*i),(90*(j+1)+offset_y),10,80);
            pipes.append(pipe);
        }
    }
    for(int i = 0; i < 7; i ++){//画横着的管子
        for(int j = 0; j < 8; j ++){
            Pipe *pipe = new Pipe(56+i*8 +j,this);
            pipe->setGeometry((offset_x+90*i+10),(90*(j+1)+offset_y-10),80,10);
            pipes.append(pipe);
        }
    }
    for(int x = 0; x < 8; x ++){//绘制初始节点
        for(int y = 0; y < 8; y ++){
            Node *node = new Node(x,y,this);
            node ->setGeometry((offset_x+90*x-3),(offset_y+90*(y+1)-13),16,16);
            nodes.append(node);
        }
    }

    for(int i = 0; i < 2 ; i ++){//初始化所有输入的管子
        Pipe *pipe = new Pipe(112+i,this);
        pipe->setGeometry((offset_x+90*i),offset_y,10,80);
        inPipes.append(pipe);
    }
    for(int i = 0; i < 3 ; i ++){//初始化所有输出的管子
        Pipe *pipe = new Pipe(114+i,this);
        pipe->setGeometry((offset_x+90*i),offset_y+90*8,10,80);
        outPipes.append(pipe);
    }


}
void Board::getLeftClicked(int index, QMouseEvent *event){
    pipes[index]->repaint();
}

void Board::initBoard(int num,int in1,int in2,int out1,int out2,int out3){
    for(int i = 0; i < 8; i ++){
        for(int j = 0 ; j < 7 ; j ++){
            if(i >= num || j >= num - 1){
                pipes[i*7+j]->setDeleted(true);
            }
        }
    }
    for(int i = 0; i < 7; i ++){
        for(int j = 0; j < 8; j ++){
            if(i >= num-1 || j >= num){
                pipes[56+i*8 +j]->setDeleted(true);
            }
        }
    }

    for(int i = 0; i < 112; i ++){
        connect(pipes[i],SIGNAL(LeftClicked(int,QMouseEvent*)),this,SLOT(getLeftClicked(int,QMouseEvent*)));
    }

    //画出两根输入管道
    inpipe.append(in1);
    inpipe.append(in2);
    inPipes[0]->setGeometry((offset_x+90*(in1-1)),offset_y,10,80);
    inPipes[1]->setGeometry((offset_x+90*(in2-1)),offset_y,10,80);


    //画出三个输出管道
    outpipe.append(out1);
    outpipe.append(out2);
    outpipe.append(out3);
    outPipes[0]->setGeometry((offset_x+90*(out1-1)),offset_y + 8*90,10,80);
    outPipes[1]->setGeometry((offset_x+90*(out2-1)),offset_y + 8*90,10,80);
    outPipes[2]->setGeometry((offset_x+90*(out3-1)),offset_y + 8*90,10,80);
}
int Board::getPipes(){
    int max1 = 0;
    for(int i = 0 ; i < 8; i ++)
    {
        int num = 0;
        for(int j = 0; j < 7; j ++)
        {
            if(pipes[i*7+j]->isDeleted()){
                num = j;
                break;
            }
        }
        if(num > max1)
            max1 = num;
    }
    max1 ++;
    int max2 = 0;
    for(int j = 0; j < 8;j ++){
        int num = 0;
        for(int i = 0; i < 7; i ++){
            if(pipes[56+i*8+j]->isDeleted()){
                num = i;
                break;
            }
        }
        if(num > max2)
            max2 = num;
    }
    max2++;
    if(max1 > max2)
        return max1;
    else
        return max2;
}

QVector<int> Board::getInPipes(){
    return inpipe;
}

QVector<int> Board::getOutPipes(){
    return outpipe;
}
QVector<double> Board::getPipesLength(){
    int num = getPipes();
    for(int i = 0; i < num; i ++)
        for(int j = 0; j < num -1; j ++)
        {
            if(pipes[i*7+j]->isDeleted())
                pipeslen.append(0.0);
            else
                pipeslen.append(1.0);
        }
    for(int i = 0 ; i < num-1; i ++)
        for(int j = 0 ; j < num; j ++){
            if(pipes[56+i*8+j]->isDeleted())
                pipeslen.append(0.0);
            else
                pipeslen.append(1.0);
        }
    return pipeslen;
}

void Board::clearBoard(){
    for(int i = 0; i < 112; i ++){
        pipes[i]->setDeleted(true);
        pipes[i]->repaint();
    }
    for(int i = 0; i < 2; i ++){
        inPipes[i]->setDeleted(true);
        inPipes[i]->repaint();
    }
    for(int i = 0; i < 3; i ++){
        outPipes[i]->setDeleted(true);
        outPipes[i]->repaint();
    }
    inpipe.clear();
    outpipe.clear();
    pipeslen.clear();
}
