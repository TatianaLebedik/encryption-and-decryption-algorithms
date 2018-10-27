#ifndef CAESAR_H
#define CAESAR_H
#include "data.h"


class CAESAR: public DATA
{
protected:

    int mod(int x, int y);

public:
    CAESAR();
    CAESAR(QString data);
    CAESAR(QString data, int language);

    QString Cryption(int key, bool ind);

};

#endif // CAESAR_H
