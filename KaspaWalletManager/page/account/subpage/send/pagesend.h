#ifndef PAGESEND_H
#define PAGESEND_H

#include <QWidget>
#include <QRect>
#include <QFont>
#include <QSize>
#include <QTimer>

//#include "api/rpc/rpcclass.h"
#include "wallet/walletgrpc.h"

#include "page/account/subpage/send/camera.h"


namespace Ui {
class PageSend;
}

class PageSend : public QWidget
{
    Q_OBJECT

public:
    explicit PageSend(QWidget *parent = nullptr);
    ~PageSend();
    void open();
    void close();
    void setScale();
    void setStyle();
    void loop();

private slots:
    void on_SendRetriveDone(const QString &s);
    void on_SendRetriveError(const QString &s);

private:
    Ui::PageSend *ui;

    void checkIntegrityOfInputs();
    bool checkEnoughFunds();

    QRect backPushButtonQRectBack;
    QSize backPushButtonQSizeBack;
    QRect headerFrameQRectBack;
    QRect titleLabelQRectBack;
    QFont titleLabelQFontBack;

    QRect recipientAddressLineEditQRectBack;
    QFont recipientAddressLineEditQFontBack;
    QRect amountLineEditQRectBack;
    QFont amountLineEditQFontBack;

    QRect qrPushButtonQRectBack;
    QSize qrPushButtonQSizeBack;
    QRect maximumPushButtonQRectBack;
    QSize maximumPushButtonQSizeBack;

    QRect sendPushButtonQRectBack;
    QFont sendPushButtonQFontBack;

    QRect sendingLabelQRectBack;
    QFont sendingLabelQFontBack;

    Camera *camera = nullptr;

    //WalletGRpc::Send *sendThread = nullptr;
    QThread *sendWorkerThread = nullptr;

    bool checkCameraAvailability();
signals:
    void sendOperate(QString amount, QString destAccount, QString ticker);
};

#endif // PAGESEND_H
