#include "grpc.h"

#include "global.h"

void gRPC::openChannel(std::string url) {
    std::string Url = Global::Network::getNodeAddress().second.toStdString();
    if(url != "")
        Url = url;
#if GRPC_DEBUG
    qDebug() << "gRPC Try to connect to: " << Url.c_str();
#endif
    ch = grpc::CreateChannel(Url, grpc::InsecureChannelCredentials());
    stub_ = protowire::RPC::NewStub(ch);
    connect(&timerCheckConn, &QTimer::timeout, this, [=]{
        grpc_connectivity_state state = ch->GetState(true);
        /*if(state != grpc_connectivity_state::GRPC_CHANNEL_READY) {
            qDebug() << "gRPC disconnected detected";
        }*/
        Global::Network::setOnline(state == grpc_connectivity_state::GRPC_CHANNEL_READY);
    });
    timerCheckConn.start(250);
}

void gRPC::GetBalanceByAddress(const std::string& addr) {
    ClientContext context;
    setTimeout(&context);
    addMetadata(&context);
    //context.set_wait_for_ready(true);
    std::unique_ptr<grpc::ClientReaderWriter<protowire::KaspadMessage, protowire::KaspadMessage> > readerWritter(
                stub_->MessageStream(&context));
    // Data we are sending to the server.
    auto *req = new protowire::GetBalanceByAddressRequestMessage;
    auto *rsp = new protowire::GetBalanceByAddressResponseMessage;
    req->set_address(addr);
    KaspadMessage request, reply;
    request.set_allocated_getbalancebyaddressrequest(req);
    reply.set_allocated_getbalancebyaddressresponse(rsp);
    // Container for the data we expect from the server.
    readerWritter->Write(request);
    readerWritter->Read(&reply);
    readerWritter->WritesDone();
    grpc::Status status = readerWritter->Finish();
    if (status.ok()) {
        const auto rep = reply.getbalancebyaddressresponse();
#if GRPC_DEBUG
        qDebug() << "----START----";
        qDebug() << "gRPC GetBalanceByAddress: " << Global::Util::normaliseNumber((double)(rep.balance() / 100000000.0)) << "$KAS";
        qDebug() << "----END----";
#endif
        emit  GetBalanceByAddressComplete(rep.balance());
    } else {
#if GRPC_DEBUG
        qDebug() << "RecordRoute rpc GetBalanceByAddress failed.";
#endif
        emit GetBalanceByAddressError("RecordRoute rpc GetBalanceByAddress failed.");
    }
}

void gRPC::GetBalanceByAddresses(std::vector<std::string> addrs) {
    ClientContext context;
    setTimeout(&context);
    addMetadata(&context);
    //context.set_wait_for_ready(true);
    std::unique_ptr<grpc::ClientReaderWriter<protowire::KaspadMessage, protowire::KaspadMessage> > readerWritter(
                stub_->MessageStream(&context));
    // Data we are sending to the server.
    auto *req = new protowire::GetBalancesByAddressesRequestMessage;
    auto *rsp = new protowire::GetBalancesByAddressesResponseMessage;
    foreach (std::string addr, addrs) {
        req->add_addresses(addr);
    }
    KaspadMessage request, reply;
    request.set_allocated_getbalancesbyaddressesrequest(req);
    reply.set_allocated_getbalancesbyaddressesresponse(rsp);
    // Container for the data we expect from the server.
    readerWritter->Write(request);
    readerWritter->Read(&reply);
    readerWritter->WritesDone();
    grpc::Status status = readerWritter->Finish();
    if (status.ok()) {
        const auto rep = reply.getbalancesbyaddressesresponse();
        google::protobuf::RepeatedPtrField< ::protowire::BalancesByAddressEntry > entrys = rep.entries();
        uint64_t balance = 0;
        for(int i = 0; i < entrys.size(); i++) {
            protowire::BalancesByAddressEntry balanceEntry = entrys.at(i);
            balance += balanceEntry.balance();
        }
#if GRPC_DEBUG
        qDebug() << "----START----";
        qDebug() << "gRPC GetBalanceByAddresses: " << Global::Util::normaliseNumber((double)(balance / 100000000.0)) << "$KAS";
        qDebug() << "----END----";
#endif
        emit GetBalanceByAddressesComplete(balance);
    } else {
#if GRPC_DEBUG
        qDebug() << "RecordRoute rpc GetBalanceByAddresses failed.";
#endif
        emit GetBalanceByAddressesError("RecordRoute rpc GetBalanceByAddresses failed.");
    }
}

