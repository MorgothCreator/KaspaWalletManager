#include "pageaccount.h"
#include <list>
#include <string>
#include "api/grpc/protos/macosx/kaspawalletd.pb.h"
#include "api/grpc/protos/macosx/rpc.pb.h"
#include "ui_pageaccount.h"

#include <QListWidgetItem>
#include <QListView>
#include <QVBoxLayout>
#include <QTimer>

#include "style.h"
#include "global.h"
#include "translate/translate.h"

#include "api/grpc/grpc.h"

#define ACCOUNT_REFRESH_INTERVAL    (30*1000)

PageAccount::PageAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageAccount) {
    this->parent = parent;
    setGeometry(Global::Layout::getTabLayoutGeometryScaled());
    ui->setupUi(this);
    setStyle();

    messageList = new PageAccountList(this);

    messageList->setGeometry(QRect(10, Global::Layout::scaleValueX(180), parent->geometry().width() - 20,
                                   parent->geometry().height() - Global::Layout::scaleValueX(180) - Global::Layout::scaleValueX(MENU_BAR_HEIGHT + 9)));
    messageList->setStyleSheet(
                "border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px;"
                "border-style: solid; background-color: transparent;"
                "border-width: 1px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + ";");

    progressMovie = new QMovie(":/res/ic/res/ic/waiting_light.gif");
    if (progressMovie->isValid()) {
        progressLabel = new QLabel(this);
        progressLabel->setGeometry(135,320,40,40);
        progressLabel->setScaledContents(true);
        progressLabel->setMovie(progressMovie);
        progressLabel->setVisible(false);
        //progressMovie->start();
    }

    // Backup items geometry, size and font.
    onlineLabelQRectBack = ui->onlineLabel->geometry();
    onlineLabelQFontBack = ui->onlineLabel->font();
    lyraLogoLabelQRectBack = ui->logoLabel->geometry();
    //lyraLogoLabelQSizeBack = ui->lyraLogoLabel->pixmap().size();
    accountValueKasLabelQRectBack = ui->accountValueKasLabel->geometry();
    accountValueKasLabelQFontBack = ui->accountValueKasLabel->font();
    accountTotalValueUsdLabelQRectBack = ui->accountTotalValueUsdLabel->geometry();
    accountTotalValueUsdLabelQFontBack = ui->accountTotalValueUsdLabel->font();
    sendPushButtonQRectBack = ui->sendPushButton->geometry();
    sendPushButtonQSizeBack = ui->sendPushButton->iconSize();
    historyPushButtonQRectBack = ui->historyPushButton->geometry();
    historyPushButtonQSizeBack = ui->historyPushButton->iconSize();
    receivePushButtonQRectBack = ui->receivePushButton->geometry();
    receivePushButtonQSizeBack = ui->receivePushButton->iconSize();
    historyLabelQRectBack = ui->historyLabel->geometry();
    historyLabelQFontBack = ui->historyLabel->font();
    progressMovieQRectBack = progressLabel->geometry();
    messageListQRectBack = messageList->geometry();

    setScale();

    Style::invertPushButtonIcon(ui->sendPushButton, true);
    Style::invertPushButtonIcon(ui->receivePushButton, true);
    Style::invertPushButtonIcon(ui->historyPushButton, true);

    messageList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    messageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    messageList->scrollToTop();
    messageList->setEnabled(true);

    connect(messageList, &PageAccountList::itemClicked, this, [=](int i){
        Global::Page::goManagerPage(Global::Page::HISTORY, &utxosSegregatedList.at(i));
    });
    /*messageList->addMessage("KAS",
                            "kaspa:ppk66xua7nmq8elv3eglfet0xxcfuks835xdgsm5jlymjhazyu6h5ac62l4ey",
                            "2e7185d936a87d72646877648ddbf6c4ccddf947f345c36b812650a4859cad71",
                            1000000,
                            1000000 * 0.0048725,
                            0.0048);

    messageList->addMessage("KAS",
                            "kaspa:ppk66xua7nmq8elv3eglfet0xxcfuks835xdgsm5jlymjhazyu6h5ac62l4ey",
                            "3d8037b7f073c2d2cfb78b9df897a764dea3d9413d4e32e101118557de56b06d",
                            2000000,
                            2000000 * 0.0048725,
                            0.0048);*/

    messageList->scrollToTop();

    connect(ui->sendPushButton, &QPushButton::clicked, ui->sendPushButton, &QPushButton::setDisabled);
    connect(ui->receivePushButton, &QPushButton::clicked, ui->receivePushButton, &QPushButton::clearFocus);

    refreshTimer.setInterval(ACCOUNT_REFRESH_INTERVAL);
    connect(&refreshTimer, &QTimer::timeout, this, [=] {
        //getBalance();
        //if(Wallet::History::get())
            refreshBalances();
    });
    refreshTimer.start();

    ui->historyLabel->setVisible(false);
    ui->historyPushButton->setVisible(false);
}

PageAccount::~PageAccount() {
    delete ui;
}

void PageAccount::open() {
}

void PageAccount::close() {

}

void PageAccount::setScale() {
    this->setGeometry(Global::Layout::getTabLayoutGeometryScaled());
    ui->onlineLabel->setGeometry(Global::Layout::scaleRect(onlineLabelQRectBack));
    ui->onlineLabel->setFont(Global::Layout::scaleFontOffset(onlineLabelQFontBack));
    ui->logoLabel->setGeometry(Global::Layout::scaleRect(lyraLogoLabelQRectBack));
    //ui->lyraLogoLabel->setIconSize(Global::Layout::scaleSize(lyraLogoLabelQSizeBack));
    ui->accountValueKasLabel->setGeometry(Global::Layout::scaleRect(accountValueKasLabelQRectBack));
    ui->accountValueKasLabel->setFont(Global::Layout::scaleFontOffset(accountValueKasLabelQFontBack));
    ui->accountTotalValueUsdLabel->setGeometry(Global::Layout::scaleRect(accountTotalValueUsdLabelQRectBack));
    ui->accountTotalValueUsdLabel->setFont(Global::Layout::scaleFontOffset(accountTotalValueUsdLabelQFontBack));
    ui->sendPushButton->setGeometry(Global::Layout::scaleRect(sendPushButtonQRectBack));
    ui->sendPushButton->setIconSize(Global::Layout::scaleSize(sendPushButtonQSizeBack));
    ui->historyPushButton->setGeometry(Global::Layout::scaleRect(historyPushButtonQRectBack));
    ui->historyPushButton->setIconSize(Global::Layout::scaleSize(historyPushButtonQSizeBack));
    ui->receivePushButton->setGeometry(Global::Layout::scaleRect(receivePushButtonQRectBack));
    ui->receivePushButton->setIconSize(Global::Layout::scaleSize(receivePushButtonQSizeBack));
    ui->historyLabel->setGeometry(Global::Layout::scaleRect(historyLabelQRectBack));
    ui->historyLabel->setFont(Global::Layout::scaleFontOffset(historyLabelQFontBack, Global::Layout::labelFontScale()));
    progressLabel->setGeometry(Global::Layout::scaleRect(progressMovieQRectBack));
    messageList->setGeometry(QRect(10, Global::Layout::scaleValueX(180), parent->geometry().width() - 20,
                                   parent->geometry().height() - Global::Layout::scaleValueX(180) - Global::Layout::scaleValueX(MENU_BAR_HEIGHT + 9)));
}

void PageAccount::setStyle() {
    //Style::setButtonTransparentStyle(ui->lyraLogoLabel);
    Style::setOfflineLabelStyle(ui->onlineLabel);
    Style::setTitleStyle(ui->logoLabel);
    Style::setLabelStyle(ui->accountValueKasLabel);
    Style::setLabelStyle(ui->accountTotalValueUsdLabel);
    Style::setButtonSendReceiveStyle(ui->sendPushButton);
    Style::setButtonTransparentStyle(ui->historyPushButton);
    Style::setButtonSendReceiveStyle(ui->receivePushButton);
    Style::setLabelStyle(ui->historyLabel);
}

void PageAccount::loop() {
    if( AccountListChangedCount != Global::Account::getAccountListChangedCount() ||
            SelectedAccount != Global::Account::getSelectedAccount() ||
            network != Global::Network::getNetwork() ) {
        AccountListChangedCount = Global::Account::getAccountListChangedCount();
        SelectedAccount = Global::Account::getSelectedAccount();
        network = Global::Network::getNetwork();
        if( Global::Account::getAccountList().count() > 0 ) {
            //if(Wallet::History::get()) {
                refreshBalances();
            //}
            refreshTimer.stop();
            refreshTimer.start();
        }
    }
    if( BalancesChangedCount != Global::TickerPrice::getModifyCount() ) {
        BalancesChangedCount = Global::TickerPrice::getModifyCount();
        QList<QString> tickerList = messageList->getTickers();
        foreach( QString ticker, tickerList ) {
            messageList->setTokenValue(ticker, Global::TickerPrice::get(ticker.remove('$')));
        }
        ui->accountTotalValueUsdLabel->setText(
                    Global::Util::normaliseNumber((double)(lastBalance / 100000000.0) * Global::TickerPrice::get("KAS"), 2) + "USD");
    }
    if( Global::Network::getOnline() ) {
        ui->onlineLabel->setText(Translate::tr("Online"));
        Style::setOnlineLabelStyle(ui->onlineLabel);
    } else {
        ui->onlineLabel->setText(Translate::tr("Offline"));
        Style::setOfflineLabelStyle(ui->onlineLabel);
    }
}

bool compareInterval(gRPC::getUtxosByAddressesEntry_t i1, gRPC::getUtxosByAddressesEntry_t i2) {
    return (i1.utxoEntryBlockDaaScore > i2.utxoEntryBlockDaaScore);
}

void PageAccount::refreshBalances() {
    connect(walletGrpc, &WalletGRpc::GetUtxosByAddressesComplete, this, [=](std::vector<gRPC::getUtxosByAddressesEntry_t> utxos) {
        uint64_t amountInAccount = 0;
        double usdPerKas = Global::TickerPrice::get("KAS");
        std::vector<std::pair<std::string, uint64_t>> addressList;
        std::vector<std::vector<gRPC::getUtxosByAddressesEntry_t>> utxosSegregatedListTmp;
        std::sort(utxos.begin(), utxos.end(), compareInterval);
        for( size_t i = 0; i < utxos.size(); i++ ) {
            amountInAccount += utxos.at(i).utxoEntryAmount;
            size_t j = 0;
            for( j = 0; j < addressList.size(); j++ ) {
                if(!addressList.at(j).first.compare(utxos.at(i).address)) {
                    addressList.at(j).second += utxos.at(i).utxoEntryAmount;
                    utxosSegregatedListTmp.at(j).push_back(utxos.at(i));
                    break;
                }
            }
            if( j == addressList.size() ) {
                std::pair<std::string, uint64_t>entry = {utxos.at(i).address, utxos.at(i).utxoEntryAmount};
                addressList.push_back(entry);
                std::vector<gRPC::getUtxosByAddressesEntry_t> entrySegregatedList;
                entrySegregatedList.push_back(utxos.at(i));
                utxosSegregatedListTmp.push_back(entrySegregatedList);
            }
        }
        if( amountInAccount != lastBalance ) {
            messageList->clearAll();
            for( size_t i = 0; i < addressList.size(); i++ ) {
                std::pair<std::string, uint64_t>entry = addressList.at(i);
                messageList->addMessage("KAS",
                                        entry.first.c_str(),
                                        //entry.outpointTransactionId.c_str(),
                                        (double)(entry.second / 100000000.0),
                                        (double)(entry.second / 100000000.0) * usdPerKas,
                                        usdPerKas);
            }
            ui->accountValueKasLabel->setText(Global::Util::normaliseNumber((double)(amountInAccount / 100000000.0), 4) + "KAS");
            ui->accountTotalValueUsdLabel->setText(Global::Util::normaliseNumber((double)(amountInAccount / 100000000.0) * usdPerKas, 2) + "USD");
            lastBalance = amountInAccount;
            utxosSegregatedList = utxosSegregatedListTmp;
            messageList->scrollToTop();
        }
        //progressMovie->stop();
        //progressLabel->setVisible(false);
    });
    connect(walletGrpc, &WalletGRpc::GetUtxosByAddressesError, this, [=](std::string s) {
        Q_UNUSED(s)
        //progressMovie->stop();
        //progressLabel->setVisible(false);
    });
    //progressMovie->start();
    //progressLabel->setVisible(true);
    std::vector<std::string> addrs;
    addrs.insert(addrs.end(), Global::Account::getAccountPublicId().toStdString());
    walletGrpc->getUtxosByAddresses(addrs);
}

void PageAccount::on_sendPushButton_clicked() {
    ui->sendPushButton->clearFocus();
    Global::Page::goManagerPage(Global::Page::SEND);
}

extern "C" {
#include "crypto/bip39.h"
#include "crypto/bip32.h"
}
void PageAccount::on_receivePushButton_clicked() {
    ui->receivePushButton->clearFocus();
    QStringList addrList;
    addrList.append(Global::Account::getAccountPublicId());
    /*for( size_t i = 0; i < utxosSegregatedList.size(); i++ ) {
        if(utxosSegregatedList.at(i).size())
            addrList.append(utxosSegregatedList.at(i).at(0).address.c_str());
    }*/
    Global::Page::goManagerPage(Global::Page::RECEIVE, &addrList);
}

void PageAccount::on_historyPushButton_clicked() {
    Global::Page::goManagerPage(Global::Page::HISTORY);
}



