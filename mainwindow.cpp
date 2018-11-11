#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"
#include "caesar.h"
#include "trithemius.h"
#include "vernam.h"
#include "book.h"
#include "des.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    ui->main_textEdit->clear();
    DATA Object;
    ui->main_textEdit->append(Object.LoadFromFile());
}

void MainWindow::on_actionAdd_to_Current_triggered()
{
    DATA Object;
    ui->main_textEdit->append(Object.LoadFromFile());
}

void MainWindow::on_actionSave_triggered()
{
    DATA Object;
    Object.SaveToFile(ui->main_textEdit->toPlainText());
}

void MainWindow::on_actionPrint_triggered()
{
    DATA Object(ui->main_textEdit->toPlainText());
    Object.Print();
}

void MainWindow::on_actionEncrypt_triggered()
{
    int ind = 1;
    GoCryption(ind);

}

void MainWindow::on_actionDecrypt_triggered()
{
   int ind = 0;
   GoCryption(ind);
}

void MainWindow::GoCryption(int ind){


    int language;


    if(ui->En_radioButton->isChecked()){
     language = 0;
    }
    if(ui->Ru_radioButton->isChecked()){
     language = 1;
    }
    if(ui->Uk_radioButton->isChecked()){
     language = 2;
    }


    if(ui->caesar_page->isVisible()){

          QString str = ui->main_textEdit->toPlainText() ;
          CAESAR Object(str,language);
          ui->main_textEdit->clear();
          ui->main_textEdit->append(Object.Cryption( ui->caesar_spinBox->value(),
                                                      bool(ind)));
    }
    if(ui->trit_linear_page->isVisible()){

          int a =ui->trit_linear_a_spinBox->value();
          int b =ui->trit_linear_b_spinBox->value();
          QString str = ui->main_textEdit->toPlainText() ;
          TRITHEMIUS Object(str,language);
          ui->main_textEdit->clear();
          ui->main_textEdit->append(Object.Cryption(a, b,ind));
    }
    if(ui->trit_non_linear_equation_page->isVisible()){

          QString str = ui->main_textEdit->toPlainText() ;
          TRITHEMIUS Object(str,language);
          ui->main_textEdit->clear();
          ui->main_textEdit->append(Object.Cryption(ui->trit_non_linear_a_spinBox->value(),
                                                    ui->trit_non_linear_b_spinBox->value(),
                                                    ui->trit_non_linear_c_spinBox->value(),
                                                    ind));
    }
    if(ui->slogan_page->isVisible()){
          QString str = ui->main_textEdit->toPlainText() ;
          TRITHEMIUS Object(str,language);
          ui->main_textEdit->clear();
          ui->main_textEdit->append(Object.Cryption(ui->trit_slogan_textEdit->toPlainText(),
                                                    ind));
    }
    if(ui->vernam_page->isVisible()){
          QString str = ui->main_textEdit->toPlainText() ;
          VERNAM Object(str,language);
          ui->main_textEdit->clear();
          ui->main_textEdit->append(Object.Cryption(ind, ui->seed_spinBox->value()));
    }
    if(ui->book_page->isVisible()){
          QString str = ui->main_textEdit->toPlainText() ;
          BOOK Object(str);
          ui->main_textEdit->clear();
          ui->main_textEdit->append(Object.Cryption(ind, ui->poem_textEdit->toPlainText()));
    }
    if(ui->des_page->isVisible()){

        QString str = ui->main_textEdit->toPlainText();
          DES Object(str);
          ui->main_textEdit->clear();
          if(ind == 1){
              QString temp;
              temp = Object.Cryption(ind, ui->des_textEdit->toPlainText().toUtf8().toBase64());

              QString str1;
                  ushort val = 0;
                  for (int i = 0; i < temp.length(); i++)
                  {

                      val = temp[i].toLatin1();
                      str1 = str1 + QString("0x") + QString("%1 ").arg(val, 0, 8).rightJustified(3, '0').right(3);
                  }
                  //return str1.trimmed();


//               ui->main_textEdit->append(str1.trimmed());

               ui->main_textEdit->append(temp);
          }
          else{

            ui->main_textEdit->append(Object.Cryption(ind, ui->des_textEdit->toPlainText().toUtf8().toBase64()));

          }

    }

}
