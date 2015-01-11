#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include <QPointer>
#include <QKeyEvent>
#include <QDebug>

static int curOp;

/**
 * @brief MainWindow::MainWindow Constructor for the main window.
 * @details Sets up the UI and connects the signals and sockets.
 * @param parent Parent Qwidget
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Sets up initial UI constraints
    ui->setupUi(this);
    ui->numberField->setReadOnly(true);
    ui->numberField->setText("0");

    curOp = 0;

    //Very ineffecient way to connect button signals to the slot handler
    //Will improve this later, may try an array of button objects.
    //TODO: Fix spaghetti code
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Percent, SIGNAL(clicked()), this, SLOT(Percent()));
    connect(ui->pushButton_Period, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Plus, SIGNAL(clicked()), this, SLOT(Plus()));
    connect(ui->pushButton_Clear, SIGNAL(clicked()), this, SLOT(Clear()));
    connect(ui->pushButton_Divide, SIGNAL(clicked()), this, SLOT(Divide()));
    connect(ui->pushButton_Inverse, SIGNAL(clicked()), this, SLOT(Inverse()));
    connect(ui->pushButton_Equals, SIGNAL(clicked()), this, SLOT(Equals()));
    connect(ui->pushButton_Minus, SIGNAL(clicked()), this, SLOT(Minus()));
    connect(ui->pushButton_Multiply, SIGNAL(clicked()), this, SLOT(Multiply()));
    connect(ui->pushButton_Modulus, SIGNAL(clicked()), this, SLOT(Modulus()));
    connect(ui->pushButton_Sqrt, SIGNAL(clicked()), this, SLOT(Sqrt()));

    qDebug() << "launched";
}

/**
 * @brief MainWindow::~MainWindow Deconstructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_actionExit_triggered Exit command via drop down menu
 */
void MainWindow::on_actionExit_triggered()
{
    //Quits application
    QApplication::quit();
}
/**
 * @brief MainWindow::keyPressEvent Function to listen for keyboard button presses.
 * @details allows keypad to be used for calculations.
 * @param event gets current get pressed as an event object
 */
void MainWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_0: emit ui->pushButton_0->clicked(true);
        break;
    case Qt::Key_1: emit ui->pushButton_1->clicked(true);
        break;
    case Qt::Key_2: emit ui->pushButton_2->clicked(true);
        break;
    case Qt::Key_3: emit ui->pushButton_3->clicked(true);
        break;
    case Qt::Key_4: emit ui->pushButton_4->clicked(true);
        break;
    case Qt::Key_5: emit ui->pushButton_5->clicked(true);
        break;
    case Qt::Key_6: emit ui->pushButton_6->clicked(true);
        break;
    case Qt::Key_7: emit ui->pushButton_7->clicked(true);
        break;
    case Qt::Key_8: emit ui->pushButton_8->clicked(true);
        break;
    case Qt::Key_9: emit ui->pushButton_9->clicked(true);
        break;
    case Qt::Key_Asterisk: emit ui->pushButton_Multiply->clicked(true);
        break;
    case Qt::Key_Slash: emit ui->pushButton_Divide->clicked(true);
        break;
    case Qt::Key_Minus: emit ui->pushButton_Minus->clicked(true);
        break;
    case Qt::Key_Plus: emit ui->pushButton_Plus->clicked(true);
        break;
    case Qt::Key_Enter: emit ui->pushButton_Equals->clicked(true);
        break;
    case Qt::Key_Period: emit ui->pushButton_Period->clicked(true);
        break;
    }
}
\
/**
 * @brief MainWindow::buttonHandler Handles the button events of 0 through 9
 * @details Creates an object from the event sender then compares the sender to the buttons to get the appropriate number pressed.
 */
void MainWindow::buttonHandler(){
    QObject* obj = sender();
//Cannot use a switch here since QObjects cannot be casted as integral types.
    //TODO: Find alternative to if/else chain

    if(obj == ui->pushButton_1){
          numberInput(1);
  }else if(obj == ui->pushButton_2){
          numberInput(2);
  }else if(obj == ui->pushButton_3){
          numberInput(3);
  }else if(obj == ui->pushButton_4){
          numberInput(4);
  }else if(obj == ui->pushButton_5){
          numberInput(5);
  }else if(obj == ui->pushButton_6){
          numberInput(6);
  }else if(obj == ui->pushButton_7){
          numberInput(7);
  }else if(obj == ui->pushButton_8){
          numberInput(8);
  }else if(obj == ui->pushButton_9){
          numberInput(9);
  }else if(obj == ui->pushButton_0){
          numberInput(0);
  }else if(obj == ui->pushButton_Period){
          numberInput(-1);
  }
}

//TODO: Implement functions
void MainWindow::Percent(){
     qDebug() << "%";
     curOp = percentOp;
}
void MainWindow::Plus(){
     qDebug() << "+";
     curOp = plusOp;
}
void MainWindow::Clear(){
     qDebug() << "CLEAR";
     curOp = noneOp;
     ui->numberField->setText("0");
}
void MainWindow::Divide(){
     qDebug() << "/";
     curOp = divideOp;
}
void MainWindow::Inverse(){
     qDebug() << "1/x";
     curOp = inverseOp;
}
void MainWindow::Equals(){
     qDebug() << "=";
}
void MainWindow::Minus(){
     qDebug() << "-";
     curOp = minusOp;
}
void MainWindow::Modulus(){
     qDebug() << "mod";
     curOp = modOp;
}
void MainWindow::Sqrt(){
     qDebug() << "Sqrt";
     curOp = rootOp;
}
void MainWindow::Multiply(){
     qDebug() << "*";
     curOp = multiplyOp;
}
void MainWindow::numberInput(int n){

    qDebug() << ui->numberField->toPlainText().length() << " " << curOp;

    if(ui->numberField->toPlainText() == "0"){
        ui->numberField->setText("");
    }else if(16 <= ui->numberField->toPlainText().length()){
        return;
    }

    if((n == -1) && !(ui->numberField->toPlainText().contains("."))){
        ui->numberField->setText(ui->numberField->toPlainText() + ".");
    }else if(n != -1){
        ui->numberField->setText(ui->numberField->toPlainText() + QString::number(n));
    }
}
