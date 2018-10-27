#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
   void GoCryption(int ind);
};

#endif // MAINWINDOW_H