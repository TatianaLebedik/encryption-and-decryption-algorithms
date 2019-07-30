#include "trithemius.h"

TRITHEMIUS::TRITHEMIUS() : CAESAR() {}

TRITHEMIUS::TRITHEMIUS(QString inp_data, int inp_language) : CAESAR(inp_data, inp_language) {}


QString TRITHEMIUS::Cryption(int a, int b, int ind) {   //ind - indicator for encryption or decryptyon

    int key;
    QString outgoing_data;

    for (int i = 0; i < data.length(); i++) {
        key = a * i + b;
        outgoing_data.append(Cycle(outgoing_data, i, key, ind));
    }
    return outgoing_data;
}

QString TRITHEMIUS::Cryption(int a, int b, int c, int ind) {

    int key;
    QString outgoing_data;

    for (int i = 0; i < data.length(); i++) {
        key = a * i * i + b * i + c;

        outgoing_data.append(Cycle(outgoing_data, i, key, ind));
    }
    return outgoing_data;
}

QString TRITHEMIUS::Cryption(QString slogan_key, int ind) {

    int key;
    QString outgoing_data;

    for (int i = 0, s = 0; i < data.length() && s < slogan_key.length(); i++, s++) {
        for (int c; c < alphabet.length(); c++) {
            if (alphabet.at(c) == slogan_key.at(s)) {
                key = c;
                break;
            }
            if (c == alphabet.length()) {
                key = 0;
            }
        }
        outgoing_data.append(Cycle(outgoing_data, i, key, ind));
        if (s == slogan_key.length() - 1) {
            s = 0;
        }
    }
    return outgoing_data;
}

QString TRITHEMIUS::Cycle(QString outgoing_data, int i, int key, int ind) {

    for (int j = 0; j < alphabet.length(); j++) {
        if (data.at(i) == alphabet.at(j)) {
            if (ind == 1)
                return alphabet.at(mod((j + key), alphabet.length()));

            else {

                return alphabet.at(mod(j + alphabet.length() - mod(key, alphabet.length()), alphabet.length()));
            }
        } else if (j == alphabet.length() - 1) {
            outgoing_data.append(data.at(i));
            return data.at(i);
        }
    }

}

