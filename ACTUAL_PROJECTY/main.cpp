#include "mainwindow.h"
#include<globalvar.h>
#include <QApplication>
#include<QString>
QString loggedindocemail;
QString loggedindocname;
QString loggedinstaffemail;
QString loggedinstaffname;
double stlogint;
double stlogoutt;
double dclogint;
double dclogoutt;
QString patcode;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
