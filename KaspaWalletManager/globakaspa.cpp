#include <QString>
#include <QList>
#include "global.h"
#include "crypto/bip32.h"

QList<QString> networkNameList = QList<QString>({"TESTNET", "MAINNET"/*, "DEVNET"*/});


QList<QString> profitingAccountTypesList = QList<QString>({"NODE", "ORACLE", "MERCHANT", "YIELD"});

std::string ADDRESSPREFIX() {
    switch(Global::Network::getNetwork()) {
    case networkName_e::TESTNET: return "kaspatest";
    case networkName_e::MAINNET: return "kaspa";
    case networkName_e::DEVNET: return "kaspadev";
    case networkName_e::SIMNET: return "kaspasim";
    default: return "";
    }
}

int BIP32_XKEY_NET_PREFIX() {
    switch(Global::Network::getNetwork()) {
    case networkName_e::TESTNET: return BIP32_XKEY_NET_TESTNET;
    case networkName_e::MAINNET: return BIP32_XKEY_NET_MAINNET;
    case networkName_e::DEVNET: return BIP32_XKEY_NET_DEVNET;
    case networkName_e::SIMNET: return BIP32_XKEY_NET_SIMNET;
    default: return -1;
    }
}
