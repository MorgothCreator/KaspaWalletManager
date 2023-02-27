#include "pagereceive.h"
#include "ui_pagereceive.h"

#include <QPicture>
#include <QClipboard>
#include <QGraphicsOpacityEffect>

#include "style.h"
#include "global.h"
#include "extensions/qrcodegen.h"
#include "translate/translate.h"

PageReceive::PageReceive(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageReceive)
{
    ui->setupUi(this);
    setStyle();
    ui->copiedLabel->setVisible(false);

    // Backup items geometry, size and font.
    backPushButtonQRectBack = ui->backPushButton->geometry();
    backPushButtonQSizeBack = ui->backPushButton->iconSize();
    headerFrameQRectBack = ui->headerFrame->geometry();
    titleLabelQRectBack = ui->titleLabel->geometry();
    titleLabelQFontBack = ui->titleLabel->font();

    accountsComboBoxQRectBack = ui->accountsComboBox->geometry();
    accountsComboBoxQSizeBack = ui->accountsComboBox->iconSize();
    accountsComboBoxQFontBack = ui->accountsComboBox->font();
    addressGroupBoxQRectBack = ui->addressGroupBox->geometry();
    addressGroupBoxQFontBack = ui->addressGroupBox->font();
    qrLabelQRectBack = ui->qrLabel->geometry();
    copyAddressHorizontalLayoutQRectBack = ui->horizontalFrame->geometry();
    addressLabelQFontBack = ui->addressLabel->font();
    copyAddressPushButtonQRectBack = ui->copyAddressPushButton->geometry();
    copyAddressPushButtonQSizeBack = ui->copyAddressPushButton->iconSize();

    copiedLabelQRectBack = ui->copiedLabel->geometry();
    copiedLabelQFontBack = ui->copiedLabel->font();

    setScale();

    ui->accountsComboBox->setView(new QListView);

    Style::invertPushButtonIcon(ui->backPushButton, true);
    //Style::invertPushButtonIcon(ui->copyAddressPushButton, true);

    connect(ui->backPushButton, &QPushButton::clicked, this, [=]{
        Global::Page::goManagerPage(Global::Page::ACCOUNT);
        close();
    });
    connect(ui->copyAddressPushButton, &QPushButton::clicked, this, [=]{
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(Global::Account::getAccountPublicId());
        fadeCount = FADE_COUNT_START_VALE;
        fadeTimer.start();
    });
    connect(ui->accountsComboBox, &QComboBox::currentIndexChanged, this, [=](int index) {
        if(index < 0 || lockAccountsComboBox == true)
            return;
        if(index == addrList.length() - 1) {
            //addrList.insert(addrList.length() - 1,"kaspa:");
            ui->accountsComboBox->clear();
            for(QString addr: addrList)
                ui->accountsComboBox->addItem(Global::Util::truncateIdHash(addr, 28));
            ui->accountsComboBox->setCurrentIndex(addrList.length() - 2);
            return;
        }
        showQr(addrList.at(index).toLocal8Bit());
    });
    connect(&fadeTimer, &QTimer::timeout, this, [=]{
        if(fadeCount == FADE_COUNT_START_VALE)
            ui->copiedLabel->setVisible(true);
        double opacity = 0;
        if(fadeCount == 0) {
            opacity = 0.0;
            ui->copiedLabel->setVisible(false);
            fadeTimer.stop();
        } else  if(fadeCount < 100) {
            opacity = (double)fadeCount / 100.0;
            fadeCount--;
        } else {
            opacity = 1.0;
            fadeCount--;
        }
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
        effect->setOpacity(opacity);
        ui->copiedLabel->setGraphicsEffect(effect);
    });
    ui->accountsComboBox->setEnabled(false);
    fadeTimer.setInterval(20);
    fadeTimer.stop();
}

PageReceive::~PageReceive()
{
    delete ui;
}

