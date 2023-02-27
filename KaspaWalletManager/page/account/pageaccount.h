#ifndef PAGEACCOUNT_H
#define PAGEACCOUNT_H

#include <QWidget>

#include <QRect>
#include <QFont>
#include <QSize>
#include <QMovie>
#include <QLabel>
#include <QTimer>

#include "globakaspa.h"
#include "pageaccountlist/pageaccountlist.h"
//#include "page/account/subpage/history/pagehistory.h"
#include "wallet/walletgrpc.h"

namespace Ui {
class PageAccount;
}

class PageAccount : public QWidget {
    Q_OBJECT

public:
    explicit PageAccount(QWidget *parent = nullptr);
    ~PageAccount();
    void open();
    void close();
    void setScale();
    void setStyle();
    void loop();
private slots:
    void on_sendPushButton_clicked();
    void on_receivePushButton_clicked();
    void on_historyPushButton_clicked();

private:
    void refreshBalances();

    Ui::PageAccount *ui;
    QWidget *parent;
    PageAccountList *messageList;
    std::vector<std::vector<gRPC::getUtxosByAddressesEntry_t>> utxosSegregatedList;
    QMovie *progressMovie;
    QLabel *progressLabel;

    QTimer refreshTimer;

    /*WalletGRpc::Balance *balanceThread = nullptr;
    QThread *balanceWorkerThread = nullptr;
    WalletGRpc::History *historyThread = nullptr;
    QThread *historyWorkerThread = nullptr;
    WalletGRpc::Receive *receiveThread = nullptr;
    QThread *receiveWorkerThread = nullptr;*/

    QRect onlineLabelQRectBack;
    QFont onlineLabelQFontBack;
    QRect lyraLogoLabelQRectBack;
    QSize lyraLogoLabelQSizeBack;
    QRect accountValueKasLabelQRectBack;
    QFont accountValueKasLabelQFontBack;
    QRect accountTotalValueUsdLabelQRectBack;
    QFont accountTotalValueUsdLabelQFontBack;
    QRect sendPushButtonQRectBack;
    QSize sendPushButtonQSizeBack;
    QRect historyPushButtonQRectBack;
    QSize historyPushButtonQSizeBack;
    QRect receivePushButtonQRectBack;
    QSize receivePushButtonQSizeBack;
    QRect historyLabelQRectBack;
    QFont historyLabelQFontBack;
    QRect progressMovieQRectBack;
    QRect messageListQRectBack;

    int AccountListChangedCount = -1;
    int SelectedAccount = -1;
    int BalancesChangedCount = -1;
    uint64_t lastBalance;
    networkName_e network = networkName_e::NONE;

signals:
    void balanceStartFetch();
    void historyStartFetch();
    void receiveStartFetch();
};

#endif // PAGEACCOUNT_H
