#include "pagehistorylistmain.h"
#include "ui_pagehistorylistmain.h"

#include "global.h"
#include "style.h"

PageHistoryListMain::PageHistoryListMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageHistoryListMain) {
    ui->setupUi(this);

    thisQRectBack = geometry();

    setScale();
    setStyle();
}

PageHistoryListMain::PageHistoryListMain(QList<entry_t> entrys, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageHistoryListMain) {
    ui->setupUi(this);

    thisQRectBack = geometry();

    entry_t entry;
    foreach(entry, entrys) {
        append(entry.Amount, entry.AmountUsd, entry.TransactionId);
    }
    renumerotateEntrys();
    repaint();

    setScale();
    setStyle();
}

PageHistoryListMain::~PageHistoryListMain() {
    clear();
    delete ui;
}

void PageHistoryListMain::setScale() {
    setGeometry(Global::Layout::scaleRect(thisQRectBack));

    PageHistoryList *entry;
    foreach (entry, EntryList) {
        entry->setScale();
    }
    repaint();
}

void PageHistoryListMain::setStyle() {
    PageHistoryList *entry;
    foreach (entry, EntryList) {
        entry->setStyle();
    }
}

void PageHistoryListMain::append(double amount, double amountUsd, QString transactionId) {
    entry_t entryData;
    entryData.Amount = amount;
    entryData.AmountUsd = amountUsd;
    entryData.TransactionId = transactionId;
    PageHistoryList *entry = new PageHistoryList(entryData, this);
    entry->setVisible(true);
    EntryList.append(entry);
    renumerotateEntrys();
    //repaint();
    connect(entry, &PageHistoryList::setupPushButton, this, &PageHistoryListMain::setupPushButton);
}

void PageHistoryListMain::insert(int index, double amount, double amountUsd, QString transactionId) {
    entry_t entryData;
    entryData.Amount = amount;
    entryData.AmountUsd = amountUsd;
    entryData.TransactionId = transactionId;
    PageHistoryList *entry = new PageHistoryList(entryData, this);
    entry->setVisible(true);
    EntryList.insert(index, entry);
    renumerotateEntrys();
    //repaint();
    connect(entry, &PageHistoryList::setupPushButton, this, &PageHistoryListMain::setupPushButton);
}

void PageHistoryListMain::clear() {
    PageHistoryList *entry;
    foreach (entry, EntryList) {
        entry->setVisible(false);
        delete entry;
    }
    EntryList.clear();
    this->scroll(0, 0);
    QRect thisRect = this->geometry();
    thisRect.setBottom(1);
    this->setGeometry(thisRect);
}

void PageHistoryListMain::removeAt(int index) {
    EntryList[index]->setVisible(false);
    delete EntryList[index];
    EntryList.removeAt(index);
    renumerotateEntrys();
}

void PageHistoryListMain::repaint() {
    PageHistoryList *entry;
    int posY = 0;
    foreach (entry, EntryList) {
        QRect rect = entry->geometry();
        rect.moveTop(posY);
        posY += entry->geometry().height();
        entry->setGeometry(rect);
    }
    QRect thisRect = this->geometry();
    thisRect.setBottom(posY);
    this->setGeometry(thisRect);
}

/*void PageHistoryListMain::setWithdrawEnable(int index, bool enable) {
    EntryList[index]->setWithdrawEnable(enable);
}*/

void PageHistoryListMain::renumerotateEntrys() {
    PageHistoryList *entry;
    int count = 0;
    foreach (entry, EntryList) {
        entry->setIndex(count);
        count++;
    }
}
