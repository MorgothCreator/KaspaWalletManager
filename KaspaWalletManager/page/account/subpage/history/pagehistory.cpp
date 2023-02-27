#include "pagehistory.h"
#include "ui_pagehistory.h"

#include <QScroller>

#include "global.h"
#include "color.h"
#include "style.h"

#include "page/account/pageaccount.h"
#include "wallet/history.h"

PageHistory::PageHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageHistory) {
    ui->setupUi(this);
    this->parent = parent;

    // Backup items geometry, size and font.
    backPushButtonQRectBack = ui->backPushButton->geometry();
    backPushButtonQSizeBack = ui->backPushButton->iconSize();
    headerFrameQRectBack = ui->headerFrame->geometry();
    titleLabelQRectBack = ui->titleLabel->geometry();
    titleLabelQFontBack = ui->titleLabel->font();

    previousPagePushButtonQRectBack = ui->previousPagePushButton->geometry();
    previousPagePushButtonQSizeBack = ui->previousPagePushButton->iconSize();
    nextPagePushButtonQRectBack = ui->nextPagePushButton->geometry();
    nextPagePushButtonQSizeBack = ui->nextPagePushButton->iconSize();
    ofPagesLabelQRectBack = ui->ofPagesLabel->geometry();
    ofPagesLabelQFontBack = ui->ofPagesLabel->font();

    page = new PageHistoryListMain(this);
    ui->scrollArea->setWidget(page);

    progressMovie = new QMovie(":/res/ic/res/ic/waiting_light.gif");
    if (progressMovie->isValid()) {
        progressLabel = new QLabel(this);
        progressLabel->setGeometry(135,260,40,40);
        progressLabel->setScaledContents(true);
        progressLabel->setMovie(progressMovie);
        progressLabel->setVisible(false);
        //progressMovie->start();
    }
    progressMovieQRectBack = progressLabel->geometry();

    connect(page, &PageHistoryListMain::setupPushButton, this, [=](int index) {
        qDebug() << "Setup" << index;
    });

    setScale();
    setStyle();

    QScrollerProperties sp;
    sp.setScrollMetric(QScrollerProperties::DragVelocitySmoothingFactor, 0.6);
    sp.setScrollMetric(QScrollerProperties::MinimumVelocity, 0.0);
    sp.setScrollMetric(QScrollerProperties::MaximumVelocity, 0.5);
    sp.setScrollMetric(QScrollerProperties::AcceleratingFlickMaximumTime, 0.4);
    sp.setScrollMetric(QScrollerProperties::AcceleratingFlickSpeedupFactor, 1.2);
    sp.setScrollMetric(QScrollerProperties::SnapPositionRatio, 0.2);
    sp.setScrollMetric(QScrollerProperties::MaximumClickThroughVelocity, 0);
    sp.setScrollMetric(QScrollerProperties::DragStartDistance, 0.001);
    sp.setScrollMetric(QScrollerProperties::MousePressEventDelay, 0.1);
    sp.setScrollMetric(QScrollerProperties::OvershootDragDistanceFactor, 0.1);
    sp.setScrollMetric(QScrollerProperties::OvershootScrollDistanceFactor, 0.1);
    QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
    QScroller* scroller = QScroller::scroller(ui->scrollArea);
    scroller->grabGesture(this, QScroller::LeftMouseButtonGesture);
    scroller->setScrollerProperties(sp);

    connect(ui->backPushButton, &QPushButton::clicked, this, [=] {
        Global::Page::goManagerPage(Global::Page::ACCOUNT);
    });
    connect(ui->previousPagePushButton, &QPushButton::clicked, this, [=] {
        ui->nextPagePushButton->setEnabled(true);
        currentShownPage--;
        page->clear();
        double tokenPrice = Global::TickerPrice::get("KAS");
        for( size_t i = currentShownPage * MAX_HISTORY_ENTRY_NR; i < (currentShownPage + 1) * MAX_HISTORY_ENTRY_NR; i++) {
            double a = (double)utxos->at(i).utxoEntryAmount / 100000000.0;
            page->append(a, a * tokenPrice, utxos->at(i).outpointTransactionId.c_str());
            page->setStyle();
        }
        page->repaint();
        ui->ofPagesLabel->setText(QString::asprintf("%lu of %lu", currentShownPage + 1, (utxos->size() / MAX_HISTORY_ENTRY_NR) + 1));
        if(currentShownPage == 0) {
            ui->previousPagePushButton->setEnabled(false);
            return;
        }
    });
    connect(ui->nextPagePushButton, &QPushButton::clicked, this, [=] {
        ui->previousPagePushButton->setEnabled(true);
        currentShownPage++;
        page->clear();
        double tokenPrice = Global::TickerPrice::get("KAS");
        size_t items = utxos->size();
        if((currentShownPage + 1) * MAX_HISTORY_ENTRY_NR < items)
            items = (currentShownPage + 1) * MAX_HISTORY_ENTRY_NR;
        for( size_t i = currentShownPage * MAX_HISTORY_ENTRY_NR; i < items; i++) {
            double a = (double)utxos->at(i).utxoEntryAmount / 100000000.0;
            page->append(a, a * tokenPrice, utxos->at(i).outpointTransactionId.c_str());
            page->setStyle();
        }
        page->repaint();
        ui->ofPagesLabel->setText(QString::asprintf("%lu of %lu", currentShownPage + 1, (utxos->size() / MAX_HISTORY_ENTRY_NR) + 1));
        if(currentShownPage == (utxos->size() / MAX_HISTORY_ENTRY_NR)) {
            ui->nextPagePushButton->setEnabled(false);
            return;
        }
    });

    Style::invertPushButtonIcon(ui->backPushButton, true);
    Style::invertPushButtonIcon(ui->previousPagePushButton, true);
    Style::invertPushButtonIcon(ui->nextPagePushButton, true);
}

