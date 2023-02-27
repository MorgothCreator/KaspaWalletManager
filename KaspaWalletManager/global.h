#ifndef GLOBAL_H
#define GLOBAL_H

#include <QTabWidget>
#include <QWidget>
#include <QRect>
#include <QFont>
#include <QSize>
#include <QList>
#include <QDebug>
#include <QMessageBox>
#include <QStandardPaths>

#include "page/account/pageaccount.h"
#include "page/more/pagemore.h"

#include "page/accountManagement/pageimportwallet.h"
#include "page/accountManagement/pagenewaccount.h"
#include "page/accountManagement/pagenewwallet.h"
#include "page/accountManagement/pageopenwallet.h"
#include "page/accountManagement/pagerecoveraccount.h"
#include "page/accountManagement/pageshowseed.h"

#include "page/account/subpage/history/pagehistory.h"
#include "page/account/subpage/history/pagetransactiondetail.h"
#include "page/account/subpage/send/pagesend.h"
#include "page/account/subpage/receive/pagereceive.h"

#include "page/more/subpage/settings/pagesettings.h"

#include "globakaspa.h"
#include "crypto/base58Encoding.h"
#include "crypto/signatures.h"
#include "util/bech32.h"

#include "storage/storagecommon.h"

#include "api/grpc/grpc.h"

#define GRPC_DEBUG   true

#define PAGE_WIDTH      310
#define MENU_BAR_HEIGHT 30

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define FONT_OFFSET     0.8
#elif __linux__
#define FONT_OFFSET     0.8
#else
#define FONT_OFFSET     1
#endif

#define TICKER  "KAS"

#define FADE_COUNT_START_VALE   250
#define MAX_HISTORY_ENTRY_NR    32

extern QTabWidget *mainTabWidget;

extern PageAccount *pageAccount;
extern PageMore *pageMore;

extern PageImportWallet *pageImportWallet;
extern PageNewAccount *pageNewAccount;
extern PageNewWallet *pageNewWallet;
extern PageOpenWallet *pageOpenWallet;
extern PageRecoverAccount *pageRecoverAccount;
extern PageShowSeed *pageShowSeed;

extern PageHistory *pageHistory;
extern PageTransactionDetail *pageTransactionDetail;
extern PageSend *pageSend;
extern PageReceive *pageReceive;

extern PageSettings *pageSettings;

extern WalletGRpc *walletGrpc;

extern double yScale;
extern double xScale;
extern int headerHeight;
extern int ScreenWidth;
extern int ScreenHeight;

extern networkName_e Net;
extern bool Online;
extern QList<QList<QPair<QString,QString>>> NodeList;

#define DEFAULT_WALLET_EXTENSION    ".kas"
#define COMPOSE_WALLET_PARH     QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
#define COMPOSE_WALLET_NAME     COMPOSE_WALLET_PARH + QDir::separator() + Global::Wallet::Name::get() + DEFAULT_WALLET_EXTENSION
#define COMPOSE_SETTINGS_PARH     QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
#define COMPOSE_SETTINGS_NAME     COMPOSE_SETTINGS_PARH + QDir::separator() + Global::Wallet::Name::get() + "_cfg"
#define COMPOSE_GEN_SETTINGS_PARH     QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
#define COMPOSE_GEN_SETTINGS_NAME     COMPOSE_SETTINGS_PARH + QDir::separator() + "cfg"

#if defined(__APPLE__) || defined(Q_OS_ANDROID)
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE || defined(Q_OS_ANDROID)
#define SCREEN_WIDTH_DIFFERENCE ((getScreenWidth() / getLayoutGeometry().width()) * 0.4)
#else
#define SCREEN_WIDTH_DIFFERENCE 1
#endif
#else
#define SCREEN_WIDTH_DIFFERENCE 1
#endif

namespace Global {
    class Page{
    public:
        typedef enum {
            NONE = -1,
            ACCOUNT = 0,
            MORE,

            IMPORT_WALLET,
            NEW_ACCOUNT,
            NEW_WALLET,
            OPEN_WALLET,
            RECOVER_ACCOUNT,
            SHOW_SEED,

            HISTORY,
            TRANSACTION_DETAIL,
            SEND,
            RECEIVE,
            ADD_STAKING_ACCOUNT,

            DEX_WITHDRAW,
            DEX_DEPOSIT,

            SETTINGS,
        }PAGE;

        //static void backManagerPage();
        static void goManagerPage(PAGE page, void *arg1 = nullptr, void *arg2 = nullptr);
    };

    class Layout {
    public:
        static QRect getLayoutGeometry() { return QRect(0, headerHeight, PAGE_WIDTH, 532); }
        static QRect getLayoutGeometryScaled() { return QRect(0, headerHeight, (int)((double)PAGE_WIDTH * xScale),
                                                              (int)((double)getLayoutGeometry().height() * yScale)); }

