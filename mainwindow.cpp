#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    glwidget = new GLWidget();

#ifdef Q_WS_MAEMO_5
    glwidget->showFullScreen();
#else
    glwidget->show();
#endif

    close();
}
