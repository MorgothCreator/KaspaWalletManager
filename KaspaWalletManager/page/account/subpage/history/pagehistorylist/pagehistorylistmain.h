#ifndef PAGEDEXLISTMAIN_H
#define PAGEDEXLISTMAIN_H

#include <QWidget>
#include <QList>

#include <ui_pagehistory.h>
#include "pagehistorylist.h"

namespace Ui {
class PageHistoryListMain;
}

class PageHistoryListMain : public QWidget
{
    Q_OBJECT

public:
    typedef PageHistoryList::entry_t entry_t;
    explicit PageHistoryListMain(QWidget *parent = nullptr);
    explicit PageHistoryListMain(QList<entry_t> entrys, QWidget *parent = nullptr);
    ~PageHistoryListMain();
    void append(double amount, double amountUsd, QString transactionId);
    void insert(int index, double amount, double amountUsd, QString transactionId);
    void clear();
    void removeAt(int index);
    qsizetype count(){ return EntryList.count(); }
    void repaint();
    QList<PageHistoryList *> entryList() { return EntryList;}
    void setWithdrawEnable(int index, bool enable);
    void setScale();
    void setStyle();

private:
    Ui::PageHistoryListMain *ui;

    QList<PageHistoryList *> EntryList;
    void renumerotateEntrys();

    QRect thisQRectBack;
signals:
    void setupPushButton(int index);
};

#endif // PAGEDEXLISTMAIN_H
