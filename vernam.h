#ifndef VERNAM_H
#define VERNAM_H

#include "trithemius.h"

class VERNAM : TRITHEMIUS {
public:

    VERNAM();

    VERNAM(QString data, int language);

    QString Cryption(int ind, int seed);
};

#endif // VERNAM_H
