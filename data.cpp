#include "data.h"

DATA::DATA() {
    data = "\0";
    alphabet.append(
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890.,:;+-=_<>/?!'\"|\\~`#$%^&*(){}[]\ \t\n");
    //  Validation();
}

DATA::DATA(QString data) {

    this->data.append(data);
    alphabet.append(
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890.,:;+-=_<>/?!'\"|\\~`#$%^&*(){}[]\ \t\n");
    //  Validation();
}

DATA::DATA(QString data, int id) {

    this->data.append(data);

    if (id == 0) {//en
        alphabet.append(
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890.,:;+-=_<>/?!'\"|\\~`#$%^&*(){}[]\ \t\n");
    }
    if (id == 1) {//ru
        alphabet.append(
                "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя1234567890.,:;<>+-=_/?!'\"|\\~`#$%^&*(){}[]\ \t\n");
    }
    if (id == 2) {//uk
        alphabet.append(
                "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯабвгґдеєжзиіїйклмнопрстуфхцчшщьюя1234567890.,:;<>+-=_/?!'\"|\\~`#$%^&*(){}[]\ \t\n");
    }
    if (id == 3) {
        alphabet.append(
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯабвгґдеєжзиіїйклмнопрстуфхцчшщьюя1234567890.,:;<>+-=_/?!'\"|\\~`#$%^&*(){}[]\ \t\n");

    }
    //  Validation();

}

QString DATA::LoadFromFile() {

    QString path = QFileDialog::getOpenFileName(0, "Open", "", "*.cpp *.h *.txt *.pro");
    qDebug() << path;
    QFile file(path);
    file.open(QIODevice::ReadOnly);

    if (file.isOpen()) {
        QString temp = file.readAll();
        return temp;
    } else {
        return "\0";
    }
}

bool DATA::SaveToFile(QString str) {

    QString path = QFileDialog::getSaveFileName(0, "Save", "", ".cpp *.h *.txt *.pro");
    QFile file(path);
    file.open(QIODevice::WriteOnly);

    if (file.isOpen()) {
        QTextStream stream(&file);
        stream << str;
        return 0;
    } else {

        return 1;
    }

}

bool DATA::Print() {

    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer);

    if (dialog->exec() == QDialog::Accepted) {
        QTextDocument TextDocument;
        TextDocument.setPlainText(data);
        TextDocument.print(&printer);
    }

}

void DATA::Validation() {
    for (int i = 0; i < data.length(); i++) {
        for (int j = 0; j < alphabet.length(); j++) {
            if (data.at(i) == alphabet.at(j)) {
                break;
            } else {
                if (j == alphabet.length() - 1) {
                    QMessageBox::StandardButton verify = QMessageBox::critical(0, "Oops: We have problem!",
                                                                               "Some symbol can not be encrypted/decrypted! \nCheck lenguage you chose.");
                    i = data.length() + 1;
                    break;
                }
            }
        }
    }
}
