#include "pagehistorylist.h"
#include "ui_pagehistorylist.h"

#include <QPixmap>

#include "global.h"
#include "style.h"

PageHistoryList::PageHistoryList(entry_t entry,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageHistoryList) {
    ui->setupUi(this);
    Parent = parent;
    Index = entry.Index;
    setAmount(entry.Amount);
    setAmountUsd(entry.AmountUsd);
    setTransactionId(entry.TransactionId);

    thisQRectBack = this->geometry();
    groupBoxQRectBack = ui->groupBox->geometry();

    //tickerIconLabelQRectBack = ui->tickerIconLabel->geometry();
    //tickerIconLabelQSizeBack = ui->tickerIconLabel->size();

    amountLabelQRectBack = ui->amountLabel->geometry();
    amountLabelQFontBack = ui->amountLabel->font();
    amountValueLabelQRectBack = ui->amountValueLabel->geometry();
    amountValueLabelQFontBack = ui->amountValueLabel->font();
    amountValueUsdLabelQRectBack = ui->amountValueUsdLabel->geometry();
    amountValueUsdLabelQFontBack = ui->amountValueUsdLabel->font();
    transactionIdLabelQRectBack = ui->transactionIdLabel->geometry();
    transactionIdLabelQFontBack = ui->transactionIdLabel->font();
    transactionIdValueLabelQRectBack = ui->transactionIdValueLabel->geometry();
    transactionIdValueLabelQFontBack = ui->transactionIdValueLabel->font();

    ui->transactionIdLabel->setWordWrap(true);

    setupPushButtonQRectBack = ui->setupPushButton->geometry();
    setupPushButtonQSizeBack = ui->setupPushButton->iconSize();

    ui->setupPushButton->setVisible(false);


    setStyle();
    setScale();

    Style::invertPushButtonIcon(ui->setupPushButton, true);
}

PageHistoryList::~PageHistoryList() {
    delete ui;
}

void PageHistoryList::setScale() {
    setGeometry(Global::Layout::scaleRect(thisQRectBack));
    ui->groupBox->setGeometry(Global::Layout::scaleRect(groupBoxQRectBack));

    //ui->tickerIconLabel->setGeometry(Global::Layout::scaleRect(tickerIconLabelQRectBack));
    //ui->tickerIconLabel->setSize(tickerIconLabelQSizeBack);

    ui->amountLabel->setGeometry(Global::Layout::scaleRect(amountLabelQRectBack));
    ui->amountLabel->setFont(Global::Layout::scaleFontOffset(amountLabelQFontBack));
    ui->amountValueLabel->setGeometry(Global::Layout::scaleRect(amountValueLabelQRectBack));
    ui->amountValueLabel->setFont(Global::Layout::scaleFontOffset(amountValueLabelQFontBack));
    ui->amountValueUsdLabel->setGeometry(Global::Layout::scaleRect(amountValueUsdLabelQRectBack));
    ui->amountValueUsdLabel->setFont(Global::Layout::scaleFontOffset(amountValueUsdLabelQFontBack));
    ui->transactionIdLabel->setGeometry(Global::Layout::scaleRect(transactionIdLabelQRectBack));
    ui->transactionIdLabel->setFont(Global::Layout::scaleFontOffset(transactionIdLabelQFontBack));
    ui->transactionIdValueLabel->setGeometry(Global::Layout::scaleRect(transactionIdValueLabelQRectBack));
    ui->transactionIdValueLabel->setFont(Global::Layout::scaleFontOffset(transactionIdValueLabelQFontBack));

    ui->setupPushButton->setGeometry(Global::Layout::scaleRect(setupPushButtonQRectBack));
    ui->setupPushButton->setIconSize(Global::Layout::scaleSize(setupPushButtonQSizeBack));
    ui->transactionIdValueLabel->setText(Global::Util::wrapText(TransactionId, ui->transactionIdValueLabel->geometry().width(), ui->transactionIdValueLabel->fontMetrics()));
}

void PageHistoryList::setStyle() {
    this->setStyleSheet(
                "background-color: transparent;"
                "border-width: 1px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + ";");
    Style::setGroupBoxStyle(ui->groupBox);
    Style::setAditionalColorLabelStyle(ui->transactionIdLabel);
    Style::setLabelStyle(ui->transactionIdValueLabel);
    Style::setAditionalColorLabelStyle(ui->amountLabel);
    Style::setLabelStyle(ui->amountValueLabel);
    Style::setAditionalColorLabelStyle(ui->amountValueUsdLabel);
}

void PageHistoryList::setAmount(double amount) {
    Amount = amount;
    ui->amountValueLabel->setText(Global::Util::normaliseNumber(amount) + "KAS");
}

void PageHistoryList::setAmountUsd(double amountUsd) {
    AmountUsd = amountUsd;
    ui->amountValueUsdLabel->setText(Global::Util::normaliseNumber(amountUsd, 2) + "USD");
}

void PageHistoryList::setTransactionId(QString transactionId) {
    TransactionId = transactionId;
    ui->transactionIdValueLabel->setText(Global::Util::wrapText(TransactionId, ui->transactionIdValueLabel->geometry().width(), ui->transactionIdValueLabel->fontMetrics()));
}


void PageHistoryList::on_setupPushButton_clicked() {
    emit setupPushButton(Index);
}

