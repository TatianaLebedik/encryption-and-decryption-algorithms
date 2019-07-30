#include "caesar.h"

CAESAR::CAESAR() : DATA() {}

CAESAR::CAESAR(QString inp_data) : DATA(inp_data) {}

CAESAR::CAESAR(QString inp_data, int inp_language) : DATA(inp_data, inp_language) {}

QString CAESAR::Cryption(int key, bool ind) {

    QString outgoing_data;

    for (int i = 0; i < data.length(); i++) {
        for (int j = 0; j < alphabet.length(); j++) {
            if (data.at(i) == alphabet.at(j)) {
                if (ind == 1) {
                    outgoing_data.append(alphabet[mod((j + key), alphabet.length())]);
                } else {
                    outgoing_data.push_back(
                            alphabet[mod(j + alphabet.length() - mod(key, alphabet.length()), alphabet.length())]);
                }
                break;
            } else if (j == alphabet.length() - 1) {
                outgoing_data.append(data.at(i));
            }

        }
    }

    return outgoing_data;
}

int CAESAR::mod(int a, int b) {
    int r = a % b;
    return (r < 0 ? r + abs(b) : r);
}


