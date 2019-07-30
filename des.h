#ifndef DES_H
#define DES_H

#include <cryptopp/des.h>
#include <QString>
#include <cryptopp/modes.h>
#include "data.h"

class DES : public DATA {
public:
    DES();

    DES(QString data);

    QString Cryption(int ind, QString key);
};

#endif // DES_H
