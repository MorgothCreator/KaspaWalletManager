#ifndef WALLETRPC_H
#define WALLETRPC_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include "storage/storageinternal.h"

#include "api/grpc/grpc.h"


class WalletGRpc : public QObject  {
    Q_OBJECT
private:
    QThread *grpcWorkerThread = NULL;
    gRPC *grpcWorker = NULL;
    bool connected;
public:
    WalletGRpc(std::string url = "");
    ~WalletGRpc();
    void rpcConnect();

    void getBalanceByAddress(const std::string& s) { emit GetBalanceByAddress(s); }
    void getBalanceByAddresses(std::vector<std::string> s) { emit GetBalanceByAddresses(s); }
    void getBlockCount() { emit GetBlockCount(); }
    void getBlockDagInfo() { emit GetBlockDagInfo(); }
    void getCoinSupply() { emit GetCoinSupply(); }
    void getUtxosByAddresses(std::vector<std::string> v) { emit GetUtxosByAddresses(v); }

    void getBalanceByAddressComplete(const uint64_t i) { emit GetBalanceByAddressComplete(i); }
    void getBalanceByAddressesComplete(const uint64_t i) { emit GetBalanceByAddressesComplete(i); }
    void getBlockCountComplete(const gRPC::getBlockCount_t t) { emit GetBlockCountComplete(t); }
    void getBlockDagInfoComplete(const gRPC::blockDagInfo_t t) { emit GetBlockDagInfoComplete(t); }
    void getCoinSupplyComplete(const gRPC::coinSupply_t t) { emit GetCoinSupplyComplete(t); }
    void getUtxosByAddressesComplete(const std::vector<gRPC::getUtxosByAddressesEntry_t> v) { emit GetUtxosByAddressesComplete(v); }

    void getBalanceByAddressError(const std::string s) { emit GetBalanceByAddressError(s); }
    void getBalanceByAddressesError(const std::string s) { emit GetBalanceByAddressesError(s); }
    void getBlockCountError(const std::string s) { emit GetBlockCountError(s); }
    void getBlockDagInfoError(const std::string s) { emit GetBlockDagInfoError(s); }
    void getCoinSupplyError(const std::string s) { emit GetCoinSupplyError(s); }
    void getUtxosByAddressesError(const std::string s) { emit GetUtxosByAddressesError(s); }
signals:
    void GetBalanceByAddress(const std::string& addr);
    void GetBalanceByAddresses(std::vector<std::string> addrs);
    void GetBlockCount();
    void GetBlockDagInfo();
    void GetCoinSupply();
    void GetUtxosByAddresses(std::vector<std::string> addrs);
signals:
    void GetBalanceByAddressComplete(const uint64_t);
    void GetBalanceByAddressesComplete(const uint64_t);
    void GetBlockCountComplete(const gRPC::getBlockCount_t);
    void GetBlockDagInfoComplete(const gRPC::blockDagInfo_t);
    void GetCoinSupplyComplete(const gRPC::coinSupply_t);
    void GetUtxosByAddressesComplete(const std::vector<gRPC::getUtxosByAddressesEntry_t>);

    void GetBalanceByAddressError(const std::string);
    void GetBalanceByAddressesError(const std::string);
    void GetBlockCountError(const std::string);
    void GetBlockDagInfoError(const std::string);
    void GetCoinSupplyError(const std::string);
    void GetUtxosByAddressesError(const std::string);

};

#endif // WALLETRPC_H
