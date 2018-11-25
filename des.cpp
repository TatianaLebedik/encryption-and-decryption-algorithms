#include "des.h"
#include "qdebug.h"
#include <cryptopp/modes.h>
using CryptoPP::CBC_Mode;
#include <cryptopp/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include <cryptopp/cryptlib.h>
using CryptoPP::Exception;

#include <cryptopp/hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include <cryptopp/secblock.h>

#include <assert.h>
DES::DES(): DATA(){}

#include<cryptopp/aes.h>

DES::DES(QString data): DATA(data){}

QString DES::Cryption(int ind, QString input_key){
    QString outgoing_data;
    std::string output_text;

    byte key[CryptoPP::DES::MAX_KEYLENGTH];
       byte* k = (byte*) input_key.toStdString().c_str();

       for (int i = 0; i < CryptoPP::DES::MAX_KEYLENGTH; i++)
           if (i<sizeof (k))
               key[i] = k[i];
           else
               key[i] = 0;
           byte iv[ CryptoPP::DES::BLOCKSIZE ];
           for (int i = 0; i < CryptoPP::DES::BLOCKSIZE; i++)
                   iv[i] = 0;

if(ind == 1){

    std::string ciphertextEncode,ciphertext;
    CryptoPP::DES::Encryption desEncryption(key, CryptoPP::DES::MAX_KEYLENGTH);
       CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(desEncryption, iv);

       CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
       stfEncryptor.Put(reinterpret_cast<const unsigned char*> (data.toStdString().c_str()), data.toStdString().length() + 1);
       stfEncryptor.MessageEnd();
      // qDebug() << "\nencrypted text: " << QString::fromStdString(ciphertext);
       StringSource ss(ciphertext, true, new HexEncoder(new StringSink(ciphertextEncode)));
       //qDebug() << "\nencoded encrypted text: " << QString::fromStdString(ciphertextEncode);
      // return ciphertextEncode;
       output_text = ciphertextEncode;

}else{

    std::string ciphertextDecode,decryptedtext;
    StringSource ss(data.toStdString(), true, new HexDecoder(new StringSink(ciphertextDecode)));
       // qDebug() << "\n cipher decoded: " << QString::fromStdString(ciphertextDecode);
        CryptoPP::DES::Decryption desDecryption(key, CryptoPP::DES::MAX_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(desDecryption, iv);

        CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
        stfDecryptor.Put(reinterpret_cast<const unsigned char*> (ciphertextDecode.c_str()), ciphertextDecode.size());
        stfDecryptor.MessageEnd();

        //qDebug() <<"\ndecrypted text: "<<QString::fromStdString(decryptedtext);

        output_text = decryptedtext;
}

    return outgoing_data = QString::fromStdString(output_text);;
}
