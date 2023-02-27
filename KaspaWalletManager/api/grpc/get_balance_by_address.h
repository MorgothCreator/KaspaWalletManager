#ifndef GET_BALANCE_BY_ADDRESS_H
#define GET_BALANCE_BY_ADDRESS_H

#include <string>
#include "base_message.h"
#include "message.h"
#include "message.h"
#include "error.h"

class GetBalanceByAddressRequestMessage {
public:
    baseMessage BaseMessage;
    std::string Address;
    MessageCommand Command() { return CmdGetBalanceByAddressRequestMessage; };
    static GetBalanceByAddressRequestMessage *NewGetBalanceByAddressRequest(std::string Address) {
        GetBalanceByAddressRequestMessage *inst = new GetBalanceByAddressRequestMessage();
        inst->BaseMessage = baseMessage();
        inst->Address = Address;
        return inst;
    }
};

class GetBalanceByAddressResponseMessage {
public:
    baseMessage BaseMessage;
    uint64_t Balance;
    RPCError *Error;
    MessageCommand Command() { return CmdGetBalanceByAddressResponseMessage; };
    static GetBalanceByAddressResponseMessage *NewGetBalanceByAddressResponse(uint64_t Balance) {
        GetBalanceByAddressResponseMessage *inst = new GetBalanceByAddressResponseMessage();
        inst->BaseMessage = baseMessage();
        inst->Balance = Balance;
        return inst;
    }
};

#endif // GET_BALANCE_BY_ADDRESS_H
