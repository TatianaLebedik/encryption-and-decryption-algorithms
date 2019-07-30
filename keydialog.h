#ifndef KEYDIALOG_H
#define KEYDIALOG_H

#include <QDialog>

namespace Ui {
    class KeyDialog;
}

class KeyDialog : public QDialog {
    Q_OBJECT

public:
    explicit KeyDialog(QWidget *parent = 0);

    QString return_private_key();

    int return_q();

    int return_r();

    int return_mult_rev_r();

    ~KeyDialog();

private:
    Ui::KeyDialog *ui;
};

#endif // KEYDIALOG_H
