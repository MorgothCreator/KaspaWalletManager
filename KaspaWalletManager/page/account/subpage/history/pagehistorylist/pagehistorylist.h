#ifndef PAGEDEXLIST_H
#define PAGEDEXLIST_H

#include <QWidget>
#include <QPixmap>

#include <QRect>
#include <QFont>
#include <QSize>

namespace Ui {
class PageHistoryList;
}

class PageHistoryList : public QWidget
{
    Q_OBJECT

public:
    typedef struct {
        int Index;
        double Amount;
        double AmountUsd;
        QString TransactionId;
    }entry_t;
    explicit PageHistoryList(entry_t entry, QWidget *parent = nullptr);
    ~PageHistoryList();
    void setIndex(int index) { Index = index;}
    void setTicker(QString ticker);
    void setAmount(double amount);
    void setAmountUsd(double amount);
    void setTransactionId(QString transactionId);
    void setScale();
    void setStyle();

private:
    Ui::PageHistoryList *ui;
    QWidget *Parent;
    int Index;
    double Amount;
    double AmountUsd;
    QString TransactionId;

    QRect thisQRectBack;
    QRect groupBoxQRectBack;

    QRect tickerIconLabelQRectBack;
    QSize tickerIconLabelQSizeBack;

    QRect amountLabelQRectBack;
    QFont amountLabelQFontBack;
    QRect amountValueLabelQRectBack;
    QFont amountValueLabelQFontBack;
    QRect amountValueUsdLabelQRectBack;
    QFont amountValueUsdLabelQFontBack;
    QRect transactionIdLabelQRectBack;
    QFont transactionIdLabelQFontBack;
    QRect transactionIdValueLabelQRectBack;
    QFont transactionIdValueLabelQFontBack;

    QRect setupPushButtonQRectBack;
    QSize setupPushButtonQSizeBack;
signals:
    void setupPushButton(int index);
private slots:
    void on_setupPushButton_clicked();
};

#endif // PAGEDEXLIST_H
