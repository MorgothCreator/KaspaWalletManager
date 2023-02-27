#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QDebug>

#include "signatures.h"
#include "base58Encoding.h"
//#include "ecc.h"
#include "globakaspa.h"
#include "bip32.h"
#include "global.h"
#include "util/bech32.h"

QString signatures::getAccountIdFromPrivateKey(QString privKey) {
    QByteArray prKey = signatures::decodePrivateKey(privKey);
    BIP32_xkey_t key;
    BIP32_NewMaster((uint8_t *)prKey.data(), prKey.length(), (BIP32_XKEY_NET)BIP32_XKEY_NET_PREFIX(), &key);
    bech32::data pk(std::begin(key.privateKey), std::end(key.privateKey));
    return QString::fromStdString(bech32::Encode(ADDRESSPREFIX(), pk, 0));
}

QString signatures::getAccountIdFromPrivateKey(QByteArray privKey) {
  BIP32_xkey_t key;
  BIP32_xkey_t pubKey;
    BIP32_NewMaster((uint8_t *)privKey.data(), privKey.length(), (BIP32_XKEY_NET)BIP32_XKEY_NET_PREFIX(), &key);
    BIP32_derive_public_child(&key, &pubKey, 0);
    bech32::data pk(std::begin(pubKey.privateKey), std::end(pubKey.privateKey));
    return QString::fromStdString(bech32::Encode(ADDRESSPREFIX(), pk, 0));
}

signatures::generatedAccount signatures::generateAccount(QByteArray key) {
    signatures::generatedAccount acc;
    acc.accountId = getAccountIdFromPrivateKey(key);
    acc.privateKey = signatures::encodePrivateKey(key);
    return acc;
}

signatures::generatedAccount signatures::generateAccount() {
    quint32 array[4];
    QRandomGenerator::global()->fillRange(array);
    QByteArray key;
    for(quint32 tmp: array) {
        key.append((tmp >> 24) & 0xFF);
        key.append((tmp >> 16) & 0xFF);
        key.append((tmp >> 8) & 0xFF);
        key.append(tmp & 0xFF);
    }
    return generateAccount(key);
}

bool signatures::validateAccountId(QString id) {
    bech32::decoded dec = bech32::Decode(id.toStdString());
    QString index = QString::fromStdString(ADDRESSPREFIX());
    if(dec.second.empty() || id.mid(0, index.length()).compare(index))
        return false;
    else
        return true;
}

bool signatures::validatePublicKey(QString pubKey) {
    return signatures::decodePublicKey(pubKey) != nullptr;
}

bool signatures::validatePrivateKey(QString privKey) {
    return signatures::decodePrivateKey(privKey) != nullptr;
}

bool signatures::verifyAccountSignature(QString message, QString accountId, QString signature) {
    return verifySignature(message, accountId, signature);
}

bool signatures::verifySignature(QString message, QString accountId, QString signature) {
    /*QByteArray signatureBytes = base58Encoding::decode(signature);
    QByteArray publicKeyBytes = signatures::decodeAccountId(accountId);
    EccPoint pubKey;
    EccPoint sig;
    int cnt = 0;
    for(; cnt < 32; cnt++) {
        pubKey.x[cnt] = publicKeyBytes[cnt];
        pubKey.y[cnt] = publicKeyBytes[cnt + 32];
        sig.x[cnt] = signatureBytes[cnt];
        sig.y[cnt] = signatureBytes[cnt + 32];
    }
    QCryptographicHash sha256 (QCryptographicHash::Sha256);
    sha256.reset();
    sha256.addData(message.toUtf8(), message.length());
    QByteArray hash = sha256 .result();
    return ecc::ecdsa_verify(&pubKey, (uint8_t *)hash.data(), sig.x, sig.y);*/
}

QString signatures::getSignature(QString privateKey, QString message) {
    /*QByteArray privateKeyBytes = signatures::decodePrivateKey(privateKey);
    uint8_t pKey[NUM_ECC_DIGITS];
    int cnt = 0;
    for(; cnt < 32; cnt++)
        pKey[cnt] = privateKeyBytes[cnt];
    QCryptographicHash sha256 (QCryptographicHash::Sha256);
    sha256.reset();
    sha256.addData(message.toUtf8(), message.length());
    QByteArray hash = sha256.result();
    uint8_t sig[NUM_ECC_DIGITS * 2];
    ecc::ecdsa_sign(pKey, (uint8_t *)hash.data(), sig);
    return base58Encoding::encode(QByteArray((char *)sig, 64));*/
}

QByteArray signatures::getCheckSum(QByteArray data) {
    QCryptographicHash sha256 (QCryptographicHash::Sha256);
    sha256.reset();
    sha256.addData(data);
    QByteArray hash1 = sha256.result();
    sha256.reset();
    sha256 .addData(hash1);
    QByteArray hash2 = sha256.result();
    QByteArray ret;
    for(int cnt = 0; cnt < KASPA_CHECKSUM_SIZE_IN_BYTES; cnt ++) {
        ret.append(hash2.at(cnt));
    }
    return ret;
}

QByteArray signatures::verifyAndRemoveCheckSum(QByteArray data) {
    if(data.count() < KASPA_CHECKSUM_SIZE_IN_BYTES)
        return QByteArray();
    QByteArray tmpData;
    for (int cnt = 0; cnt < data.count() - KASPA_CHECKSUM_SIZE_IN_BYTES; cnt++) {
        tmpData.append(data.at(cnt));
    }
    QByteArray checkSumCalc = getCheckSum(tmpData);
    QByteArray checkSumData;
    for (int cnt = data.count() - KASPA_CHECKSUM_SIZE_IN_BYTES; cnt < data.count(); cnt++) {
        checkSumData.append(data.at(cnt));
    }
    if(!checkSumCalc.compare(checkSumData))
        return tmpData;
    else
        return nullptr;
}

QByteArray signatures::addCheckSum(QByteArray data) {
    QByteArray tmpData;
    for (int cnt = 0; cnt < data.count(); cnt++) {
        tmpData.append(data.at(cnt));
    }
    QByteArray checkSum = getCheckSum(tmpData);
    return data + checkSum;
}

QString signatures::encodeWithCheckSum(QByteArray data) {
    QByteArray tmpData;
    for (int cnt = 0; cnt < data.count(); cnt++) {
        tmpData.append(data.at(cnt));
    }
    QByteArray checkSum = getCheckSum(tmpData);
    return base58Encoding::encode(data + checkSum);
}

QString signatures::encodePrivateKey(QByteArray privKey) {
    return encodeWithCheckSum(privKey);
}

QString signatures::encodePublicKey(QByteArray pubKey) {
    return encodeWithCheckSum(pubKey);
}

QString signatures::encodeAccountId(QByteArray pubKey) {
    bech32::data pk(std::begin(pubKey), std::end(pubKey));
    return QString::fromStdString(bech32::Encode(ADDRESSPREFIX(), pk, 0));
}

QByteArray signatures::decodeWithCheckSum(QString data) {
    QByteArray dat = base58Encoding::decode(data);
    return verifyAndRemoveCheckSum(dat);
}

QByteArray signatures::decodePrivateKey(QString privKey) {
    return decodeWithCheckSum(privKey);
}

QByteArray signatures::decodePublicKey(QString pubKey) {
    return decodeWithCheckSum(pubKey);
}

QByteArray signatures::decodeAccountId(QString accountId) {
    return decodeWithCheckSum(accountId/*QStringRef(&accountId, 1, accountId.length() - 1).toString()*/);
}



