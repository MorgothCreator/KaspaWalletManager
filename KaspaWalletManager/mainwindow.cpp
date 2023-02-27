#include "mainwindow.h"
#include "global.h"
#include "ui_mainwindow.h"

#include <QTranslator>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QLayout>
#include <QVector>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "color.h"
#include "global.h"
#include "style.h"
#include "storage/storagesettings.h"

#include "util/bech32.h"
extern "C" {
#include "crypto/bip32.h"
#include "crypto/bip39.h"
}

int lastIndex = -1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) ,
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    qDebug() << COMPOSE_WALLET_PARH;
    qSetRealNumberPrecision(KASPA_DECIMALS);
    switchTranslator("ro");
    mainTabWidget = ui->mainTabWidget;
    this->setWindowFlags(( windowFlags() & ~(Qt::WindowFullscreenButtonHint | Qt::WindowMaximizeButtonHint)) | Qt::CustomizeWindowHint | Qt::MSWindowsFixedSizeDialogHint);
	double windowScale = StorageSettings::genGet("windowScale", "1.0").toDouble();
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE || defined(Q_OS_ANDROID)
	windowScale = 1.0;
#endif
    Global::Layout::setXScale(windowScale);
    Global::Layout::setYScale(windowScale);
    Global::Layout::setHeaderHeight(0);


    // Backup items geometry, size and font.
    walletNetworkNameLabelQRectBack = ui->walletNetworkNameLabel->geometry();
    walletNetworkNameLabelQFontBack = ui->walletNetworkNameLabel->font();

    const QScreen* screen = qApp->primaryScreen();
    Global::Layout::setScreenWidth(screen->availableSize().width());
    Global::Layout::setScreenHeight(screen->availableSize().height());

    // On mobile we need the actually available application window
#if defined(__APPLE__) || defined(Q_OS_ANDROID)
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE || defined(Q_OS_ANDROID)
    Global::Layout::setXScale((double)screen->availableSize().width() / (double)Global::Layout::getLayoutGeometry().width());
    Global::Layout::setYScale((double)(screen->availableSize().height()) / (double)Global::Layout::getLayoutGeometry().height());
    Global::Layout::setHeaderHeight(screen->availableVirtualGeometry().y());
    //Global::Layout::setHeaderHeight(QGuiApplication::primaryScreen()->availableSize().height() - screen->availableSize().height());
    qDebug() << "Available size: " << screen->availableSize().height() << "Layout size: " << Global::Layout::getLayoutGeometry().height();
    qDebug() << "X: " << Global::Layout::getXScale() << "Y: " << Global::Layout::getYScale();
