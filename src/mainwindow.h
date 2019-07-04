#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    InputDialog *indialog;
    Board *board;
    Pipe *pipe;

signals:
    void loadSignal(QString filename);
private slots:
    void on_actionCalculate_triggered();
    void on_actionStart_triggered();
    void on_actionClear_triggered();
    void setPipeNumber(int,int, int,int,int,int);
    void on_LoadFileButton_clicked();
    void on_actionReturn_triggered();
};

#endif // MAINWINDOW_H
