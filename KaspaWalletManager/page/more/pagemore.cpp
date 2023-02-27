#include "pagemore.h"
#include "ui_pagemore.h"

#include <QList>
#include <QStyle>

#include "global.h"
#include "color.h"
#include "style.h"
#include "storage/storagesettings.h"

PageMore::PageMore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageMore) {
    ui->setupUi(this);

    // Backup items geometry, size and font.
    headerFrameQRectBack = ui->headerFrame->geometry();
    titleLabelQRectBack = ui->titleLabel->geometry();
    titleLabelQFontBack = ui->titleLabel->font();

    accountsComboBoxQRectBack = ui->accountsComboBox->geometry();
    accountsComboBoxQSizeBack = ui->accountsComboBox->iconSize();
    accountsComboBoxQFontBack = ui->accountsComboBox->font();
    explorerPushButtonQRectBack = ui->explorerPushButton->geometry();
    explorerPushButtonQSizeBack = ui->explorerPushButton->iconSize();
    explorerPushButtonQFontBack = ui->explorerPushButton->font();
    newAccountPushButtonQRectBack = ui->newAccountPushButton->geometry();
    newAccountPushButtonQSizeBack = ui->newAccountPushButton->iconSize();
    newAccountPushButtonQFontBack = ui->newAccountPushButton->font();
    settingsPushButtonQRectBack = ui->settingsPushButton->geometry();
    settingsPushButtonQSizeBack = ui->settingsPushButton->iconSize();
    settingsPushButtonQFontBack = ui->settingsPushButton->font();
    aboutUsPushButtonQRectBack = ui->aboutUsPushButton->geometry();
    aboutUsPushButtonQSizeBack = ui->aboutUsPushButton->iconSize();
    aboutUsPushButtonQFontBack = ui->aboutUsPushButton->font();
    advancedFunctionsPushButtonQRectBack = ui->advancedFunctionsPushButton->geometry();
    advancedFunctionsPushButtonQSizeBack = ui->advancedFunctionsPushButton->iconSize();
    advancedFunctionsPushButtonQFontBack = ui->advancedFunctionsPushButton->font();


    setStyle();
    setScale();

    Style::invertPushButtonIcon(ui->newAccountPushButton, true);
    Style::invertPushButtonIcon(ui->explorerPushButton, true);
    Style::invertPushButtonIcon(ui->settingsPushButton, true);
    Style::invertPushButtonIcon(ui->aboutUsPushButton, true);
    Style::invertPushButtonIcon(ui->advancedFunctionsPushButton, true);

    ui->accountsComboBox->setView(new QListView);

    ui->advancedFunctionsPushButton->setVisible(false);

    initialized = true;
}

PageMore::~PageMore() {
    delete ui;
}

void PageMore::open() {
    QList<Global::Account::account_t> accList = Global::Account::getAccountList();
    Global::Account::account_t acc;
    initialized = false;
    ui->accountsComboBox->clear();
    foreach(acc, accList){
        ui->accountsComboBox->addItem(acc.accountName);
    }
    ui->accountsComboBox->setCurrentText(Global::Account::getAccountName());
    initialized = true;
}

void PageMore::close() {

}

void PageMore::setScale() {
    this->setGeometry(Global::Layout::getTabLayoutGeometryScaled());
    ui->headerFrame->setGeometry(Global::Layout::scaleRect(headerFrameQRectBack));
    ui->titleLabel->setGeometry(Global::Layout::scaleRect(titleLabelQRectBack));
    ui->titleLabel->setFont(Global::Layout::scaleFontOffset(titleLabelQFontBack));

    ui->accountsComboBox->setGeometry(Global::Layout::scaleRect(accountsComboBoxQRectBack));
    ui->accountsComboBox->setIconSize(Global::Layout::scaleSize(accountsComboBoxQSizeBack));
    ui->accountsComboBox->setFont(Global::Layout::scaleFontOffset(accountsComboBoxQFontBack));
    ui->explorerPushButton->setGeometry(Global::Layout::scaleRect(explorerPushButtonQRectBack));
    ui->explorerPushButton->setIconSize(Global::Layout::scaleSize(explorerPushButtonQSizeBack));
    ui->explorerPushButton->setFont(Global::Layout::scaleFontOffset(explorerPushButtonQFontBack));
    ui->newAccountPushButton->setGeometry(Global::Layout::scaleRect(newAccountPushButtonQRectBack));
    ui->newAccountPushButton->setIconSize(Global::Layout::scaleSize(newAccountPushButtonQSizeBack));
    ui->newAccountPushButton->setFont(Global::Layout::scaleFontOffset(newAccountPushButtonQFontBack));
    ui->settingsPushButton->setGeometry(Global::Layout::scaleRect(settingsPushButtonQRectBack));
    ui->settingsPushButton->setIconSize(Global::Layout::scaleSize(settingsPushButtonQSizeBack));
    ui->settingsPushButton->setFont(Global::Layout::scaleFontOffset(settingsPushButtonQFontBack));
    ui->aboutUsPushButton->setGeometry(Global::Layout::scaleRect(aboutUsPushButtonQRectBack));
    ui->aboutUsPushButton->setIconSize(Global::Layout::scaleSize(aboutUsPushButtonQSizeBack));
    ui->aboutUsPushButton->setFont(Global::Layout::scaleFontOffset(aboutUsPushButtonQFontBack));
    ui->advancedFunctionsPushButton->setGeometry(Global::Layout::scaleRect(advancedFunctionsPushButtonQRectBack));
    ui->advancedFunctionsPushButton->setIconSize(Global::Layout::scaleSize(advancedFunctionsPushButtonQSizeBack));
    ui->advancedFunctionsPushButton->setFont(Global::Layout::scaleFontOffset(advancedFunctionsPushButtonQFontBack));

    //listView->setFont(Global::Layout::scaleFontOffset(accountsComboBoxQFontBack));
}

void PageMore::setStyle() {
    Style::setFrameStyle(ui->headerFrame);
    Style::setTitleStyle(ui->titleLabel);
    Style::setComboBoxStyle(ui->accountsComboBox, accountsComboBoxQFontBack);
    Style::setButtonTransparentAlignLeftStyle(ui->newAccountPushButton);
    Style::setButtonTransparentAlignLeftStyle(ui->explorerPushButton);
    Style::setButtonTransparentAlignLeftStyle(ui->settingsPushButton);
    Style::setButtonTransparentAlignLeftStyle(ui->aboutUsPushButton);
    Style::setButtonTransparentAlignLeftStyle(ui->advancedFunctionsPushButton);
}

void PageMore::loop() {
    if(AccountListChangedCount != Global::Account::getAccountListChangedCount()) {
        AccountListChangedCount = Global::Account::getAccountListChangedCount();
    }
}

void PageMore::on_explorerPushButton_clicked() {

}

void PageMore::on_newAccountPushButton_clicked() {
    Global::Page::goManagerPage(Global::Page::NEW_ACCOUNT);
}

void PageMore::on_accountsComboBox_currentTextChanged(const QString &arg1) {
    if(initialized && arg1.length() != 0) {
        Global::Account::setSelectedAccount(arg1);
        StorageSettings::set("lastAccount", arg1);
    }
}

void PageMore::on_settingsPushButton_clicked() {
    Global::Page::goManagerPage(Global::Page::SETTINGS);
}

