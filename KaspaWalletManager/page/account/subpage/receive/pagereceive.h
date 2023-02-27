#ifndef PAGERECEIVE_H
#define PAGERECEIVE_H

#include <QWidget>
#include <QRect>
#include <QFont>
#include <QSize>
#include <QTimer>

#include "extensions/QZXing/QZXing.h"

namespace Ui {
class PageReceive;
}

class PageReceive : public QWidget
{
    Q_OBJECT

public:
    explicit PageReceive(QWidget *parent = nullptr);
    ~PageReceive();
    void open(void *arg1);
    void close();
    void setScale();
    void setStyle();
    void loop();

private:
    Ui::PageReceive *ui;

    QTimer fadeTimer;
    int fadeCount = 0;
    QStringList addrList;
    bool lockAccountsComboBox;

    QRect backPushButtonQRectBack;
    QSize backPushButtonQSizeBack;
    QRect headerFrameQRectBack;
    QRect titleLabelQRectBack;
    QFont titleLabelQFontBack;

    QRect accountsComboBoxQRectBack;
    QSize accountsComboBoxQSizeBack;
    QFont accountsComboBoxQFontBack;
    QRect addressGroupBoxQRectBack;
    QFont addressGroupBoxQFontBack;
    QRect qrLabelQRectBack;
    QRect copyAddressHorizontalLayoutQRectBack;
    QFont addressLabelQFontBack;
    QRect copyAddressPushButtonQRectBack;
    QSize copyAddressPushButtonQSizeBack;

    QRect copiedLabelQRectBack;
    QFont copiedLabelQFontBack;

    void showQr(QString addr);
};

#endif // PAGERECEIVE_H
