#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSound>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = 0);
    ~InputDialog();

private slots:
    void on_OKButton_clicked();

private:
    Ui::InputDialog *ui;


signals:
    void getPipeNumber(int, int, int,int,int,int );
};

#endif // DIALOG_H
