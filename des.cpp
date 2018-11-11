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

 //  if(input_key.length() > data.length()){
  // input_key.resize(data.length() + 1);
  // }

    // byte* key_s = (byte*)"essasenhaehfraca";
    //CryptoPP::SecByteBlock key ( key_s, CryptoPP::DES::DEFAULT_KEYLENGTH );
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
       qDebug() << "\nencrypted text: " << QString::fromStdString(ciphertext);
       StringSource ss(ciphertext, true, new HexEncoder(new StringSink(ciphertextEncode)));
       qDebug() << "\nencoded encrypted text: " << QString::fromStdString(ciphertextEncode);
      // return ciphertextEncode;
       output_text = ciphertextEncode;

}else{

    std::string ciphertextDecode,decryptedtext;
    StringSource ss(data.toStdString(), true, new HexDecoder(new StringSink(ciphertextDecode)));
        qDebug() << "\n cipher decoded: " << QString::fromStdString(ciphertextDecode);
        CryptoPP::DES::Decryption desDecryption(key, CryptoPP::DES::MAX_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(desDecryption, iv);

        CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
        stfDecryptor.Put(reinterpret_cast<const unsigned char*> (ciphertextDecode.c_str()), ciphertextDecode.size());
        stfDecryptor.MessageEnd();

        qDebug() <<"\ndecrypted text: "<<QString::fromStdString(decryptedtext);

        output_text = decryptedtext;
}
/*
        CryptoPP::DES::Decryption desDecryption(key, CryptoPP::DES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( desDecryption, iv );


        CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( output_text ));
       // stfDecryptor.Put( reinterpret_cast<const unsigned char*>( data.toStdString().c_str() ), data.size() );
      //   qDebug() << data.length();
        size_t max_output_len = (data.length()) + 8 - ((data.length()) % 8);

        data.resize(max_output_len);
        //qDebug() << data.length();
        stfDecryptor.Put( reinterpret_cast<const unsigned char*>( data.toStdString().c_str() ), data.length() + 1 );

        stfDecryptor.MessageEnd();
}
*/

  //  byte* key_s = reinterpret_cast<byte*>(input_key.toUtf8().data());;
   // CryptoPP::SecByteBlock key ( key_s, CryptoPP::DES::DEFAULT_KEYLENGTH );
     //      byte iv[ CryptoPP::DES::BLOCKSIZE ];
/*
    byte* key_s = reinterpret_cast<byte*>(input_key.toUtf8().data());;
    CryptoPP::SecByteBlock key ( key_s, CryptoPP::AES::DEFAULT_KEYLENGTH );
           byte iv[ CryptoPP::AES::BLOCKSIZE ];
*/
    //key = key_ba;
    //memset( key, 0x00, CryptoPP::DES::DEFAULT_KEYLENGTH );
    //memset( iv, 0x00, CryptoPP::DES::BLOCKSIZE );

    /*********************************\
    \*********************************/
/*
if(ind  == 1){
/*
        CryptoPP::DES::Encryption desEncryption(key, key.size());
        CryptoPP::CBC_Mode_ExternalCipher::Encryption e( desEncryption, iv );
       // CBC_Mode< DES >::Encryption e;
       // e.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter adds padding
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.

        size_t max_output_len = data.toUtf8().toBase64().length() + 16 - (data.toUtf8().toBase64().length() % 16);

        data.resize(max_output_len);
        StringSource ss( data.toUtf8().toBase64().toStdString(), true,
            new StreamTransformationFilter( e,
                new StringSink( output_text )
            ) // StreamTransformationFilter
        ); // StringSource
*/
/*
        CBC_Mode< CryptoPP::AES >::Encryption enc( key, key.size(), iv);

        size_t max_output_len = data.toUtf8().toBase64().length() + 16 - (data.toUtf8().toBase64().length() % 16);

        data.resize(max_output_len);

        // Encryption
        CryptoPP::StringSource ss( data.toUtf8().toBase64(), true,
           new CryptoPP::StreamTransformationFilter( enc,
              new CryptoPP::StringSink( output_text )
           ) // StreamTransformationFilter
        ); // StringSource

}
else
{

    /*********************************\
    \*********************************/
/*
    // Pretty print cipher text
  //  StringSource ss( output_text , true,
   //     new HexEncoder(
    //        new StringSink( output_text )
     //   ) // HexEncoder
    //); // StringSource

    /*********************************\
    \*********************************/

  /*  CryptoPP::DES::Decryption desDecryption(key, key.size());
    CryptoPP::CBC_Mode_ExternalCipher::Decryption d (desDecryption, iv );

        //CBC_Mode< DES >::Decryption d;
        //d.SetKeyWithIV( key, key.size(), iv );

        // The StreamTransformationFilter removes
        //  padding as required.
        StringSource ss( data.toStdString(), true,
                         new StreamTransformationFilter( d,
                new StringSink( output_text )
            ) // StreamTransformationFilter
        ); // StringSource

        size_t max_output_len = data.toUtf8().toBase64().length() + 16 - (data.toUtf8().toBase64().length() % 16);

        data.resize(max_output_len);

        CryptoPP::StringSource ss1(data.toUtf8().toBase64().toStdString(), true,
            new CryptoPP::HexDecoder(
                new CryptoPP::StreamTransformationFilter( d,
                    new CryptoPP::StringSink( output_text )  ) ) );

*/
/*
    CBC_Mode< CryptoPP::AES >::Decryption dec( key, key.size(), iv);


    //size_t max_output_len = data.toUtf8().toBase64().length() + 16 - (data.toUtf8().toBase64().length() % 16);

    //data.resize(max_output_len);

    // Encryption
    CryptoPP::StringSource ss( data.toUtf8().toBase64(), true,
       new CryptoPP::StreamTransformationFilter( dec,
          new CryptoPP::StringSink( output_text ))
    ); // StringSource



}
*/
    return outgoing_data = QString::fromStdString(output_text);;
}
