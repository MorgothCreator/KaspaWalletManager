#ifndef BASE_MESSAGE_H
#define BASE_MESSAGE_H

#include <time.h>
#include <stdint.h>

class baseMessage
{
private:
    uint64_t messageNumber;
    time_t receivedAt;
public:
    baseMessage() {
        receivedAt = time(NULL);
    }
    uint64_t MessageNumber() {
        return messageNumber;
    }

    void SetMessageNumber(uint64_t messageNumber) {
        this->messageNumber = messageNumber;
    }

    time_t ReceivedAt() {
        return receivedAt;
    }

    void SetReceivedAt(time_t receivedAt) {
        this->receivedAt = receivedAt;
    }};

#endif // BASE_MESSAGE_H
