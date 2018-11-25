#include "keydialog.h"
#include "ui_keydialog.h"

KeyDialog::KeyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyDialog)
{
    ui->setupUi(this);
}

QString KeyDialog::return_private_key(){
    return ui->private_key_textEdit->toPlainText();
}

int KeyDialog::return_q(){
    return ui->q_spinBox->value();
}

int KeyDialog::return_r(){
    return ui->r_spinBox->value();
}

int KeyDialog::return_mult_rev_r(){
    return ui->mult_rev_r_spinBox->value();
}


KeyDialog::~KeyDialog()
{
    delete ui;
}
