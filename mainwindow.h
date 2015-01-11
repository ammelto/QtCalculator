#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

enum operation{noneOp, multiplyOp, divideOp, minusOp, plusOp, inverseOp, modOp, percentOp, rootOp};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void numberInput(int n);
private slots:
    void on_actionExit_triggered();
    void buttonHandler();
    void Percent();
    void Plus();
    void Clear();
    void Divide();
    void Inverse();
    void Equals();
    void Minus();
    void Modulus();
    void Sqrt();
    void Multiply();

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