void gRPC::GetBlockCount() {
    ClientContext context;
    setTimeout(&context);
    addMetadata(&context);
    //context.set_wait_for_ready(true);
    std::unique_ptr<grpc::ClientReaderWriter<protowire::KaspadMessage, protowire::KaspadMessage> > readerWritter(
                stub_->MessageStream(&context));
    // Data we are sending to the server.
    auto *req = new protowire::GetBlockCountRequestMessage;
    auto *rsp = new protowire::GetBlockCountResponseMessage;
    KaspadMessage request, reply;
    request.set_allocated_getblockcountrequest(req);
    reply.set_allocated_getblockcountresponse(rsp);
    // Container for the data we expect from the server.
    readerWritter->Write(request);
    readerWritter->Read(&reply);
    readerWritter->WritesDone();
    grpc::Status status = readerWritter->Finish();
    if (status.ok()) {
        getBlockCount_t bCount;
        const auto rep = reply.getblockcountresponse();
        bCount.blockCount = rep.blockcount();
        bCount.headerCount = rep.headercount();
#if GRPC_DEBUG
        qDebug() << "----START----";
        qDebug() << "gRPC GetBlockCount: blockCount:" << bCount.blockCount;
        qDebug() << "gRPC GetBlockCount: headCount" << bCount.headerCount;
        qDebug() << "----END----";
#endif
        emit GetBlockCountComplete(bCount);
    } else {
#if GRPC_DEBUG
        qDebug() << "RecordRoute rpc GetBlockCount failed.";
#endif
        emit GetBlockCountError("RecordRoute rpc GetBlockCount failed.");
    }
}

