#ifndef RSA_CLASS_H
#define RSA_CLASS_H

#include"mainwindow.h"
#include <cryptopp/rsa.h>
#include<cryptopp/randpool.h>
#include<sstream>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>
#include <cryptopp/sha.h>
using CryptoPP::Integer;
using CryptoPP::ByteQueue;

#include <cryptopp/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::BufferedTransformation;

#include <cryptopp/cryptlib.h>
using CryptoPP::Exception;

#include <cryptopp/hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include<QString>
#include<QDebug>
#include<vector>

class RSA_CLASS
{
private:


    //CryptoPP::AutoSeededRandomPool rng;
public:
    RSA_CLASS();
    std::vector<QString> CreateKeys();
    QString Cryption(int ind, QString KeyFromUi, QString data);
    void LoadPublicKey(const std::string& filename, CryptoPP::RSA::PublicKey& key);
    void SavePublicKey(const std::string& filename, const CryptoPP::RSA::PublicKey& key);
    void Save(const std::string& filename, const BufferedTransformation& bt);
    void Load(const std::string& filename, BufferedTransformation& bt);
};


#endif // RSA_CLASS_H
