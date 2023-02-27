#ifndef PAGEDEX_H
#define PAGEDEX_H

#include <QWidget>
#include <QHBoxLayout>
#include <QRect>
#include <QFont>
#include <QSize>

//#include "global.h"
#include "api/web/webget.h"
#include "api/web/webclass.h"

#include "pagehistorylist/pagehistorylistmain.h"
#include "api/grpc/grpc.h"

namespace Ui {
class PageHistory;
}

class PageHistory : public QWidget
{
    Q_OBJECT

public:
    explicit PageHistory(QWidget *parent = nullptr);
    ~PageHistory();
    void open(void *arg1);
    void close();
    void setScale();
    void setStyle();
    void loop();

private:
    Ui::PageHistory *ui;
    QWidget *parent;
    PageHistoryListMain *page;

    QMovie *progressMovie;
    QLabel *progressLabel;

    QRect backPushButtonQRectBack;
    QSize backPushButtonQSizeBack;
    QRect headerFrameQRectBack;
    QRect titleLabelQRectBack;
    QFont titleLabelQFontBack;
    QRect progressMovieQRectBack;

    QRect previousPagePushButtonQRectBack;
    QSize previousPagePushButtonQSizeBack;
    QRect nextPagePushButtonQRectBack;
    QSize nextPagePushButtonQSizeBack;
    QRect ofPagesLabelQRectBack;
    QFont ofPagesLabelQFontBack;


    int AccountListChangedCount = -1;
    int SelectedAccountChangedCount = -1;
    std::vector<gRPC::getUtxosByAddressesEntry_t> *utxos = NULL;
    size_t currentShownPage = 0;
    //networkName_e network = networkName_e::NONE;
    //QList<WebClass::DexGetSuportedExtTokens::entry_t> EntryList;
    //QList<WebClass::DexGetAllWallets::entry_t> WalletsEntryList;
};

#endif // PAGEDEX_H
