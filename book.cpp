#include "book.h"
#include "QVector"
#include "QDebug"
struct RAND_LETTTER {
    int column;
    int raw;
};

BOOK::BOOK(): DATA(){}

BOOK::BOOK(QString data): DATA(data){}

QString BOOK::Cryption(int ind, QString key){
    QString outgoing_data;

    QVector < QVector<QChar> > poem_key;
    QVector <QChar> temp_vector;
    int key_raw = 0;
    for(int i = 0; i < key.length(); i++){
       if(key[i].toLatin1() != '\n'){
            temp_vector.push_back(key[i]);
       }
       else{
           poem_key.push_back(temp_vector);
           temp_vector.clear();
           key_raw++;
        }
       if(i == key.length() - 1){
           poem_key.push_back(temp_vector);
       }
    }

    if(ind == 1){

        RAND_LETTTER rand_letter [data.length()];
        int rand_counter;
        for (int i = 0; i < data.length(); i++){
                rand_counter = 0;
                for(int j = 0; j < poem_key.size(); j++){
                    for(int k = 0; k < poem_key[j].size(); k++){
                        if(data[i] == poem_key[j][k]){
                            rand_letter[rand_counter].raw = j;
                            rand_letter[rand_counter].column = k;
                            rand_counter++;
                        }

                    }
                 }
                   if(rand_counter != 0){
                       int temp = rand() % rand_counter;
                       outgoing_data.push_back(QString::number((rand_letter[temp].raw)));
                       outgoing_data.push_back("/");
                       outgoing_data.push_back(QString::number(rand_letter[temp].column));
                       outgoing_data.push_back(",");
                   }
                   else{
                       outgoing_data.push_back("0");
                       outgoing_data.push_back("/");
                       outgoing_data.push_back("0");
                       outgoing_data.push_back(",");
                   }
        }
    }
    else{
        int a,b;
        int counter = 0;
        for(int i = 0; i < data.count('/'); i++){
            a = getNumber(counter);
            b = getNumber(counter);
            outgoing_data.push_back(poem_key[a][b]);
        }

    }
    return outgoing_data;
}

int BOOK::getNumber(int &counter){
    QString temp;
    while(data[counter].toLatin1() != '/' && data[counter].toLatin1() != ','){
        temp.push_back(data[counter]);
        counter++;
    }
    counter++;
    return temp.toInt();
}
