#ifndef BOOK_H
#define BOOK_H

#include "data.h"

class BOOK : public DATA {
    int getNumber(int &counter);

public:
    BOOK();

    BOOK(QString data);

    QString Cryption(int ind, QString key);
};

#endif // BOOK_H
