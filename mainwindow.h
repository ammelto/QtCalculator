#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

enum operation{noneOp, multiplyOp, divideOp, minusOp, plusOp, inverseOp, modOp, percentOp, rootOp, equalsOp};

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
    QString getOp(operation op);
private slots:
    void on_actionExit_triggered();
    void buttonHandler();
    void handleCurOp(operation newOp);

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