PageHistory::~PageHistory() {
    delete ui;
}

void PageHistory::open(void *arg1) {
    utxos = (std::vector<gRPC::getUtxosByAddressesEntry_t> *)arg1;
    page->clear();
    double tokenPrice = Global::TickerPrice::get("KAS");
    for( size_t i = 0; i < utxos->size(); i++) {
        if(i > MAX_HISTORY_ENTRY_NR)
            break;
        double a = (double)utxos->at(i).utxoEntryAmount / 100000000.0;
        page->append(a, a * tokenPrice, utxos->at(i).outpointTransactionId.c_str());
        page->setStyle();
    }
    page->repaint();
    currentShownPage = 0;
    ui->ofPagesLabel->setText(QString::asprintf("1 of %lu", (utxos->size() / MAX_HISTORY_ENTRY_NR) + 1));
    ui->previousPagePushButton->setEnabled(false);
    ui->nextPagePushButton->setEnabled(true);
    ui->previousPagePushButton->setVisible(utxos->size() > MAX_HISTORY_ENTRY_NR);
    ui->ofPagesLabel->setVisible(utxos->size() > MAX_HISTORY_ENTRY_NR);
    ui->nextPagePushButton->setVisible(utxos->size() > MAX_HISTORY_ENTRY_NR);
    setScale();
}

void PageHistory::close() {

}

void PageHistory::setScale() {
    this->setGeometry(Global::Layout::getLayoutGeometryScaled());
    ui->backPushButton->setGeometry(Global::Layout::scaleRect(backPushButtonQRectBack));
    ui->backPushButton->setIconSize(Global::Layout::scaleSize(backPushButtonQSizeBack));
    ui->headerFrame->setGeometry(Global::Layout::scaleRect(headerFrameQRectBack));
    ui->titleLabel->setGeometry(Global::Layout::scaleRect(titleLabelQRectBack));
    ui->titleLabel->setFont(Global::Layout::scaleFontOffset(titleLabelQFontBack));
    ui->scrollArea->setGeometry(QRect(0, Global::Layout::scaleValueX(63), parent->geometry().width(),
                                      parent->geometry().height() - Global::Layout::scaleValueX(utxos ? (utxos->size() > MAX_HISTORY_ENTRY_NR ? 100 : 63) : 63) - Global::Layout::scaleValueX(9)));
    progressLabel->setGeometry(Global::Layout::scaleRect(progressMovieQRectBack));

    ui->previousPagePushButton->setGeometry(Global::Layout::scaleRect(previousPagePushButtonQRectBack));
    ui->previousPagePushButton->setIconSize(Global::Layout::scaleSize(previousPagePushButtonQSizeBack));
    ui->nextPagePushButton->setGeometry(Global::Layout::scaleRect(nextPagePushButtonQRectBack));
    ui->nextPagePushButton->setIconSize(Global::Layout::scaleSize(nextPagePushButtonQSizeBack));
    ui->ofPagesLabel->setGeometry(Global::Layout::scaleRect(ofPagesLabelQRectBack));
    ui->ofPagesLabel->setFont(Global::Layout::scaleFontOffset(ofPagesLabelQFontBack));
    ui->previousPagePushButton->setGeometry(QRect(Global::Layout::scaleValueX(70), this->geometry().height() - Global::Layout::scaleValueX(40),
                                      ui->previousPagePushButton->geometry().width(), ui->previousPagePushButton->geometry().height()));
    ui->ofPagesLabel->setGeometry(QRect(Global::Layout::scaleValueX(115), this->geometry().height() - Global::Layout::scaleValueX(40),
                                      ui->ofPagesLabel->geometry().width(), ui->ofPagesLabel->geometry().height()));
    ui->nextPagePushButton->setGeometry(QRect(Global::Layout::scaleValueX(200), this->geometry().height() - Global::Layout::scaleValueX(40),
                                      ui->nextPagePushButton->geometry().width(), ui->nextPagePushButton->geometry().height()));

    page->setScale();
}

void PageHistory::setStyle() {
    page->setStyle();
    Style::setButtontOnHeaderStyle(ui->backPushButton);
    Style::setFrameStyle(ui->headerFrame);
    Style::setTitleStyle(ui->titleLabel);
    ui->scrollArea->setStyleSheet(
                "background-color: transparent;"
                "border-width: 1px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + ";");
    Style::setButtonTransparentStyle(ui->previousPagePushButton);
    Style::setLabelStyle(ui->ofPagesLabel);
    Style::setButtonTransparentStyle(ui->nextPagePushButton);
}

void PageHistory::loop() {
    if(AccountListChangedCount != Global::Account::getAccountListChangedCount() ||
            SelectedAccountChangedCount != Global::Account::getSelectedAccountChangedCnt()/* ||
            network != Global::Network::getNetwork()*/) {
        AccountListChangedCount = Global::Account::getAccountListChangedCount();
        SelectedAccountChangedCount = Global::Account::getSelectedAccountChangedCnt();
        //network = Global::Network::getNetwork();
        //dexGetSupportedTokens();
    }
}
