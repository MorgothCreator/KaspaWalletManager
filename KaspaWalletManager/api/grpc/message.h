#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
// MaxMessagePayload is the maximum bytes a message can be regardless of other
// individual limits imposed by messages themselves.
extern const int MaxMessagePayload; // 32MB

//typedef uint32_t MessageCommand;
// Commands used in kaspa message headers which describe the type of message.
typedef enum {
    // protocol
    CmdVersion,// MessageCommand = iota,
    CmdVerAck,
    CmdRequestAddresses,
    CmdAddresses,
    CmdRequestHeaders,
    CmdBlock,
    CmdTx,
    CmdPing,
    CmdPong,
    CmdRequestBlockLocator,
    CmdBlockLocator,
    CmdInvRelayBlock,
    CmdRequestRelayBlocks,
    CmdInvTransaction,
    CmdRequestTransactions,
    CmdDoneHeaders,
    CmdTransactionNotFound,
    CmdReject,
    CmdRequestNextHeaders,
    CmdRequestPruningPointUTXOSet,
    CmdPruningPointUTXOSetChunk,
    CmdUnexpectedPruningPoint,
    CmdIBDBlockLocator,
    CmdIBDBlockLocatorHighestHash,
    CmdIBDBlockLocatorHighestHashNotFound,
    CmdBlockHeaders,
    CmdRequestNextPruningPointUTXOSetChunk,
    CmdDonePruningPointUTXOSetChunks,
    CmdBlockWithTrustedData,
    CmdDoneBlocksWithTrustedData,
    CmdRequestPruningPointAndItsAnticone,
    CmdIBDBlock,
    CmdRequestIBDBlocks,
    CmdPruningPoints,
    CmdRequestPruningPointProof,
    CmdPruningPointProof,
    CmdReady,
    CmdTrustedData,
    CmdBlockWithTrustedDataV4,
    CmdRequestNextPruningPointAndItsAnticoneBlocks,
    CmdRequestIBDChainBlockLocator,
    CmdIBDChainBlockLocator,
    CmdRequestAnticone,

    // rpc
    CmdGetCurrentNetworkRequestMessage,
    CmdGetCurrentNetworkResponseMessage,
    CmdSubmitBlockRequestMessage,
    CmdSubmitBlockResponseMessage,
    CmdGetBlockTemplateRequestMessage,
    CmdGetBlockTemplateResponseMessage,
    CmdGetBlockTemplateTransactionMessage,
    CmdNotifyBlockAddedRequestMessage,
    CmdNotifyBlockAddedResponseMessage,
    CmdBlockAddedNotificationMessage,
    CmdGetPeerAddressesRequestMessage,
    CmdGetPeerAddressesResponseMessage,
    CmdGetSelectedTipHashRequestMessage,
    CmdGetSelectedTipHashResponseMessage,
    CmdGetMempoolEntryRequestMessage,
    CmdGetMempoolEntryResponseMessage,
    CmdGetConnectedPeerInfoRequestMessage,
    CmdGetConnectedPeerInfoResponseMessage,
    CmdAddPeerRequestMessage,
    CmdAddPeerResponseMessage,
    CmdSubmitTransactionRequestMessage,
    CmdSubmitTransactionResponseMessage,
    CmdNotifyVirtualSelectedParentChainChangedRequestMessage,
    CmdNotifyVirtualSelectedParentChainChangedResponseMessage,
    CmdVirtualSelectedParentChainChangedNotificationMessage,
    CmdGetBlockRequestMessage,
    CmdGetBlockResponseMessage,
    CmdGetSubnetworkRequestMessage,
    CmdGetSubnetworkResponseMessage,
    CmdGetVirtualSelectedParentChainFromBlockRequestMessage,
    CmdGetVirtualSelectedParentChainFromBlockResponseMessage,
    CmdGetBlocksRequestMessage,
    CmdGetBlocksResponseMessage,
    CmdGetBlockCountRequestMessage,
    CmdGetBlockCountResponseMessage,
    CmdGetBlockDAGInfoRequestMessage,
    CmdGetBlockDAGInfoResponseMessage,
    CmdResolveFinalityConflictRequestMessage,
    CmdResolveFinalityConflictResponseMessage,
    CmdNotifyFinalityConflictsRequestMessage,
    CmdNotifyFinalityConflictsResponseMessage,
    CmdFinalityConflictNotificationMessage,
    CmdFinalityConflictResolvedNotificationMessage,
    CmdGetMempoolEntriesRequestMessage,
    CmdGetMempoolEntriesResponseMessage,
    CmdShutDownRequestMessage,
    CmdShutDownResponseMessage,
    CmdGetHeadersRequestMessage,
    CmdGetHeadersResponseMessage,
    CmdNotifyUTXOsChangedRequestMessage,
    CmdNotifyUTXOsChangedResponseMessage,
    CmdUTXOsChangedNotificationMessage,
    CmdStopNotifyingUTXOsChangedRequestMessage,
    CmdStopNotifyingUTXOsChangedResponseMessage,
    CmdGetUTXOsByAddressesRequestMessage,
    CmdGetUTXOsByAddressesResponseMessage,
    CmdGetBalanceByAddressRequestMessage,
    CmdGetBalanceByAddressResponseMessage,
    CmdGetVirtualSelectedParentBlueScoreRequestMessage,
    CmdGetVirtualSelectedParentBlueScoreResponseMessage,
    CmdNotifyVirtualSelectedParentBlueScoreChangedRequestMessage,
    CmdNotifyVirtualSelectedParentBlueScoreChangedResponseMessage,
    CmdVirtualSelectedParentBlueScoreChangedNotificationMessage,
    CmdBanRequestMessage,
    CmdBanResponseMessage,
    CmdUnbanRequestMessage,
    CmdUnbanResponseMessage,
    CmdGetInfoRequestMessage,
    CmdGetInfoResponseMessage,
    CmdNotifyPruningPointUTXOSetOverrideRequestMessage,
    CmdNotifyPruningPointUTXOSetOverrideResponseMessage,
    CmdPruningPointUTXOSetOverrideNotificationMessage,
    CmdStopNotifyingPruningPointUTXOSetOverrideRequestMessage,
    CmdStopNotifyingPruningPointUTXOSetOverrideResponseMessage,
    CmdEstimateNetworkHashesPerSecondRequestMessage,
    CmdEstimateNetworkHashesPerSecondResponseMessage,
    CmdNotifyVirtualDaaScoreChangedRequestMessage,
    CmdNotifyVirtualDaaScoreChangedResponseMessage,
    CmdVirtualDaaScoreChangedNotificationMessage,
    CmdGetBalancesByAddressesRequestMessage,
    CmdGetBalancesByAddressesResponseMessage,
    CmdNotifyNewBlockTemplateRequestMessage,
    CmdNotifyNewBlockTemplateResponseMessage,
    CmdNewBlockTemplateNotificationMessage,
    CmdGetMempoolEntriesByAddressesRequestMessage,
    CmdGetMempoolEntriesByAddressesResponseMessage,
    CmdGetCoinSupplyRequestMessage,
    CmdGetCoinSupplyResponseMessage
} MessageCommand;


