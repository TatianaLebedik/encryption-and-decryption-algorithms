#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"
#include "caesar.h"
#include "trithemius.h"
#include "vernam.h"
#include "book.h"
#include "des.h"
#include <vector>
#include <QMessageBox>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    ui->main_textEdit->clear();
    DATA Object;
    ui->main_textEdit->append(Object.LoadFromFile());
}

void MainWindow::on_actionAdd_to_Current_triggered() {
    DATA Object;
    ui->main_textEdit->append(Object.LoadFromFile());
}

void MainWindow::on_actionSave_triggered() {
    DATA Object;
    Object.SaveToFile(ui->main_textEdit->toPlainText());
}

void MainWindow::on_actionPrint_triggered() {
    DATA Object(ui->main_textEdit->toPlainText());
    Object.Print();
}

void MainWindow::on_actionEncrypt_triggered() {
    int ind = 1;
    GoCryption(ind);

}

void MainWindow::on_actionDecrypt_triggered() {
    int ind = 0;
    GoCryption(ind);
}


void MainWindow::on_bag_create_key_pushButton_clicked() {

    KeyDialog asyn_private_key_dialog;
    if (asyn_private_key_dialog.exec()) {
        //  ui->main_textEdit->append(asyn_private_key_dialog.return_private_key());
        ui->bag_public_key_textEdit->clear();
        ui->bag_public_key_textEdit->append(Object.Create_Key_Pair(asyn_private_key_dialog.return_private_key(),
                                                                   asyn_private_key_dialog.return_q(),
                                                                   asyn_private_key_dialog.return_r(),
                                                                   asyn_private_key_dialog.return_mult_rev_r()));


    }
}


void MainWindow::GoCryption(int ind) {

    int language;


    if (ui->En_radioButton->isChecked()) {
        language = 0;
    }
    if (ui->Ru_radioButton->isChecked()) {
        language = 1;
    }
    if (ui->Uk_radioButton->isChecked()) {
        language = 2;
    }


    if (ui->caesar_page->isVisible()) {

        QString str = ui->main_textEdit->toPlainText();
        CAESAR Object(str, language);
        ui->main_textEdit->clear();
        ui->main_textEdit->append(Object.Cryption(ui->caesar_spinBox->value(),
                                                  bool(ind)));
    }
    if (ui->trit_linear_page->isVisible()) {

        int a = ui->trit_linear_a_spinBox->value();
        int b = ui->trit_linear_b_spinBox->value();
        QString str = ui->main_textEdit->toPlainText();
        TRITHEMIUS Object(str, language);
        ui->main_textEdit->clear();
        ui->main_textEdit->append(Object.Cryption(a, b, ind));
    }
    if (ui->trit_non_linear_equation_page->isVisible()) {

        QString str = ui->main_textEdit->toPlainText();
        TRITHEMIUS Object(str, language);
        ui->main_textEdit->clear();
        ui->main_textEdit->append(Object.Cryption(ui->trit_non_linear_a_spinBox->value(),
                                                  ui->trit_non_linear_b_spinBox->value(),
                                                  ui->trit_non_linear_c_spinBox->value(),
                                                  ind));
    }
    if (ui->slogan_page->isVisible()) {
        QString str = ui->main_textEdit->toPlainText();
        TRITHEMIUS Object(str, language);
        ui->main_textEdit->clear();
        ui->main_textEdit->append(Object.Cryption(ui->trit_slogan_textEdit->toPlainText(),
                                                  ind));
    }
    if (ui->vernam_page->isVisible()) {
        QString str = ui->main_textEdit->toPlainText();
        VERNAM Object(str, language);
        ui->main_textEdit->clear();
        ui->main_textEdit->append(Object.Cryption(ind, ui->seed_spinBox->value()));
    }
    if (ui->book_page->isVisible()) {
        QString str = ui->main_textEdit->toPlainText();
        BOOK Object(str);
        ui->main_textEdit->clear();
        ui->main_textEdit->append(Object.Cryption(ind, ui->poem_textEdit->toPlainText()));
    }
    if (ui->des_page->isVisible()) {
        QString key = ui->des_textEdit->toPlainText();
        int check = key.length() * sizeof(QChar);
        qDebug() << " Key length: " << check;

        if (check > 16) {
            QMessageBox::critical(0, "Critical", "Key is too long!");


        } else {

            QString str = ui->main_textEdit->toPlainText();
            DES Object(str);
            ui->main_textEdit->clear();
            ui->main_textEdit->append(Object.Cryption(ind, ui->des_textEdit->toPlainText().toUtf8().toBase64()));

        }

    }

    if (ui->bag_page->isVisible()) {
        QString str = ui->main_textEdit->toPlainText();
        if (bag_object_was_create == true) {
            ui->main_textEdit->clear();
            ui->main_textEdit->append(Object.Cryption(ind, ui->bag_public_key_textEdit->toPlainText(), str));
        } else if (ind == 1) {
            ui->main_textEdit->clear();
            ui->main_textEdit->append(Object.Cryption(ind, ui->bag_public_key_textEdit->toPlainText(), str));
        } else {
            ui->main_textEdit->clear();
            ui->main_textEdit->append(Object.Cryption(ind, ui->bag_public_key_textEdit->toPlainText(), str));
        }
    }

    if (ui->rsa_page->isVisible()) {


        QString str = ui->main_textEdit->toPlainText();

        if (ind == 1) {
            ui->main_textEdit->clear();
            ui->main_textEdit->append(RsaObject->Cryption(ind, str).toUtf8().toBase64());
            ui->main_textEdit->setReadOnly(true);
        } else {
            ui->main_textEdit->clear();
            ui->main_textEdit->append(RsaObject->Cryption(ind, str));
            ui->main_textEdit->setReadOnly(false);
        }
    }
}

void MainWindow::on_rsa_create_key_pair_pushButton_clicked() {
    RsaObject = new RSA_CLASS;
    ui->rsa_public_key_textEdit->clear();
    ui->rsa_private_key_textEdit->clear();
    std::vector <QString> keys(RsaObject->CreateKeys());
    ui->rsa_public_key_textEdit->append(keys.at(0).toUtf8().toBase64());
    ui->rsa_private_key_textEdit->append(keys.at(1).toUtf8().toBase64());
}