#endif
#endif
/*#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      //define something for Windows (64-bit only)
   #else
      //define something for Windows (32-bit only)
   #endif
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
         // iOS, tvOS, or watchOS Simulator
        const QScreen* screen = qApp->primaryScreen();
        Global::setVScale((double)screen->availableSize().width() / (double)Global::getLayoutGeometry().width());
        Global::setHScale((double)(screen->availableSize().height()) / (double)Global::getLayoutGeometry().height());
    #elif TARGET_OS_MACCATALYST
         // Mac's Catalyst (ports iOS API into Mac, like UIKit).
    #elif TARGET_OS_IPHONE
        // iOS, tvOS, or watchOS device
    #elif TARGET_OS_MAC
        // Other kinds of Apple platforms
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    // linux
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif
#if defined(Q_OS_ANDROID)
    const QScreen* screen = qApp->primaryScreen();
    Global::setVScale((double)screen->availableSize().width() / (double)Global::getLayoutGeometry().width());
    Global::setHScale((double)(screen->availableSize().height()) / (double)Global::getLayoutGeometry().height());
#endif*/
    setScale();
    ui->mainTabWidget->repaint();

    ui->mainTabWidget->setParent(this);
    pageImportWallet = new PageImportWallet(this);
    pageNewAccount = new PageNewAccount(this);
    pageNewWallet = new PageNewWallet(this);
    pageOpenWallet = new PageOpenWallet(this);
    pageRecoverAccount = new PageRecoverAccount(this);
    pageShowSeed = new PageShowSeed(this);
    pageHistory = new PageHistory(this);
    pageTransactionDetail = new PageTransactionDetail(this);
    pageSend = new PageSend(this);
    pageReceive = new PageReceive(this);
    pageSettings = new PageSettings(this);

    pageImportWallet->setVisible(false);
    pageNewAccount->setVisible(false);
    pageNewWallet->setVisible(false);
    pageOpenWallet->setVisible(true);
    pageRecoverAccount->setVisible(false);
    pageShowSeed->setVisible(false);
    pageHistory->setVisible(false);
    pageTransactionDetail->setVisible(false);
    pageSend->setVisible(false);
    pageReceive->setVisible(false);
    pageSettings->setVisible(false);
    ui->mainTabWidget->setVisible(false);


    pageAccount = new PageAccount(ui->mainTabWidget);
    pageMore = new PageMore(ui->mainTabWidget);
    ui->mainTabWidget->clear();
    ui->mainTabWidget->addTab(pageAccount, tr("ACCOUNT"));
    ui->mainTabWidget->addTab(pageMore, tr("MORE"));
    initialized = true;
    ui->mainTabWidget->setCurrentIndex(Global::Page::PAGE::NONE);

    // One to one hardwritten pairs insertion
    /*QPair<QString, double> tickerPrice;
    tickerPrice.first = "USDT";
    tickerPrice.second = 1.0;
    Global::TickerPrice::set(tickerPrice);
    tickerPrice.first = "USDC";
    tickerPrice.second = 1.0;
    Global::TickerPrice::set(tickerPrice);
    tickerPrice.first = "BUSD";
    tickerPrice.second = 1.0;
    Global::TickerPrice::set(tickerPrice);*/


    fetchCoinGeckoTimer.setInterval(250);
    connect(&fetchCoinGeckoTimer, &QTimer::timeout, this, &MainWindow::fetchCoingecko);
    fetchCoinGeckoTimer.start();

    ui->walletNetworkNameLabel->setParent(this);
    Style::setLabelStyle(ui->walletNetworkNameLabel);
    ui->walletNetworkNameLabel->setGeometry(ui->walletNetworkNameLabel->geometry().x(),
                                            ui->walletNetworkNameLabel->geometry().y() + Global::Layout::getHeaderHeight(),
                                            ui->walletNetworkNameLabel->geometry().width(),
                                            ui->walletNetworkNameLabel->geometry().height());
    ui->walletNetworkNameLabel->clear();

    Global::Network::setNetwork(StorageSettings::get("network", "TESTNET"));
    networkName = Global::Network::getNetwork();

    QTimer::singleShot(100, this, [=]{
        walletGrpc = new WalletGRpc(Global::Network::getNodeAddress().second.toStdString());
        walletGrpc->rpcConnect();

        loopTimer.setInterval(250);
        connect(&loopTimer, &QTimer::timeout, this, &MainWindow::on_timerLoopTick);
        loopTimer.start();
    });
    /*****************************************************************************/
    /*****************************************************************************/
    /*****************************************************************************/
    /*****************************************************************************/
    /**************** Next code is to check critical functions********************/
    /*****************************************************************************/
    /*****************************************************************************/
    /*****************************************************************************/
    /*****************************************************************************/
    /*****************************************************************************/
// Check Bech32 Encode/Decode properly with Kaspa address flavour.
    qDebug() << "******************************************************************";
    qDebug() << "Test Bech32 with Kaspa address flavour:";
    bech32::decoded dec = bech32::Decode("kaspa:qqegf2g6zpdlxjhye8q2v7qdvtht74rhwap9aaumzl68z26q7mj7yykuh6lqe");
    qDebug() << "Desired address:     kaspa:qqegf2g6zpdlxjhye8q2v7qdvtht74rhwap9aaumzl68z26q7mj7yykuh6lqe";
    qDebug() << "Resulting address:  " << bech32::Encode("kaspa", dec.second, dec.first.first).c_str();
