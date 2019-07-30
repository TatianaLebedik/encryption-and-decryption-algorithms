#ifndef TRITHEMIUS_H
#define TRITHEMIUS_H

#include "caesar.h"

class TRITHEMIUS : public CAESAR {
protected:
    QString Cycle(QString outgoing_data, int i, int key, int encr_or_decr_ind);

public:
    TRITHEMIUS();

    TRITHEMIUS(QString data, int language);

    QString Cryption(int a, int b, int ind);

    QString Cryption(int a, int b, int c, int ind);

    QString Cryption(QString slogan_key, int ind);
};

#endif // TRITHEMIUS_H
