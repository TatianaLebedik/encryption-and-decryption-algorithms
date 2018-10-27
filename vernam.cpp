#include "vernam.h"
#include "ctime"
//#include "cmath"

VERNAM::VERNAM() : TRITHEMIUS(){}

VERNAM::VERNAM(QString data, int language) : TRITHEMIUS(data,language) {}

QString VERNAM::Cryption(int ind, int seed){

    srand(seed);
    int key;
    QString outgoing_data;
    QString line_key;
    for(int i = 0; i < data.length(); i++){
        line_key.push_back(alphabet.at(rand() % data.length()));
    }
    for (int i = 0, s = 0; i < data.length() && s < line_key.length(); i++,s++){
        for(int c; c < alphabet.length();c++){
            if(alphabet.at(c) == line_key.at(s)){
                key = c;
                break;
            }
            if(c==alphabet.length()){
                key = 0;
            }
        }
        outgoing_data.append(Cycle(outgoing_data,i,key,ind));
        if(s == line_key.length()-1){
            s = 0;
        }
    }
    return outgoing_data;
}