        static QRect getTabLayoutGeometry() { return QRect(0, 0, PAGE_WIDTH, getLayoutGeometry().height() - MENU_BAR_HEIGHT); }
        static QRect getTabLayoutGeometryScaled() { return QRect(0, 0, (int)((double)PAGE_WIDTH * xScale),
                                                                 (int)((double)getTabLayoutGeometry().height() * yScale)); }

        static void setScreenWidth( int screenWidth) { ScreenWidth = screenWidth; }
        static int getScreenWidth() { return ScreenWidth; }
        static void setScreenHeight( int screenHeight) { ScreenWidth = screenHeight; }
        static int getScreenHeight() { return ScreenHeight; }

        static void setXScale(double sc) { xScale = sc; }
        static void setYScale(double sc) { yScale = sc; }

        static double getXScale() { return xScale; }
        static double getYScale() { return yScale; }

        static void setHeaderHeight(int height) { headerHeight = height; }
        static int getHeaderHeight() { return headerHeight; }

        static int scaleValue(double value) { return (int)((double)value * xScale); }
        static int scaleValue(double value, double scale) { return (int)((double)value * scale); }
        static int scaleValueY(double value) { return (int)((double)value * yScale); }
        static int scaleValueX(double value) { return scaleValue(value); }

        static QFont scaleFont(QFont font) { font.setPointSize((int)((double)font.pointSize() * xScale * FONT_OFFSET/* * xScale * SCREEN_WIDTH_DIFFERENCE*/)); return font; }
        static QFont scaleFont(QFont font, double scale) { font.setPointSize((int)((double)font.pointSize() * xScale * FONT_OFFSET/* * (xScale / scale) * SCREEN_WIDTH_DIFFERENCE*/)); Q_UNUSED(scale); return font; }
        static QFont scaleFontOffset(QFont font) { font.setPointSize((int)((double)font.pointSize() * xScale/* * xScale*/ * FONT_OFFSET/* * SCREEN_WIDTH_DIFFERENCE*/)); return font; }
        static QFont scaleFontOffset(QFont font, double scale) { font.setPointSize((int)((double)font.pointSize() * xScale/* * xScale*/ * FONT_OFFSET/* * scale * SCREEN_WIDTH_DIFFERENCE*/)); Q_UNUSED(scale); return font; }

        static QRect scaleRect(QRect rect) { return QRect((int)((double)rect.x() * xScale), (int)((double)rect.y() * xScale),
                                                          (int)((double)rect.width() * xScale), (int)((double)rect.height() * xScale)); }
        static QRect scaleRect(QRect rect, double scale) { return QRect((int)((double)rect.x() * scale), (int)((double)rect.y() * scale),
                                                                        (int)((double)rect.width() * scale), (int)((double)rect.height() * scale)); }
        static QRect scaleRectXY(QRect rect) { return QRect((int)((double)rect.x() * xScale), (int)((double)rect.y() * yScale),
                                                            (int)((double)rect.width() * xScale), (int)((double)rect.height() * yScale)); }
        static QRect scaleRectXYNoDisplace(QRect rect) { return QRect((int)((double)rect.x() * xScale), (int)((double)rect.y() * xScale),
                                                                      (int)((double)rect.width() * xScale), (int)((double)rect.height() * xScale * yScale)); }

        static QSize scaleSize(QSize size) { return QSize((int)((double)size.width() * xScale), (int)((double)size.height() * xScale)); }
        static QSize scaleSize(QSize size, double scale) { return QSize((int)((double)size.width() * scale), (int)((double)size.height() * scale)); }