/*****************************************************************************/
    // Try to obtain the right address 0 derivated from seed.
#define USE_DEVELOPMENT_NETWORK_DISABLE 0
#define USE_DEVELOPMENT_NETWORK_TESTNET 1
#define USE_DEVELOPMENT_NETWORK_MAINNET 2
#define USED_DEVELOPMENT_NETWORK  USE_DEVELOPMENT_NETWORK_MAINNET
#if USED_DEVELOPMENT_NETWORK != USE_DEVELOPMENT_NETWORK_DISABLE
#if USED_DEVELOPMENT_NETWORK == USE_DEVELOPMENT_NETWORK_MAINNET
    int addressXKeyPrefix = BIP32_XKEY_NET_MAINNET;
    std::string addrPrefix = "kaspa";
#elif USED_DEVELOPMENT_NETWORK == USE_DEVELOPMENT_NETWORK_TESTNET
    //int addressXKeyPrefix = BIP32_XKEY_NET_TESTNET;
    //std::string addrPrefix = "kaspatest";
#endif
    qDebug() << "******************************************************************";
    qDebug() << "Test bip39 mnemonic encoding/decoding:";
    uint8_t bits[32 + 1] = {0};
    int mnemonic_bits_len = mnemonic_to_bits((const char *)"pond noise gallery return crush middle skate salon shallow merge crime urban", bits);
    QString seedHex = "Hex seed: ";
    for (int cnt = 0; cnt < 16; cnt++) {
      seedHex += QString::asprintf("0x%X", (unsigned char)bits[cnt]);
      if(cnt < 15)
        seedHex += ", ";
    }
    const char *m = mnemonic_from_data(bits, 16);
    QString mnemonic = QString::fromLocal8Bit(m);
    qDebug() << "Expecting mnemonic: pond noise gallery return crush middle skate salon shallow merge crime urban";
    qDebug() << "Resulting mnemonic:" << mnemonic;

    qDebug() << "******************************************************************";
    qDebug() << "Test child address generator from seed:";
    qDebug() << seedHex;
    QByteArray seed((char *)bits, 17);
    BIP32_xkey_t masterKey;
    BIP32_xkey_t masterChild;
    BIP32_xkey_t pubKey;
#if 0
    // Original function in "crypto/signatures.h"
    qDebug() << "Resulting address: " << signatures::getAccountIdFromPrivateKey(seed);
#else
    // Generate master key:
    BIP32_NewMaster((uint8_t *)seed.data(), seed.length(), (BIP32_XKEY_NET)addressXKeyPrefix, &masterKey);
    BIP32_derive_private_child(&masterKey, &masterChild, 0);
    BIP32_derive_public_child(&masterChild, &pubKey, 0);
    bech32::data pk(std::begin(pubKey.privateKey), std::end(pubKey.privateKey));
    uint8_t version = 0;
    qDebug() << "Desired address:     kaspa:qqegf2g6zpdlxjhye8q2v7qdvtht74rhwap9aaumzl68z26q7mj7yykuh6lqe";
    qDebug() << "Resulting address: " << QString::fromStdString(bech32::Encode(addrPrefix, pk, version));
#endif
    qDebug() << "******************************************************************";
#endif
    /*****************************************************************************/
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setScale() {
    this->setGeometry(Global::Layout::getLayoutGeometryScaled());
    this->setStyleSheet("background: " + Color::getBackground());
    Style::setMainTabStyle(ui->mainTabWidget);
    ui->walletNetworkNameLabel->setGeometry(Global::Layout::scaleRect(walletNetworkNameLabelQRectBack));
    ui->walletNetworkNameLabel->setFont(Global::Layout::scaleFontOffset(walletNetworkNameLabelQFontBack));
    ui->mainTabWidget->setGeometry(Global::Layout::getLayoutGeometryScaled());
    ui->mainTabWidget->setFont(Global::Layout::scaleFontOffset(ui->mainTabWidget->font()));
}

