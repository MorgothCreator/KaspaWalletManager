#ifndef __GRPC_H__
#define __GRPC_H__

#include <string>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include "api/grpc/protos/macosx/messages.pb.h"
#include "api/grpc/protos/macosx/messages.grpc.pb.h"
#include "grpcpp/create_channel.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientBidiReactor;
using protowire::KaspadMessage;

class gRPC : public QObject {
    Q_OBJECT
private:
    QTimer timerCheckConn;
    std::shared_ptr<Channel> ch;
    std::unique_ptr<protowire::RPC::Stub> stub_;
public:
    typedef struct {
        uint64_t blockCount;
        uint64_t headerCount;
    }getBlockCount_t;

    typedef struct {
        std::string networkName;
        uint64_t blockCount;
        uint64_t headerCount;
        std::vector<std::string> tipHashes;
        double dificulty;
        uint64_t pastMedianTime;
        std::vector<std::string> virtualParentHashes;
        std::string pruningPointHash;
        uint64_t virtualDaaScore;
    }blockDagInfo_t;

    typedef struct {
        uint64_t circSupply;
        uint64_t maxSupply;
    }coinSupply_t;

    typedef struct {
        std::string address;
        std::string outpointTransactionId;
        uint32_t outpointIndex;
        uint64_t utxoEntryAmount;
        uint32_t scriptPublicKeyUtxoEntryVersion;
        std::string scriptPublicKeyUtxoEntryScriptPublicKey;
        uint64_t utxoEntryBlockDaaScore;
        bool utxoEntryIsCoinbase;
    }getUtxosByAddressesEntry_t;

    explicit gRPC() { };
    ~gRPC() { }
    void openChannel(std::string url);
    void addMetadata(ClientContext *context) {
        Q_UNUSED(context);
        //context->AddMetadata("method", "data");
    }
    void setTimeout(ClientContext *context, long timeout = 1000) {
        std::chrono::time_point deadline = std::chrono::system_clock::now() +
                std::chrono::milliseconds(timeout);
        context->set_deadline(deadline);
    }

public slots:
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

#endif // GRPC_H
