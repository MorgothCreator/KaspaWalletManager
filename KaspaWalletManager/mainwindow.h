#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QTimer>

#include "api/web/webget.h"
#include "api/web/webclass.h"
#include "wallet/walletgrpc.h"

#include "page/accountManagement/pageimportwallet.h"
#include "page/accountManagement/pagenewaccount.h"
#include "page/accountManagement/pagenewwallet.h"
#include "page/accountManagement/pageopenwallet.h"
#include "page/accountManagement/pagerecoveraccount.h"

#include "page/account/pageaccount.h"
#include "page/more/pagemore.h"
#include "page/more/subpage/settings/pagesettings.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setScale();
    static void setPage(int index);
private:
    QRect walletNetworkNameLabelQRectBack;
    QFont walletNetworkNameLabelQFontBack;

    QTranslator * qtTranslator = NULL;

    networkName_e networkName = networkName_e::NONE;
    std::string accountNameAndNetwork;

    bool initialized = false;

    void switchTranslator(const QString filename);

    QTimer loopTimer;
    QTimer fetchCoinGeckoTimer;


private slots:
    void on_mainTabWidget_currentChanged(int index);
    void on_timerLoopTick();

    void fetchCoingecko();

private:
    Ui::MainWindow *ui;

    WebGet *coinGecckoFetchWorker = nullptr;

    QThread *poolWorkerThread = nullptr;

    QList<QPair<QString, QString>> *priceToRetriveList = nullptr;
signals:
    void coinGeckofetch(QString url);
    void poolStartFetch(QString token1, QString token0, QList<QString> *userData);
    void rpcDisconnect();
    void rpcSend(QString message);
};
#endif // MAINWINDOW_H