        static double labelFontScale() {
            double scale = 1.0;
#if defined(__APPLE__) || defined(Q_OS_ANDROID)
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE || defined(Q_OS_ANDROID)
            scale = 1;
#else
            scale = 1;
#endif
#endif
        return scale;
        }
    };
    /**********************************************************************************/
    class Network {
    public:
        static void setNetwork(networkName_e network) { Net = network; }
        static void setNetwork(QString network) {
            if(!network.compare("TESTNET"))
                Net = networkName_e::TESTNET;
            else if(!network.compare("MAINNET"))
                Net = networkName_e::MAINNET;
            else if(!network.compare("DEVNET"))
                Net = networkName_e::DEVNET;
            else if(!network.compare("SIMNET"))
                Net = networkName_e::SIMNET;
            else
                Net = networkName_e::NONE;
        }
        static networkName_e getNetwork() { return Net; }
        static QString getNetworkName() {
            switch(Net) {
                case TESTNET: return "TESTNET";
                case MAINNET: return "MAINNET";
                case DEVNET: return "DEVNET";
                case SIMNET: return "SIMNET";
                default: return "TESTNET";
            }
        }
        static QString getNetworkName(networkName_e i) {
            switch(i) {
                case TESTNET: return "TESTNET";
                case MAINNET: return "MAINNET";
                case DEVNET: return "DEVNET";
                case SIMNET: return "SIMNET";
                default: return "NONE";
            }
        }
        static QPair<QString,QString> getNodeAddress() { return NodeList[Net][0]; }
        static void setOnline(bool online) { Online = online; }
        static bool getOnline() { return Online; }
    };
/**********************************************************************************/
    namespace Wallet {
        class Name {
        public:
            static void set(QString name);
            static QString get();
        };
        class Password {
        public:
            static void set(QString p);
            static QString get();
            static bool check(QString p);
            static void destroy();
        };
    };
    /**********************************************************************************/
    class Account {
    public:
        typedef struct account_s {
            QString accountName;
            QString privateKey;
        }account_t;
        static bool setAccountList(QList<account_t> accountList);
        static void clearAccountList();
        static QList<account_t> getAccountList();
        static account_t *getAccount();
        static QString getAccountName();
        static QString getAccountPrivateKey();
        static QString getAccountPublicId();
        static void addAccount(account_t account);
        static void addAccount(QString accountName, QString privateKey, QString publicId);
        static void delAccount(QString name);
        static void delAccount(int position);
        static int getAccountListChangedCount();
        /**********************************************************************************/
        static bool setSelectedAccount(int accountNr);
        static bool setSelectedAccount(QString accountName);
        static int getSelectedAccount();
        static QString getSelectedAccountName();
        static int getSelectedAccountChangedCnt();
    };
    /**********************************************************************************/
    class TickerIcon {
    public:
        static QString get(QString ticker);
    };
    /**********************************************************************************/
    class TickerPrice {
    public:
        static void set(QPair<QString, double> tickerPrice);
        static double get(QString ticker);
        static int getModifyCount(QString ticker);
        static int getModifyCount();
        static QList<QPair<int, QPair<QString, double>>> getList();
    };
    /**********************************************************************************/
    class Swap {
    public:
        static QList<QString> getAvailableTickers();
    };

    /**********************************************************************************/
    /**********************************************************************************/
    /**********************************************************************************/
    /**********************************************************************************/
    typedef struct {

    }accountData_t;
    /**********************************************************************************/
    class Util {
    public:
        static std::string getAccountNameAndNetwork() {
            if(Global::Account::getAccountList().count() == 0)
                return "";
            return Global::Account::getSelectedAccountName().toStdString() + "/" + Global::Network::getNetworkName().toStdString();
        }
        static QString tickerToSign(QString ticker) { return ticker.replace("tether/", "$"); }
        static QString signToTicker(QString ticker) { return ticker.replace("$", "tether/"); }
        static QString truncateIdHash(QString idHash, int len) {
            if(idHash.length() < len)
                return idHash;
            if(len < 4)
                return "";
            return idHash.left((len / 2) - 1) + "..." + idHash.right((len / 2) - 1);
        }
        static QString normaliseNumber(QString snr) {
            if(snr.indexOf('.') != -1) {
                while ( snr.at(snr.length() - 1) == '0' && snr.at(snr.length() - 1) != '.') {
                    snr.remove(snr.length() - 1, 1);
                }
            }
            return snr;
        }
        static QString normaliseNumber(double nr, int decimals = 8) {
            QString expression = "%." + QString::number(decimals) + "f";
            QString snr = QString::asprintf(expression.toUtf8(), nr);
            return normaliseNumber(snr, true);
        }
        static QString normaliseNumber(QString snr, bool clearZeroDecimals) {
            snr = snr.remove(',');
            while (!snr.mid(0, 1).compare('0') && !snr.mid(1, 1).compare('0')) { snr.remove(1,1); }
            if(clearZeroDecimals) {
                if(snr.indexOf('.') != -1) {
                    while ( snr.at(snr.length() - 1) == '0' && snr.at(snr.length() - 1) != '.' ) {
                        snr.remove(snr.length() - 1, 1);
                    }
                }
                if(snr.at(snr.length() - 1) == '.')
                    snr.remove(snr.length() - 1, 1);
            }
            bool negative = snr.contains('-');
            snr = snr.remove('-');
            int loc = snr.indexOf('.');
            if(snr.length() > 2) {
                if(loc != -1) {
                    if(loc > 12) {
                        snr.insert(loc - 3, ',');
                        snr.insert(loc - 6, ',');
                        snr.insert(loc - 9, ',');
                        snr.insert(loc - 12, ',');
                    } else if(loc > 9) {
                        snr.insert(loc - 3, ',');
                        snr.insert(loc - 6, ',');
                        snr.insert(loc - 9, ',');
                    } else if(loc > 6) {
                        snr.insert(loc - 3, ',');
                        snr.insert(loc - 6, ',');
                    } else if(loc > 3)
                        snr.insert(loc - 3, ',');
                } else {
                    int len = snr.length();
                    if(len > 12) {
                        snr.insert(len - 3, ',');
                        snr.insert(len - 6, ',');
                        snr.insert(len - 9, ',');
                        snr.insert(len - 12, ',');
                    } else if(len > 9) {
                        snr.insert(len - 3, ',');
                        snr.insert(len - 6, ',');
                        snr.insert(len - 9, ',');
                    } else if(len > 6) {
                        snr.insert(len - 3, ',');
                        snr.insert(len - 6, ',');
                    } else if(len > 3)
                        snr.insert(len - 3, ',');
                }
            }
            if(negative)
                snr.insert(0, '-');
            return snr;
        }
        static QString tickerToTokenName(QString ticker);
        static QString tokenNameToTicker(QString tokenName);
        static QString wrapText(const QString &str, const int maxWidth, const QFontMetrics &fontMetrics) {
            QString wrapped;
            int start = 0;
            int current = 0;
            for (; current < str.length(); ++current) {
                const QString sub = str.mid(start, current - start);
                const int textLength = fontMetrics.size(Qt::TextSingleLine, sub).width();
                if (textLength + fontMetrics.maxWidth() > maxWidth) {
                    wrapped += sub;
                    //if (!wrapped.isEmpty())
                        wrapped += "\n";
                    start = current + 1;
                }
            }
            wrapped += str.mid(start);
            return wrapped;
        }
    };
    class Check {
    public:
        static bool checkWalletFileNameValid(QString name) {
            static const QRegularExpression nameMatcher("^[a-zA-Z0-9_-]*$", QRegularExpression::CaseInsensitiveOption);
            QRegularExpressionMatch match = nameMatcher.match(name);
            if (!match.hasMatch() || name.length() < 1) {
                return false;
            } else {
                return true;
            }
        }
        static bool checkFileNameWithSpacesValid(QString name) {
            static const QRegularExpression nameMatcher("^[a-zA-Z0-9_-]*$", QRegularExpression::CaseInsensitiveOption);
            foreach(const QString &tmp, name.split(" ")) {
                QRegularExpressionMatch match = nameMatcher.match(tmp);
                if (!match.hasMatch() || name.length() < 1) {
                    return false;
                }
            }
            return true;
        }
        static bool privateKey(QString privateKey) {
            return signatures::validatePrivateKey(privateKey);
        }
        static bool accountId(QString accountId) {
            if (bech32::Decode(accountId.toStdString()).second.empty()) {
                return false;
            } else {
                return true;
            }
        }