extern std::vector<std::pair<MessageCommand, std::string>> ProtocolMessageCommandToString;
extern std::vector<std::pair<MessageCommand, std::string>> RPCMessageCommandToString;

class Message {
public:
    MessageCommand Command() ;
    static std::string String(MessageCommand cmd) {
        using namespace std;
        bool ok = false;
        string cmdString;
        for(auto &i : ProtocolMessageCommandToString) {
            if(i.first == cmd) {
                ok = true;
                cmdString = i.second;
                break;
            }
        }
        if( !ok ) {
            ok = false;
            for(auto &i : RPCMessageCommandToString) {
                if(i.first == cmd) {
                    ok = true;
                    cmdString = i.second;
                    break;
                }
            }
            if( !ok ) {
                cmdString = "unknown command";
            }
        }
        int length = std::snprintf(nullptr, 0, "%s [code %d]", cmdString.c_str(), (int)cmd );
        char* str = new char[length+1]; // one more character for null terminator
        std::snprintf( str, length + 1, "%s [code %d]", cmdString.c_str(), (int)cmd );
        std::string cppstr( str );
        delete[] str;
        return cppstr;
    }
    /*uint64_t MessageNumber();
    void SetMessageNumber( uint64_t index );
    time_t ReceivedAt();
    void SetReceivedAt( time_t receivedAt );*/
};

#endif // MESSAGE_H
