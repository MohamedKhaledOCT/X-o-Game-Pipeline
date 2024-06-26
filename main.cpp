#include "mainwindow.h"

#include <QApplication>
#include <QtSql>
#include <QDebug>
#include <chrono>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase tic=QSqlDatabase::addDatabase("QSQLITE");;
    tic.setDatabaseName("C:/Qt/users_.db");
    if(!tic.open())
    {
        qDebug()<<"problem";
    }
    qDebug()<<"problem";

    MainWindow w;
    w.show();
    return a.exec();
}
