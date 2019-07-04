#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QMultimedia>
#include <QSound>

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    QFont ft("Microsoft YaHei", 10);
    ft.setItalic(true);
    this->setStyleSheet("background-image:url(:/Images/label.jpg);border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->InputPipe1->setFont(ft);
    ui->InputPipe2->setFont(ft);
    ui->label->setFont(ft);
    ui->label_2->setFont(ft);
    ui->label_3->setFont(ft);
    ui->label_4->setFont(ft);
    ui->label_5->setFont(ft);
    ui->label_6->setFont(ft);
    ui->label_7->setFont(ft);
    ui->label_8->setFont(ft);
    ui->OKButton->setFont(ft);
    ui->NumInput->setFont(ft);
    ui->OutputPipe1->setFont(ft);
    ui->OutputPipe2->setFont(ft);
    ui->OutputPipe3->setFont(ft);
    this->setWindowTitle("Pipes Structure");
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::on_OKButton_clicked()
{
    QString num =  ui->NumInput->text();

    QString input1 = ui->InputPipe1->text();
    QString input2 = ui->InputPipe2->text();

    QString output1 = ui->OutputPipe1->text();
    QString output2 = ui->OutputPipe2->text();
    QString output3 = ui->OutputPipe3->text();


    if(num < "5" || num > "8")
        QMessageBox::critical(NULL, "Warning", "Wrong Input!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    else{
        QString input1 = ui->InputPipe1->text();
        QString input2 = ui->InputPipe2->text();
        if((input1 == input2)||(input1 > num)||(input1 <= "0")||(input2 > num)||(input2 <= "0"))
            QMessageBox::critical(NULL, "Warning", "Wrong Input!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        else{
            QString output1 = ui->OutputPipe1->text();
            QString output2 = ui->OutputPipe2->text();
            QString output3 = ui->OutputPipe3->text();
            if((output1 == output2)||(output1 == output3)||(output2 == output3))
                QMessageBox::critical(NULL, "Warning", "Wrong Input!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            else if((output1<="0")||(output1>num)||(output2<="0")||(output2>num)||(output3<="0")||(output3>num))
                QMessageBox::critical(NULL, "Warning", "Wrong Input!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            else{//开始创建管道
                qDebug()<<"STARTING CONSTRUCTIING PIPES!";
                bool ok;
                int Num = num.toInt(&ok);
                int Input1 = input1.toInt(&ok);
                int Input2 = input2.toInt(&ok);
                int Output1 = output1.toInt(&ok);
                int Output2 = output2.toInt(&ok);
                int Output3 = output3.toInt(&ok);
                emit getPipeNumber(Num, Input1, Input2, Output1,Output2,Output3);
                close();
            }
        }
    }
}