void gRPC::GetBlockDagInfo() {
    ClientContext context;
    setTimeout(&context);
    addMetadata(&context);
    //context.set_wait_for_ready(true);
    std::unique_ptr<grpc::ClientReaderWriter<protowire::KaspadMessage, protowire::KaspadMessage> > readerWritter(
                stub_->MessageStream(&context));
    // Data we are sending to the server.
    auto *req = new protowire::GetBlockDagInfoRequestMessage;
    auto *rsp = new protowire::GetBlockDagInfoResponseMessage;
    KaspadMessage request, reply;
    request.set_allocated_getblockdaginforequest(req);
    reply.set_allocated_getblockdaginforesponse(rsp);
    // Container for the data we expect from the server.
    readerWritter->Write(request);
    readerWritter->Read(&reply);
    readerWritter->WritesDone();
    grpc::Status status = readerWritter->Finish();
    if (status.ok()) {
        blockDagInfo_t result;
        auto rep = reply.getblockdaginforesponse();
        result.networkName = rep.networkname();
        result.blockCount = rep.blockcount();
        result.headerCount = rep.headercount();
#if GRPC_DEBUG
        qDebug() << "----START----";
        qDebug() << "gRPC GetBlockDagInfo: Network name: " << result.networkName.c_str();
        qDebug() << "gRPC GetBlockDagInfo: Block count: " << result.blockCount;
        qDebug() << "gRPC GetBlockDagInfo: Header count: " << result.headerCount;
#endif
        for( int i = 0; i < rep.tiphashes().size(); i++ ) {
            std::string tipHashes = rep.tiphashes().at(i);
            result.tipHashes.insert(result.tipHashes.end(), tipHashes.c_str());
#if GRPC_DEBUG
            qDebug() << "gRPC GetBlockDagInfo: Tip hashes: " << tipHashes.c_str();
#endif
        }
        result.dificulty = rep.difficulty();
        result.pastMedianTime = rep.pastmediantime();
#if GRPC_DEBUG
        qDebug() << "gRPC GetBlockDagInfo: Dificulty: " << QString::asprintf("%f", result.dificulty);
        qDebug() << "gRPC GetBlockDagInfo: Post median time: " << result.pastMedianTime;
#endif
        for(  int i = 0; i < rep.virtualparenthashes().size(); i++ ) {
            std::string virtualParentHashes = rep.virtualparenthashes().at(i);
            result.virtualParentHashes.insert(result.virtualParentHashes.end(), virtualParentHashes.c_str());
#if GRPC_DEBUG
            qDebug() << "gRPC GetBlockDagInfo: Virtual parent hashes: " << virtualParentHashes.c_str();
#endif
        }
        result.pruningPointHash = rep.pruningpointhash();
        result.virtualDaaScore = rep.virtualdaascore();

#if GRPC_DEBUG
        qDebug() << "gRPC GetBlockDagInfo: Pruning point hashes: " << result.pruningPointHash.c_str();
        qDebug() << "gRPC GetBlockDagInfo: Virtual daa score: " << result.virtualDaaScore;
        qDebug() << "----END----";
#endif

        emit GetBlockDagInfoComplete(result);
    } else {
        emit GetBlockDagInfoError("RecordRoute rpc GetBlockDagInfo failed.");
    }
}

void gRPC::GetCoinSupply() {
    ClientContext context;
    setTimeout(&context, 10000);
    addMetadata(&context);
    //context.set_wait_for_ready(true);
    std::unique_ptr<grpc::ClientReaderWriter<protowire::KaspadMessage, protowire::KaspadMessage> > readerWritter(
                stub_->MessageStream(&context));
    // Data we are sending to the server.
    auto *req = new protowire::GetCoinSupplyRequestMessage;
    auto *rsp = new protowire::GetCoinSupplyResponseMessage;
    KaspadMessage request, reply;
    request.set_allocated_getcoinsupplyrequest(req);
    reply.set_allocated_getcoinsupplyresponse(rsp);
    // Container for the data we expect from the server.
    readerWritter->Write(request);
    readerWritter->Read(&reply);
    readerWritter->WritesDone();
    grpc::Status status = readerWritter->Finish();
    if (status.ok()) {
        const auto rep = reply.getcoinsupplyresponse();
        uint64_t circSupply = rep.circulatingsompi();
        uint64_t maxSupply = rep.maxsompi();
#if GRPC_DEBUG
        qDebug() << "----START----";
        qDebug() << "gRPC CirculatingSupply: " <<
                    Global::Util::normaliseNumber((double)(circSupply / 100000000.0)) << "$KAS CoinSupply: " <<
                    Global::Util::normaliseNumber((double)(maxSupply / 100000000.0)) << "$KAS";
        qDebug() << "----END----";
#endif
        coinSupply_t supply = {circSupply, maxSupply};
        emit GetCoinSupplyComplete(supply);
    } else {
        qDebug() << "RecordRoute rpc GetCoinSupply failed.";
        emit GetCoinSupplyError("RecordRoute rpc GetCoinSupply failed.");
    }
}

