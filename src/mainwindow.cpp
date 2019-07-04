#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "pipe.h"
#include "board.h"
#include "calculate.cpp"
#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QtAlgorithms>
#include <QMessageBox>
#include <QLabel>
#include <QGridLayout>
#include <QPixmap>
#include <QFont>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QApplication>
#include <QVBoxLayout>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-image:url(:/Images/main.jpg);border:2px groove gray;border-radius:10px;padding:2px 4px;");
    QFont ft("Microsoft YaHei", 10);
    ft.setItalic(true);
    ui->menuBar->setFont(ft);
    ui->menuCHOOSE->setFont(ft);
    ui->LoadFileButton->setFont(ft);
    this-> setWindowTitle("Microfluidic Chip Simulation");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCalculate_triggered()//菜单栏计算按钮
{
    int num = board->getPipes();
    qDebug()<<"num："<<num<<endl;

    QVector<int>in = board->getInPipes();
     if(in.size()!=0){
        qSort(in.begin(),in.end());//排序(保证输入为乱序的时候有正确的结果)

        qDebug()<<"in1: "<<in[0]<<" in2: "<<in[1];
        QVector<int> out = board->getOutPipes();
        qSort(out.begin(),out.end());//排序
        qDebug()<<"out1: "<<out[0]<<" out2: "<<out[1]<<" out3: "<<out[2];
        QVector<double> len = board->getPipesLength();
        for(int i = 0; i < 5; i ++)
            len.append(1.0);
        qDebug()<<"size: "<<len.size();
        QVector<double> res = caluconspeed(num, len, in[0]-1, in[1]-1, out[0]-1, out[1]-1, out[2]-1);
        QString s1 = QString::number(res[0],'g',3);
        QString s2 = QString::number(res[1],'g',3);
        QString s3 = QString::number(res[2],'g',3);
        QLabel *v = new QLabel;
        v->setText(s1+" , "+s2+" , "+s3);
         v->setStyleSheet("background-image:url(:/Images/res.jpg);font-size:30px;color:#4682B4;Qt::AlignHCenter;");
        v->setFixedSize(500, 200);
        v->setAlignment(Qt::AlignCenter);
        v->setAutoFillBackground(true);
        QFont ft("Microsoft YaHei", 10);
        ft.setItalic(true);
        v->setFont(ft);
        v->setWindowTitle("Result Calculated");
        v->show();
    }
    else{//如果清空之后再点击运算按钮，则会弹出提示窗口
        QMessageBox::critical(NULL, "Warning", "Need to Initialize the Pipes!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}
void MainWindow::setPipeNumber(int num, int input1, int input2,int output1,int output2,int output3){
    board = new Board(this);
    setCentralWidget(board);
    board->initBoard(num,input1,input2,output1,output2,output3);
    board->show();


}
void MainWindow::on_actionStart_triggered()//菜单栏开始按钮
{
    indialog = new InputDialog(this);
    indialog->setModal(false);
    indialog->setFixedHeight(500);
    indialog->setFixedWidth(500);
    indialog->show();
    connect(indialog,SIGNAL(getPipeNumber(int,int,int,int,int,int)),this,SLOT(setPipeNumber(int,int,int,int,int,int)));
}
void MainWindow::on_actionClear_triggered()//菜单栏清除按钮
{
    board->clearBoard();
}
void MainWindow::on_LoadFileButton_clicked()
{
    QString fileName;//文件拓展名要展开
    qDebug()<<"Before Dialog";
    fileName = QFileDialog::getOpenFileName(this,tr("File"),"",tr("text(*.txt)"));
    qDebug()<<"After Dialog";
    int num = 8, in1 =1 ,in2 = 2, out1 =1,out2 = 2, out3 = 3;
    if(!fileName.isNull()){
        QFile file(fileName);
        if(!file.open((QFile::ReadOnly|QFile::Text))){
            QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(file.errorString()));
            return;
        }
        QTextStream in(&file);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QStringList lineStr;//如果电脑中有autodesk360这个软件，会导致报错
        int count = 0;
        while(!in.atEnd())
        {
            lineStr.append(in.readLine());
            qDebug() << lineStr[count++];
        }

        fileName = nullptr;
        num = lineStr[0].toInt();
        QStringList list1 = lineStr[1].split(QRegExp(",|\\s+"), QString::SkipEmptyParts);
        in1 = list1[0].toInt();
        in2 = list1[1].toInt();
        QStringList list2 = lineStr[2].split(QRegExp(",|\\s+"), QString::SkipEmptyParts);
        out1 = list2[0].toInt();
        out2 = list2[1].toInt();
        out3 = list2[2].toInt();
        board = new Board(this);
        setCentralWidget(board);
        board->initBoard(num,in1,in2,out1,out2,out3);
        board->show();
        QApplication::restoreOverrideCursor();
    }

}


void MainWindow::on_actionReturn_triggered()
{
    if(board == nullptr){
        QLabel *v = new QLabel;
        v->setText("This is the HomePage!");
        v->setStyleSheet("background-image:url(:/Images/main.jpg);font-size:30px;color:#4682B4;Qt::AlignHCenter;");
        v->setFixedSize(500, 200);
        v->setAlignment(Qt::AlignCenter);
        v->setAutoFillBackground(true);  //一定要这句，否则不行
        QFont ft("Microsoft YaHei", 10);
        ft.setItalic(true);
        v->setFont(ft);
        v->show();
    }
    else
    {
        qDebug()<<"HIDE";
        this->close();
        board->close();


        this->ui->setupUi(this);
        this->show();
        QLabel *v = new QLabel;
        v->setText("See You Next Time!");

        v->setStyleSheet("background-image:url(:/Images/main.jpg);font-size:30px;color:#4682B4;Qt::AlignHCenter;");
        v->setFixedSize(500, 200);
        v->setWindowTitle("GoodBye");
        v->setAlignment(Qt::AlignCenter);
        v->setAutoFillBackground(true);  //一定要这句，否则不行
        QFont ft("Microsoft YaHei", 10);
        ft.setItalic(true);
        v->setFont(ft);
        v->show();
        this->close();
    }
}