void PageReceive::open(void *arg1) {
    addrList.clear();
    addrList.append(((QStringList *) arg1)->toList());
    //addrList.append(Translate::tr("New address"));
    lockAccountsComboBox = true;
    ui->accountsComboBox->clear();
    for(int i = 0; i < addrList.length(); i++) {
        ui->accountsComboBox->addItem(Global::Util::truncateIdHash(addrList.at(i).toLocal8Bit(), 28));
    }
    lockAccountsComboBox = false;
    if(addrList.length() >= 1)
        showQr(addrList.at(0).toLocal8Bit());
}

void PageReceive::close() {

}

void PageReceive::setScale() {
    /*double scale = Global::Layout::labelFontScale();*/
    this->setGeometry(Global::Layout::getLayoutGeometryScaled());

    ui->backPushButton->setGeometry(Global::Layout::scaleRect(backPushButtonQRectBack));
    ui->backPushButton->setIconSize(Global::Layout::scaleSize(backPushButtonQSizeBack));
    ui->headerFrame->setGeometry(Global::Layout::scaleRect(headerFrameQRectBack));
    ui->titleLabel->setGeometry(Global::Layout::scaleRect(titleLabelQRectBack));
    ui->titleLabel->setFont(Global::Layout::scaleFontOffset(titleLabelQFontBack));

    ui->accountsComboBox->setGeometry(Global::Layout::scaleRect(accountsComboBoxQRectBack));
    ui->accountsComboBox->setIconSize(Global::Layout::scaleSize(accountsComboBoxQSizeBack));
    ui->accountsComboBox->setFont(Global::Layout::scaleFontOffset(accountsComboBoxQFontBack));
    ui->addressGroupBox->setGeometry(Global::Layout::scaleRect(addressGroupBoxQRectBack));
    ui->addressGroupBox->setFont(Global::Layout::scaleFontOffset(addressGroupBoxQFontBack));
    ui->qrLabel->setGeometry(Global::Layout::scaleRect(qrLabelQRectBack));
    ui->horizontalFrame->setGeometry(Global::Layout::scaleRect(copyAddressHorizontalLayoutQRectBack));
    ui->addressLabel->setFont(Global::Layout::scaleFontOffset(addressLabelQFontBack));
    ui->copyAddressPushButton->setGeometry(Global::Layout::scaleRect(copyAddressPushButtonQRectBack));
    ui->copyAddressPushButton->setIconSize(Global::Layout::scaleSize(copyAddressPushButtonQSizeBack));

    ui->copiedLabel->setGeometry(Global::Layout::scaleRect(copiedLabelQRectBack));;
    ui->copiedLabel->setFont(Global::Layout::scaleFontOffset(copiedLabelQFontBack));
}

void PageReceive::setStyle() {
    Style::setGroupBoxStyle(ui->addressGroupBox);
    Style::setButtontOnHeaderStyle(ui->backPushButton);
    Style::setFrameStyle(ui->headerFrame);
    Style::setComboBoxStyle(ui->accountsComboBox, accountsComboBoxQFontBack);
    Style::setTitleStyle(ui->titleLabel);
    Style::setButtonTransparentStyle(ui->copyAddressPushButton);
}

void PageReceive::loop() {

}

void PageReceive::showQr(QString addr) {
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    bool ok = qrcodegen_encodeText(addr.toUtf8(), tempBuffer, qrcode,
        qrcodegen_Ecc_MEDIUM, qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
    QImage image;
    if (ok) {
        QSize size(qrcodegen_getSize(qrcode), qrcodegen_getSize(qrcode));
        image = QImage(size.width(), size.height(), QImage::Format_ARGB32);
        for(int i=0; i<size.width(); i++)
            for(int j=0; j<size.height(); j++)
                image.setPixel(i, j, qrcodegen_getModule(qrcode, i, j) ?
                                   qRgb(0,0,0) :
                                   qRgb(255,255,255));

        image = image.scaled(240, 240);
        QZXingImageProvider::getInstance()->storeImage(image);
    }
    ui->qrLabel->setPixmap(QPixmap::fromImage(image));
    ui->qrLabel->setScaledContents(true);
    ui->addressLabel->setText(Global::Util::truncateIdHash(addr, 27));
}

