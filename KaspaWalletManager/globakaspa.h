#ifndef GLOBAKASPA_H
#define GLOBAKASPA_H

#include <QString>
#include <QList>

typedef enum {
    NONE = -1,
    TESTNET = 0,
    MAINNET = 1,
    DEVNET = 2,
    SIMNET = 3
} networkName_e;

#define KASPA_CHECKSUM_SIZE_IN_BYTES             4
std::string ADDRESSPREFIX();
int BIP32_XKEY_NET_PREFIX();
#define KASPA_MAX_SUPPLY                         10_000_000_000
#define KASPA_DECIMALS                           8

#define RPC_CONNECTION_TIMEOUT_MS               20000

extern QList<QString> networkNameList;


extern QList<QString> profitingAccountTypesList;

/*class GlobalLyra {
    static double getAmount(long long amount) {

    };
};*/

#endif // GLOBAKASPA_H
