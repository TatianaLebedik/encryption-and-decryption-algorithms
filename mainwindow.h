#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bag.h"
#include <QMainWindow>
#include "keydialog.h"

class BAG;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionAdd_to_Current_triggered();

    void on_actionSave_triggered();

    void on_actionPrint_triggered();

    void on_actionEncrypt_triggered();

    void on_actionDecrypt_triggered();

    void on_bag_create_key_pushButton_clicked();

private:
    Ui::MainWindow *ui;
   bool bag_object_was_create = 0;
   void GoCryption(int ind);
   BAG Object;
};

#endif // MAINWINDOW_H
