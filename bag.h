
#ifndef BAG_H
#define BAG_H
#include "QString"
#include "vector"
#include "QDebug"
#include "caesar.h"

class BAG: public CAESAR
{
private:
    std::vector<int> private_key;
    int q;
    int r;
    int mult_rev_r;
public:
    BAG();
    BAG(QString data);
    QString Cryption(int ind, QString intut_public_key, QString input_data);
    QString Create_Key_Pair(QString input_private_key, int input_q, int input_r, int input_mult_rev_r);
};

#endif // BAG_H
