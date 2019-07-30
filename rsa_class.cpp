
#include"rsa_class.h"
#include<cryptopp/base64.h>

#include<cryptopp/files.h>

RSA_CLASS::RSA_CLASS() {
    params.GenerateRandomWithKeySize(rng, 1024);
}

//Create Keys
std::vector <QString> RSA_CLASS::CreateKeys() {
    params.GenerateRandomWithKeySize(rng, 1024);
    CryptoPP::RSA::PrivateKey privateKey(params);
    CryptoPP::RSA::PublicKey publicKey(privateKey);

    std::string tempPrivateKey;
    CryptoPP::StringSink output1(tempPrivateKey);
    privateKey.DEREncode(output1);
    SaveKey("privateKey.txt", privateKey);

    std::string tempPublicKey;
    CryptoPP::StringSink output2(tempPublicKey);
    publicKey.Save(output2);
    SaveKey("publicKey.txt", publicKey);


    std::vector <QString> keys;
    keys.push_back(QString::fromStdString(tempPublicKey));
    keys.push_back(QString::fromStdString(tempPrivateKey));
    return keys;

}


QString RSA_CLASS::Cryption(int ind, QString data) {

    QString outgoing_data;

    //Encrypt
    if (ind == 1) {
        std::string cipher;

        CryptoPP::RSA::PublicKey publicKey;
        LoadKey("test.txt", publicKey);

        CryptoPP::RSAES_OAEP_SHA_Encryptor enc(publicKey);
        CryptoPP::StringSource ss1(data.toStdString(), true,
                                   new CryptoPP::PK_EncryptorFilter(rng, enc,
                                                                    new CryptoPP::StringSink(cipher)
                                   )
        );

        StringSource sink(cipher, true);
        Save("Cipher.txt", sink);

        outgoing_data.clear();
        outgoing_data.append(QString::fromStdString(cipher));

    }
        //Decrypt
    else {

        CryptoPP::RSA::PrivateKey privateKey;
        LoadKey("test2.txt", privateKey);

        std::string cipher;
        StringSink sink(cipher);
        Load("Cipher.txt", sink);

        std::string recovered;
        CryptoPP::RSAES_OAEP_SHA_Decryptor dec(privateKey);
        CryptoPP::StringSource ss2(cipher, true,
                                   new CryptoPP::PK_DecryptorFilter(rng, dec,
                                                                    new CryptoPP::StringSink(recovered)
                                   )
        );

        outgoing_data.clear();
        outgoing_data.append(QString::fromStdString(recovered));

    }
    return outgoing_data;
}

void RSA_CLASS::SaveKey(const std::string &filename, const CryptoPP::RSA::PublicKey &key) {
    ByteQueue queue;
    key.Save(queue);

    Save(filename, queue);
}

void RSA_CLASS::Save(const std::string &filename, const BufferedTransformation &bt) {
    CryptoPP::FileSink file(filename.c_str());
    bt.CopyTo(file);
    file.MessageEnd();
}

void RSA_CLASS::LoadKey(const std::string &filename, CryptoPP::RSA::PublicKey &key) {
    ByteQueue queue;
    Load(filename, queue);

    key.Load(queue);
}

void RSA_CLASS::Load(const std::string &filename, BufferedTransformation &bt) {
    CryptoPP::FileSource file(filename.c_str(), true /*pumpAll*/);

    file.TransferTo(bt);
    bt.MessageEnd();
}