        static bool password(QString password1, QString password2) {
            return password1.compare(password2) == 0 && password1.length() >= 8 && password2.length() >= 8 ? true: false;
        }

        static bool password(QString password) {
            return password.length() >= 8 ? true: false;
        }
    };
    class Error {
/*      OK = 0,
        ALREADY_EXISTS,
        NOT_EXISTS,
        INVALID_NAME,
        CANNOT_SAVE,
        CANNOT_READ,
        INVALID_FILE,
        FILE_PROTECTED,
        ACCOUNT_NOT_FOUND,
        INVALID_PASSWORD
        */
    public:
        static bool show(QWidget *parent, Global::Errors::Errors_e err) {
            switch(err) {
            case Global::Errors::ALREADY_EXISTS:
                QMessageBox::critical(parent, "ERROR", "A file with this name already exists.");
                break;
            case Global::Errors::FILE_NOT_EXISTS:
                QMessageBox::critical(parent, "ERROR", "The file with this name does not exist.");
                break;
            case Global::Errors::INVALID_NAME:
                QMessageBox::critical(parent, "ERROR", "The name has invalid format.");
                break;
            case Global::Errors::CANNOT_SAVE:
                QMessageBox::critical(parent, "ERROR", "Unable to save the wallet file.");
                break;
            case Global::Errors::CANNOT_READ:
                QMessageBox::critical(parent, "ERROR", "Unable to read the wallet file.");
                break;
            case Global::Errors::INVALID_FILE:
                QMessageBox::critical(parent, "ERROR", "Invalid file format.");
                break;
            case Global::Errors::FILE_PROTECTED:
                QMessageBox::critical(parent, "ERROR", "The file is protected.");
                break;
            case Global::Errors::ACCOUNT_NOT_FOUND:
                QMessageBox::critical(parent, "ERROR", "Account not found.");
                break;
            case Global::Errors::INVALID_PASSWORD:
                QMessageBox::critical(parent, "ERROR", "Invalid password.");
                break;
            case Global::Errors::INVALID_PRIVATE_KEY:
                QMessageBox::critical(parent, "ERROR", "Invalid private key.");
                break;
            default:
                return false;
            }
            return true;
        }
    };
};

#endif // GLOBAL_H
