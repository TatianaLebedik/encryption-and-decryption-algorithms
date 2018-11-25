#ifndef DATA_H
#define DATA_H

//#include "mainwindow.h"

#include<QString>
#include<QMessageBox>
#include <QFileDialog>
#include <QIODevice>
#include <QFile>
#include<QDebug>
#include <QPrinter>
#include<QTextDocument>
#include<QPrintDialog>

class DATA
{
protected:
    QString data;
    QString alphabet;
    void Validation();
public:
    DATA();
    DATA(QString data);
    DATA(QString data,  int id);
    QString LoadFromFile();
    bool SaveToFile(QString str);
    bool Print();
};

#endif // DATA_H
