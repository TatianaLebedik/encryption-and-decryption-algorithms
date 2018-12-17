
#include"rsa_class.h"
#include<cryptopp/base64.h>

#include<cryptopp/files.h>
RSA_CLASS::RSA_CLASS(){}


std::vector<QString> RSA_CLASS::CreateKeys()
{


    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 2048);

    CryptoPP::RSA::PrivateKey privateKey(params);
    CryptoPP::RSA::PublicKey publicKey(params);

    qDebug() << "Private Key:" << endl;

    std::string tempPrivateKey;
    CryptoPP::StringSink output1(tempPrivateKey);
    privateKey.DEREncode(output1);
    SavePublicKey("test2.txt", privateKey);
    qDebug() << QString::fromStdString(tempPrivateKey)<< endl;

    qDebug() << "Public Key:" << endl;
    std::string tempPublicKey;
    std::string tempPubKey;
    CryptoPP::StringSink output2(tempPublicKey);
    publicKey.Save(output2);
    SavePublicKey("test.txt", publicKey);
    qDebug() << QString::fromStdString(tempPublicKey) << endl;

    std::vector<QString> keys;
    keys.push_back(QString::fromStdString(tempPublicKey));
    keys.push_back(QString::fromStdString(tempPrivateKey));
    return keys;
}


QString RSA_CLASS::Cryption(int ind, QString KeyFromUi, QString data){

     qDebug() << "KeyFromUi:" << KeyFromUi << endl;
    QString outgoing_data = ":|";
    CryptoPP::AutoSeededRandomPool rng;


    if(ind == 1){
       std::string cipher;

       CryptoPP::RSA::PublicKey publicKey;
       LoadPublicKey("test.txt", publicKey);

       CryptoPP::RSAES_OAEP_SHA_Encryptor enc(publicKey);
       CryptoPP::StringSource ss1(data.toStdString(), true,
           new CryptoPP::PK_EncryptorFilter(rng, enc,
               new CryptoPP::StringSink(cipher)
          ) // PK_EncryptorFilter
       ); // StringSource

       StringSource sink (cipher, true);
       Save("Cipher.txt", sink);

       qDebug() << "Plain:" << endl;
       qDebug() << data << endl;

      qDebug() << "Cipher:" << endl;
      qDebug() << QString::fromStdString(cipher) << endl;

      outgoing_data.clear();
      outgoing_data.append(QString::fromStdString(cipher));



    }
    else{
        std::string cipher;
        StringSink sink (cipher);
        Load("Cipher.txt", sink);

        CryptoPP::RSA::PrivateKey privateKey;
        LoadPublicKey("test2.txt", privateKey);

        qDebug() << "Private key validation:" << privateKey.Validate(rng, 3);

        std::string recovered;
        CryptoPP::RSAES_OAEP_SHA_Decryptor dec(privateKey);
                CryptoPP::StringSource ss2(cipher, true, //data.toStdString()
                    new CryptoPP::PK_DecryptorFilter(rng, dec,
                        new CryptoPP::StringSink(recovered)
                   ) // PK_DecryptorFilter
                ); // StringSource


      /*
        CryptoPP::RSAES_OAEP_SHA_Decryptor dec(privateKey);
      CryptoPP::StringSource ss2(data.toStdString(), true,
          new CryptoPP::PK_DecryptorFilter(rng, dec,
              new CryptoPP::StringSink(recovered)
         ) // PK_DecryptorFilter
      ); // StringSource
      */
      qDebug() << "Recovered:" << endl;
      qDebug() << QString::fromStdString(recovered) << endl;

      std::string s;
      //CryptoPP::HexEncoder hex(new CryptoPP::StringSink(s));

    //  outgoing_data.clear();
    //  outgoing_data.append(QString::fromStdString(recovered));

    }
    return outgoing_data;
}

void RSA_CLASS::SavePublicKey(const std::string& filename, const CryptoPP::RSA::PublicKey& key)
{
    ByteQueue queue;
    key.Save(queue);

    Save(filename, queue);
}

void RSA_CLASS::Save(const std::string& filename, const BufferedTransformation& bt)
{
    CryptoPP::FileSink file(filename.c_str());
    bt.CopyTo(file);
    file.MessageEnd();
}


void RSA_CLASS::LoadPublicKey(const std::string& filename, CryptoPP::RSA::PublicKey& key)
{
    ByteQueue queue;
    Load(filename, queue);

    key.Load(queue);
}

void RSA_CLASS::Load(const std::string& filename, BufferedTransformation& bt)
{
    CryptoPP::FileSource file(filename.c_str(), true /*pumpAll*/);

    file.TransferTo(bt);
    bt.MessageEnd();
}

