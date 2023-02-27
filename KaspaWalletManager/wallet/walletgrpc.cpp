#include "walletgrpc.h"
#include "global.h"

#include <QDateTime>
//#include "wallet/history.h"
#include "api/grpc/grpc.h"

WalletGRpc::WalletGRpc(std::string url) {
    grpcWorker = new gRPC;
    connect(this, &WalletGRpc::GetBalanceByAddress, grpcWorker, &gRPC::GetBalanceByAddress);
    connect(this, &WalletGRpc::GetBalanceByAddresses, grpcWorker, &gRPC::GetBalanceByAddresses);
    connect(this, &WalletGRpc::GetBlockCount, grpcWorker, &gRPC::GetBlockCount);
    connect(this, &WalletGRpc::GetBlockDagInfo, grpcWorker, &gRPC::GetBlockDagInfo);
    connect(this, &WalletGRpc::GetCoinSupply, grpcWorker, &gRPC::GetCoinSupply);
    connect(this, &WalletGRpc::GetUtxosByAddresses, grpcWorker, &gRPC::GetUtxosByAddresses);

    connect(grpcWorker, &gRPC::GetBalanceByAddressComplete, this, &WalletGRpc::getBalanceByAddressComplete);
    connect(grpcWorker, &gRPC::GetBalanceByAddressesComplete, this, &WalletGRpc::getBalanceByAddressesComplete);
    connect(grpcWorker, &gRPC::GetBlockCountComplete, this, &WalletGRpc::getBlockCountComplete);
    connect(grpcWorker, &gRPC::GetBlockDagInfoComplete, this, &WalletGRpc::getBlockDagInfoComplete);
    connect(grpcWorker, &gRPC::GetCoinSupplyComplete, this, &WalletGRpc::getCoinSupplyComplete);
    connect(grpcWorker, &gRPC::GetUtxosByAddressesComplete, this, &WalletGRpc::getUtxosByAddressesComplete);

    connect(grpcWorker, &gRPC::GetBalanceByAddressError, this, &WalletGRpc::getBalanceByAddressError);
    connect(grpcWorker, &gRPC::GetBalanceByAddressesError, this, &WalletGRpc::getBalanceByAddressesError);
    connect(grpcWorker, &gRPC::GetBlockCountError, this, &WalletGRpc::getBlockCountError);
    connect(grpcWorker, &gRPC::GetBlockDagInfoError, this, &WalletGRpc::getBlockDagInfoError);
    connect(grpcWorker, &gRPC::GetCoinSupplyError, this, &WalletGRpc::getCoinSupplyError);
    connect(grpcWorker, &gRPC::GetUtxosByAddressesError, this, &WalletGRpc::getUtxosByAddressesError);

    grpcWorkerThread = new QThread;
    grpcWorker->moveToThread(grpcWorkerThread);
    grpcWorkerThread->start();
    grpcWorker->openChannel(url);
}

WalletGRpc::~WalletGRpc() {
    grpcWorkerThread->quit();
    grpcWorkerThread->wait();
    delete grpcWorkerThread;
}

void WalletGRpc::rpcConnect() {
    /*getCoinSupply();
    getBlockCount();
    getBlockDagInfo();
    getBalanceByAddress("kaspa:ppcmdskxqj5gxzs5sjayd85ytsmmkzhn9uzyhj8apjyjezrcgx0g2eqmuky95");
    GetUtxosByAddresses(std::vector<std::string>({"kaspa:ppcmdskxqj5gxzs5sjayd85ytsmmkzhn9uzyhj8apjyjezrcgx0g2eqmuky95"}));*/
}

