#ifndef HISTORY_H
#define HISTORY_H

#include <QString>

namespace Wallet {
    class History
    {
    public:
        typedef enum {
            ERR_OK = 0,
            ERR_DECODE,
            ERR_INVALID_ACCOUNT
        }HistoryEntry_e;

        typedef struct{
            int ChangeCount;
            QString Name;
            //GrpcClass::History *history;
        }HistoryEntry_t;

        static Wallet::History::HistoryEntry_e set(QString data);
        //static Wallet::History::HistoryEntry_e set(GrpcClass::History *history);
        static Wallet::History::HistoryEntry_t *get();
        static double getTickerBalance(QString ticker);
        static QList<QString> getAvailableTikers();
        static int getChangeCount();
    private:
    };
}

#endif // HISTORY_H
