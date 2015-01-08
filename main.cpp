/**
  * @author Alexander Melton
  * @version 0.1a pre-release
  * @copyright MIT License
  *
  * @brief Simple calculator created using Qt and c++
  * Currently, I'm attempting to learn c++ and Qt at the same time.
  * The code should become cleaner as I work on the project.
  * I plan on making several more complex applications using Qt and C++.
  * Once I am more familiar with c++ and Qt I may try and do some work with SDL
  */
#include "mainwindow.h"
#include <QApplication>

/**
 * @brief main Creates the main window widget
 * @param argc Command line arguments are passed to the main window
 * @param argv Command line arguments are passed to the main window
 * @return Enters the main event loop
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
