#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include <QPointer>
#include <QKeyEvent>
#include <QDebug>
#include <functional>

static int curOp;
static double memory;
static bool newIn;
static int tempOp;

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
    memory = 0;
    newIn = true;

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
    connect(ui->pushButton_Percent, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Period, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Plus, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Clear, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Divide, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Inverse, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Equals, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Minus, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Multiply, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Modulus, SIGNAL(clicked()), this, SLOT(buttonHandler()));
    connect(ui->pushButton_Sqrt, SIGNAL(clicked()), this, SLOT(buttonHandler()));

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
  }else if(obj == ui->pushButton_Percent){
        handleCurOp(percentOp);
  }else if(obj == ui->pushButton_Plus){
        handleCurOp(plusOp);
  }else if(obj == ui->pushButton_Clear){
        curOp = noneOp; //Clears all fields, acts as a true clear. No CE yet
        ui->memory->setText("");
        memory = 0;
        newIn = true;
        ui->numberField->setText("0");
  }else if(obj == ui->pushButton_Divide){
        handleCurOp(divideOp);
  }else if(obj == ui->pushButton_Inverse){
        curOp = inverseOp;  //This allows the inverse to have the highest priority and cannot be chained (treated as a power)
        handleCurOp(noneOp);
  }else if(obj == ui->pushButton_Equals){
            handleCurOp(equalsOp);
  }else if(obj == ui->pushButton_Minus){
        if((newIn || (curOp == minusOp && newIn)) && ui->numberField->toPlainText() != "-"){
            ui->numberField->setText("-"); //this allows the user to use the minus operation to input negatives
            newIn = false;
        }else if(ui->numberField->toPlainText() == "-" && !newIn){
            ui->numberField->setText("0");
            newIn = true;
            return;
        }else{
            handleCurOp(minusOp);
        }
  }else if(obj == ui->pushButton_Modulus){
        handleCurOp(modOp);
  }else if(obj == ui->pushButton_Sqrt){
        curOp = rootOp; //This allows the sprt to have the highest priority and cannot be chained (treated as a power)
        handleCurOp(noneOp);
  }else if(obj == ui->pushButton_Multiply){
        handleCurOp(multiplyOp);
  }
}

/**
 * @brief MainWindow::handleCurOp Handles the current queued operation before changing to the new operation
 * @param newOp This is the new operation selected by the user via clicking the buttons
 */
void MainWindow::handleCurOp(operation newOp){
    bool ok = false;
    double val = ui->numberField->toPlainText().toDouble(&ok);

    switch(curOp){
    case noneOp: memory = val;
        break;
    case rootOp: memory = sqrt(val);
        break;
    case multiplyOp: memory = memory * val;
        break;
    case minusOp: memory = memory - val;
        break;
    case divideOp: memory = memory / val;
        break;
    case plusOp: memory = memory + val;
        break;
    case modOp: memory = fmod(memory,val);
        break;
    case percentOp: memory = (val * memory) / 100;
        break;
    case inverseOp: memory = pow(val,-1);
        break;
    }
    ui->numberField->setText(QString::number(memory));
    QString str = getOp(newOp);

    //Echos operations into memory bank
    if(str != "NAN" && ui->memory->toPlainText().length() <= 32){
        ui->memory->setText(ui->memory->toPlainText() + " " + QString::number(val) + " " + str);
    }else if((newOp = equalsOp) && ui->memory->toPlainText().length() <= 32){
        str = getOp((operation)curOp);
        ui->memory->setText(ui->memory->toPlainText() + " " + QString::number(val) + " " + str);
    }else{
        ui->memory->setText("");
    }

    newIn = true;

    if(newOp == equalsOp){
        return;
    }else{
        curOp = newOp;
    }


}

/**
 * @brief MainWindow::getOp translates operation enum into qstring
 * @param op operation to be converted
 * @return returns a string or nan if not chainable.
 */
QString MainWindow::getOp(operation op){
    //noneOp, multiplyOp, divideOp, minusOp, plusOp, inverseOp, modOp, percentOp, rootOp, equalsOp
    switch(op){
    case plusOp: return "+";
    case multiplyOp: return "*";
    case divideOp: return "/";
    case minusOp: return "-";
    case modOp: return "mod";
    case percentOp: return "%";
    }
    return "NAN";
}

/**
 * @brief MainWindow::numberInput Allows for the input of numeric values
 * @param n The current digit the user has selected (-1 represents a period)
 */
void MainWindow::numberInput(int n){
    if(newIn){    //Clears the current field when the user begins a new number
            ui->numberField->setText("");
    }else if(16 <= ui->numberField->toPlainText().length()){
        return;
    }
    if((n == -1) && !(ui->numberField->toPlainText().contains("."))){   //Allows for only one decimal point
        if(ui->numberField->toPlainText() == ""){
            ui->numberField->setText("0."); //Doubles require a leading zero when being compared to other values 0<x<1
        }else{
            ui->numberField->setText(ui->numberField->toPlainText() + ".");
        }
    }else if(n != -1){
        ui->numberField->setText(ui->numberField->toPlainText() + QString::number(n));  //Creates a string of numbers
    }
    newIn = false;
}