void gRPC::GetUtxosByAddresses(std::vector<std::string> addrs) {
    ClientContext context;
    setTimeout(&context);
    addMetadata(&context);
    //context.set_wait_for_ready(true);
    std::unique_ptr<grpc::ClientReaderWriter<protowire::KaspadMessage, protowire::KaspadMessage> > readerWritter(
                stub_->MessageStream(&context));
    // Data we are sending to the server.
    auto *req = new protowire::GetUtxosByAddressesRequestMessage;
    auto *rsp = new protowire::GetUtxosByAddressesResponseMessage;
    foreach (std::string addr, addrs) {
        req->add_addresses(addr);
    }
    KaspadMessage request, reply;
    request.set_allocated_getutxosbyaddressesrequest(req);
    reply.set_allocated_getutxosbyaddressesresponse(rsp);
    // Container for the data we expect from the server.
    readerWritter->Write(request);
    readerWritter->Read(&reply);
    readerWritter->WritesDone();
    grpc::Status status = readerWritter->Finish();
    if (status.ok()) {
        std::vector<getUtxosByAddressesEntry_t> utxos;
        const auto rep = reply.getutxosbyaddressesresponse();
        google::protobuf::RepeatedPtrField<protowire::UtxosByAddressesEntry> allentrys = rep.entries();
#if GRPC_DEBUG
        uint64_t balance =0;
        qDebug() << "----START----";
#endif
        for(int i = 0; i < allentrys.size(); i++) {
            getUtxosByAddressesEntry_t entry;
            protowire::UtxosByAddressesEntry utxoEntry = allentrys.at(i);
            entry.address = utxoEntry.address().c_str();
            entry.outpointTransactionId = utxoEntry.outpoint().transactionid();
            entry.outpointIndex = utxoEntry.outpoint().index();
            entry.utxoEntryAmount = utxoEntry.utxoentry().amount();
            entry.scriptPublicKeyUtxoEntryVersion = utxoEntry.utxoentry().scriptpublickey().version();
            entry.scriptPublicKeyUtxoEntryScriptPublicKey = utxoEntry.utxoentry().scriptpublickey().scriptpublickey().c_str();
            entry.utxoEntryBlockDaaScore = utxoEntry.utxoentry().blockdaascore();
            entry.utxoEntryIsCoinbase = utxoEntry.utxoentry().iscoinbase();
#if GRPC_DEBUG
            qDebug() << "----START ENTRY----";
            qDebug() << "gRPC GetUtxosByAddresses: Address: " << entry.address.c_str();
            qDebug() << "gRPC GetUtxosByAddresses: Outpoint transaction ID: " << entry.outpointTransactionId.c_str();
            qDebug() << "gRPC GetUtxosByAddresses: Outpoint index: " << entry.outpointIndex;
            qDebug() << "gRPC GetUtxosByAddresses: Utxo entry amount: " << Global::Util::normaliseNumber((double)entry.utxoEntryAmount / 100000000.0) << "$KAS";
            qDebug() << "gRPC GetUtxosByAddresses: Script public key utxo entry version: " << entry.scriptPublicKeyUtxoEntryVersion;
            qDebug() << "gRPC GetUtxosByAddresses: Script public key utxo entry script public key: " << entry.scriptPublicKeyUtxoEntryScriptPublicKey.c_str();
            qDebug() << "gRPC GetUtxosByAddresses: Utxo entry block daa score: " << entry.utxoEntryBlockDaaScore;
            qDebug() << "gRPC GetUtxosByAddresses: Utxo entry is coinbase: " << entry.utxoEntryIsCoinbase;
            qDebug() << "----END ENTRY----";
            balance += entry.utxoEntryAmount;
#endif
            utxos.insert(utxos.end(), entry);
        }
#if GRPC_DEBUG
        qDebug() << "gRPC GetUtxosByAddresses: balance = " << Global::Util::normaliseNumber((double)(balance / 100000000.0)) << "$KAS";
        qDebug() << "----END----";
#endif
        emit GetUtxosByAddressesComplete(utxos);
    } else {
#if GRPC_DEBUG
        qDebug() << "RecordRoute rpc GetUtxosByAddresses failed.";
#endif
        emit GetUtxosByAddressesError("RecordRoute rpc GetUtxosByAddresses failed.");
    }
}

