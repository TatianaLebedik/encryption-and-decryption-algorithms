#include "bag.h"

BAG::BAG() : CAESAR(){}

BAG::BAG(QString data) : CAESAR(data){}

QString BAG::Cryption(int ind, QString input_public_key_in_qstring, QString input_data){

    QString outgoing_data;
    data = input_data;
    QString temp_qstring;
    int temp_sum = 0;

    if(ind == 1){

        //convert QString public key into int
        std::vector<int> public_key;
        for(int i = 0; i < input_public_key_in_qstring.length(); i++){
                if(input_public_key_in_qstring[i] != ',' && input_public_key_in_qstring[i] != ';'){
                    temp_qstring.append(input_public_key_in_qstring[i]);
                }
                else{
                    public_key.push_back(temp_qstring.toInt());
                    temp_qstring.clear();
                }
        }


        if(public_key.size() != 8){
            QMessageBox::critical(0, "Critical", "Public key is wrong,\n please create right key pair!");
        }
        else{
            temp_qstring.clear();

            for(int i = 0; i < data.length(); i++){
                temp_qstring = QString::number( data.toLatin1()[ i ], 2 );
                 for(int k = 0; k < 8; k++){
                    if(temp_qstring.length() < 8){
                         temp_qstring.push_front('0');
                    }
                    else{
                        break;
                    }
                }

                 for(int j = 0; j < temp_qstring.length(); j++){
                     temp_sum += public_key[j]*((int)temp_qstring.at(j).toLatin1() == 48 ? 0 : 1);
                }

                outgoing_data.push_back(QString::number(temp_sum));

                if( i != data.length() - 1){
                    outgoing_data.push_back(",");
                }
                else{
                     outgoing_data.push_back(";");
                }
                temp_sum = 0;
                temp_qstring.clear();
            }
        }
    }
    else{

            temp_qstring.clear();
            QString temp_char_in_binary_code;
            for(int i = 0; i < data.length();i++){
                if(data.at(i) != ',' && data.at(i) != ';'){
                    temp_qstring.push_back(data.at(i));

                }
                else{
                    bool ok;
                    temp_sum = mod(temp_qstring.toInt()*mult_rev_r,q);
                    for(int j = 7; j >= 0; j--){
                        if(temp_sum >= private_key[j]){
                            temp_sum -= private_key[j];
                            temp_char_in_binary_code.push_front('1');
                        }
                        else{
                            temp_char_in_binary_code.push_front('0');
                        }
                    }
                    temp_qstring.clear();
                    outgoing_data.append(char(temp_char_in_binary_code.toInt(&ok, 2)));
                    temp_char_in_binary_code.clear();
                }
            }
        }

    return outgoing_data;
}

QString BAG::Create_Key_Pair(QString input_private_key, int input_q, int input_r, int input_mult_rev_r){

    private_key.clear();
    QString public_key;
    QString temp_qstring;
    q = input_q;
    r = input_r;
    mult_rev_r = input_mult_rev_r;

    for(int i = 0; i < input_private_key.size(); i++){

        if(input_private_key[i] != ',' && input_private_key[i] != ';'){
            temp_qstring.push_back(input_private_key[i]);
        }
        else{
            private_key.push_back(temp_qstring.toInt());
            temp_qstring.clear();
        }
    }

    bool ind = true;
    int temp_key_number_sum = 0;

    for(int i = 7; i!=0 ; i--){
        temp_key_number_sum = 0;
        for(int j = 0; j < i; j++)
          {
                 temp_key_number_sum+=private_key[j];
          }
        if(private_key[i] < temp_key_number_sum){
            ind = false;
        }

    }

          temp_key_number_sum = 0;
         for(int i = 0; i < private_key.size(); i++){
             temp_key_number_sum += private_key[i];

         }
         if(private_key.size() != 8 || temp_key_number_sum > q || r > q || r < 1 || !ind){
             QMessageBox::critical(0, "Critical", "Private key is wrong,\n please create right key pair!");
             public_key.clear();
         }
         else {



             for(int i = 0; i < private_key.size() - 1; i++){
                 public_key.append(QString::number(mod(r*private_key.at(i),q)));
                 public_key.append(",");
             }
                 public_key.append(QString::number(mod(r*private_key.at(private_key.size() - 1),q)));
                  public_key.append(";");


         }

    return public_key;
}

