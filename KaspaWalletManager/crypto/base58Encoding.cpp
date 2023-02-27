#include <string>
#include <QList>
//#include <QStringRef>
#include <QCryptographicHash>

#include "globakaspa.h"
#include "base58Encoding.h"

const char BASE58_ALPHABET[59] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

QList<int> BASE58_ALPHABET_MAP = QList<int>({

                                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                -1,  0,  1,  2,  3,  4,  5,  6,  7,  8, -1, -1, -1, -1, -1, -1,
                                                -1,  9, 10, 11, 12, 13, 14, 15, 16, -1, 17, 18, 19, 20, 21, -1,
                                                22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, -1, -1, -1, -1, -1,
                                                -1, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, -1, 44, 45, 46,
                                                47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                                            });

static const double iFactor = 1.36565823730976103695740418120764243208481439700722980119458355862779176747360903943915516885072037696111192757109;

QString base58Encoding::encode(QByteArray data) {
    QList<uint8_t> dat;
    foreach(char byte, data) {
        dat.append(byte);
    }
    QString result;
    int zeros = 0, length = 0, pbegin = 0, pend;
    if (!(pend = dat.count()))
        return 0;
    while (pbegin != pend && !(int)dat[pbegin])
        pbegin = ++zeros;
    int size = 1 + iFactor * (double)(pend - pbegin);
    unsigned char b58[size];
    for (int i = 0; i < size; i++)
        b58[i] = 0;
    while (pbegin != pend) {
        unsigned int carry = dat[pbegin];
        int i = 0;
        for (int it1 = size - 1; (carry || i < length) && (it1 != -1); it1--,i++) {
            carry += 256 * b58[it1];
            b58[it1] = carry % 58;
            carry /= 58;
        }
        if (carry)
            return 0;
        length = i;
        pbegin++;
    }
    int it2 = size - length;
    while ((it2-size) && !b58[it2])
        it2++;
    int ri = 0;
    while(ri < zeros) {
        result.append('1');
        ri++;
    }
    for (; it2 < size; ++it2) {
        result.append(BASE58_ALPHABET[b58[it2]]);
        ri++;
    }
    return result;
}

QByteArray base58Encoding::decode(QString str) {
    QList<uint8_t> result;
    result.append(0);
    int resultlen = 1;
    for (int i = 0; i < str.length(); i++) {
        int cn = str.data()[i].toLatin1();
        uint16_t carry = (uint8_t) BASE58_ALPHABET_MAP[cn];
        if (carry == (uint8_t)-1)  {
            return QByteArray();
        }
        for (int j = 0; j < resultlen; j++) {
            carry += (uint16_t)result[j] * 58;
            result[j] = (uint8_t) (carry & 0xff);
            carry = carry / 256;
        }
        while (carry > 0) {
            result.append(0);
            result[resultlen] = (carry & 0xff);
            resultlen++;
            carry = carry / 256;
        }
    }

    for (int i = 0; i < str.length() && str.at(i) == '1'; i++)
        result[resultlen++] = 0;

    for (int i = resultlen - 1, z = (resultlen >> 1) + (resultlen & 1);
        i >= z; i--) {
        uint8_t k = result[i];
        result[i] = result[resultlen - i - 1];
        result[resultlen - i - 1] = k;
    }
    QByteArray res;
    foreach(uint8_t byte, result) {
        res.append(byte);
    }
    return res;
}