void MainWindow::setPage(int index) {
    lastIndex = index;
}

void MainWindow::on_mainTabWidget_currentChanged(int index) {
    if(!initialized)
        return;
    //qDebug() << "selected" << index;
    if(lastIndex != index) {
        switch(lastIndex) {
        case Global::Page::ACCOUNT:
            pageAccount->close();
            break;
        case Global::Page::MORE:
            pageMore->close();
            break;
        default:
            break;
        }
        switch(index) {
        case Global::Page::ACCOUNT:
            pageAccount->open();
            break;
        case Global::Page::MORE:
            pageMore->open();
            break;
        default:
            break;
        }
        lastIndex = index;
    }
}

void MainWindow::on_timerLoopTick() {
    if(accountNameAndNetwork != Global::Util::getAccountNameAndNetwork()) {
        accountNameAndNetwork = Global::Util::getAccountNameAndNetwork();
        ui->walletNetworkNameLabel->setText(Global::Util::getAccountNameAndNetwork().c_str());
    }
    if(networkName != Global::Network::getNetwork()) {
        networkName = Global::Network::getNetwork();
        ui->walletNetworkNameLabel->setText(Global::Util::getAccountNameAndNetwork().c_str());
        if(walletGrpc)
            delete walletGrpc;
        walletGrpc = new WalletGRpc();
        walletGrpc->rpcConnect();
    }
    switch(lastIndex) {
    case Global::Page::ACCOUNT:
        pageAccount->loop();
        break;
    case Global::Page::MORE:
        pageMore->loop();
        break;
    case Global::Page::HISTORY:
        pageHistory->loop();
        break;
    case Global::Page::SEND:
        pageSend->loop();
        break;
    case Global::Page::RECEIVE:
        pageReceive->loop();
        break;
    case Global::Page::SETTINGS:
        pageSettings->loop();
        break;
    default:
        break;
    }
    /*if(networkName != Global::Network::getNetwork()) {
        networkName = Global::Network::getNetwork();
        if(!priceToRetriveList)
            //getPoolPairPrice();
    }*/
}

void MainWindow::switchTranslator(const QString filename) {
    // remove the old translator
    if(qtTranslator != NULL)
        qApp->removeTranslator(qtTranslator);
    qtTranslator = new QTranslator(this);
    // load the new translator
    //QString path = QApplication::applicationDirPath();
    //path.append("/languages/");
    if(qtTranslator->load(":/languages/languages/LyraPcWalletManager_" + filename + ".qm")) //Here Path and Filename has to be entered because the system didn't find the QM Files else
        qApp->installTranslator(qtTranslator);
    else
        qDebug() << "Unable to find translation file";
}

void MainWindow::fetchCoingecko() {
    fetchCoinGeckoTimer.stop();
    fetchCoinGeckoTimer.setInterval(5 * 60 *1000);
    fetchCoinGeckoTimer.start();
    if(coinGecckoFetchWorker) {
        coinGecckoFetchWorker->disconnect();
        coinGecckoFetchWorker->deleteLater();
        delete coinGecckoFetchWorker;
    }
    coinGecckoFetchWorker = new WebGet;
    connect(coinGecckoFetchWorker, &WebGet::resultReady, this, [=](QString data) {
        WebClass::CoinGecko coinGecko(data);
    });
    connect(coinGecckoFetchWorker, &WebGet::resultError, this, [=](QString err) {
        qDebug() << err;
    });
    connect(this, &MainWindow::coinGeckofetch, coinGecckoFetchWorker, &WebGet::doWork);
    coinGecckoFetchWorker->doWork("https://api.coingecko.com/api/v3/simple/price?"
                                  "ids=kaspa,lyra,tron,ethereum,bitcoin,tether,binance-usd,usd-coin,ethereum-classic&"
                                  "vs_currencies=usd&"
                                  "include_market_cap=false&"
                                  "include_24hr_vol=false&"
                                  "include_24hr_change=false&"
                                  "include_last_updated_at=false");
}
