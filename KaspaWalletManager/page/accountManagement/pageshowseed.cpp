#include "pageshowseed.h"
#include "ui_pageshowseed.h"

#include "style.h"
#include "global.h"
extern "C" {
#include "crypto/bip39.h"
}

PageShowSeed::PageShowSeed(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageShowSeed) {
    ui->setupUi(this);
    ui->ShowSeedFrame->setStyleSheet("background-color: #FCD535;");

    // Backup items geometry, size and font.
    backPushButtonQRectBack = ui->backPushButton->geometry();
    backPushButtonQSizeBack = ui->backPushButton->iconSize();
    headerLabelQRectBack = ui->headerLabel->geometry();
    headerLabelQFontBack = ui->headerLabel->font();
    word01LineEditQRectBack = ui->word01LineEdit->geometry();
    word01LineEditQFontBack = ui->word01LineEdit->font();
    word02LineEditQRectBack = ui->word02LineEdit->geometry();
    word02LineEditQFontBack = ui->word02LineEdit->font();
    word03LineEditQRectBack = ui->word03LineEdit->geometry();
    word03LineEditQFontBack = ui->word03LineEdit->font();
    word04LineEditQRectBack = ui->word04LineEdit->geometry();
    word04LineEditQFontBack = ui->word04LineEdit->font();
    word05LineEditQRectBack = ui->word05LineEdit->geometry();
    word05LineEditQFontBack = ui->word05LineEdit->font();
    word06LineEditQRectBack = ui->word06LineEdit->geometry();
    word06LineEditQFontBack = ui->word06LineEdit->font();
    word07LineEditQRectBack = ui->word07LineEdit->geometry();
    word07LineEditQFontBack = ui->word07LineEdit->font();
    word08LineEditQRectBack = ui->word08LineEdit->geometry();
    word08LineEditQFontBack = ui->word08LineEdit->font();
    word09LineEditQRectBack = ui->word09LineEdit->geometry();
    word09LineEditQFontBack = ui->word09LineEdit->font();
    word10LineEditQRectBack = ui->word10LineEdit->geometry();
    word10LineEditQFontBack = ui->word10LineEdit->font();
    word11LineEditQRectBack = ui->word11LineEdit->geometry();
    word11LineEditQFontBack = ui->word11LineEdit->font();
    word12LineEditQRectBack = ui->word12LineEdit->geometry();
    word12LineEditQFontBack = ui->word12LineEdit->font();
    /*word13LineEditQRectBack = ui->word13LineEdit->geometry();
    word13LineEditQFontBack = ui->word13LineEdit->font();
    word14LineEditQRectBack = ui->word14LineEdit->geometry();
    word14LineEditQFontBack = ui->word14LineEdit->font();
    word15LineEditQRectBack = ui->word15LineEdit->geometry();
    word15LineEditQFontBack = ui->word15LineEdit->font();
    word16LineEditQRectBack = ui->word16LineEdit->geometry();
    word16LineEditQFontBack = ui->word16LineEdit->font();
    word17LineEditQRectBack = ui->word17LineEdit->geometry();
    word17LineEditQFontBack = ui->word17LineEdit->font();
    word18LineEditQRectBack = ui->word18LineEdit->geometry();
    word18LineEditQFontBack = ui->word18LineEdit->font();
    word19LineEditQRectBack = ui->word19LineEdit->geometry();
    word19LineEditQFontBack = ui->word19LineEdit->font();
    word20LineEditQRectBack = ui->word20LineEdit->geometry();
    word20LineEditQFontBack = ui->word20LineEdit->font();
    word21LineEditQRectBack = ui->word21LineEdit->geometry();
    word21LineEditQFontBack = ui->word21LineEdit->font();
    word22LineEditQRectBack = ui->word22LineEdit->geometry();
    word22LineEditQFontBack = ui->word22LineEdit->font();
    word23LineEditQRectBack = ui->word23LineEdit->geometry();
    word23LineEditQFontBack = ui->word23LineEdit->font();
    word24LineEditQRectBack = ui->word24LineEdit->geometry();
    word24LineEditQFontBack = ui->word24LineEdit->font();*/
    copyAllPushButtonQRectBack = ui->copyAllPushButton->geometry();
    copyAllPushButtonQFontBack = ui->copyAllPushButton->font();
    nextPushButtonQRectBack = ui->nextPushButton->geometry();
    nextPushButtonQFontBack = ui->nextPushButton->font();

    setScale();
    setStyle();

    Style::invertPushButtonIcon(ui->backPushButton, true);

    connect(ui->backPushButton, &QPushButton::clicked, this, [=]{
        Global::Page::goManagerPage(Global::Page::MORE);
    });
}

PageShowSeed::~PageShowSeed() {
    delete ui;
}

void PageShowSeed::open() {
    QString pkStr = Global::Account::getAccount()->privateKey;
    QByteArray pk = signatures::decodePrivateKey(pkStr);
    std::vector<uint8_t> entropy;
    foreach( uint8_t b, pk.sliced(0, 16)) {
        entropy.push_back(b);
    }
    const char *m = mnemonic_generate(128);
    QString mnemonic = QString::fromLocal8Bit(m);
    QStringList wordList= mnemonic.split(' ');
    ui->word01LineEdit->setText(wordList.at(0));
    ui->word02LineEdit->setText(wordList.at(1));
    ui->word03LineEdit->setText(wordList.at(2));
    ui->word04LineEdit->setText(wordList.at(3));
    ui->word05LineEdit->setText(wordList.at(4));
    ui->word06LineEdit->setText(wordList.at(5));
    ui->word07LineEdit->setText(wordList.at(6));
    ui->word08LineEdit->setText(wordList.at(7));
    ui->word09LineEdit->setText(wordList.at(8));
    ui->word10LineEdit->setText(wordList.at(9));
    ui->word11LineEdit->setText(wordList.at(10));
    ui->word12LineEdit->setText(wordList.at(11));
    /*if(wordList.length() > 12) {
        ui->word13LineEdit->setText(wordList.at(12));
        ui->word14LineEdit->setText(wordList.at(13));
        ui->word15LineEdit->setText(wordList.at(14));
        ui->word16LineEdit->setText(wordList.at(15));
        ui->word17LineEdit->setText(wordList.at(16));
        ui->word18LineEdit->setText(wordList.at(17));
        ui->word19LineEdit->setText(wordList.at(18));
        ui->word20LineEdit->setText(wordList.at(19));
        ui->word21LineEdit->setText(wordList.at(20));
        ui->word22LineEdit->setText(wordList.at(21));
        ui->word23LineEdit->setText(wordList.at(22));
        ui->word24LineEdit->setText(wordList.at(23));
    }*/
}

void PageShowSeed::setScale() {
    this->setGeometry(Global::Layout::getLayoutGeometryScaled());
    QRect rect = Global::Layout::getLayoutGeometryScaled();
    rect.setY(rect.y() + Global::Layout::getHeaderHeight());
    ui->ShowSeedFrame->setGeometry(rect);

    ui->backPushButton->setGeometry(Global::Layout::scaleRect(backPushButtonQRectBack));
    ui->backPushButton->setIconSize(Global::Layout::scaleSize(backPushButtonQSizeBack));
    ui->headerLabel->setGeometry(Global::Layout::scaleRect(headerLabelQRectBack));
    ui->headerLabel->setFont(Global::Layout::scaleFont(headerLabelQFontBack));
    ui->word01LineEdit->setGeometry(Global::Layout::scaleRect(word01LineEditQRectBack));
    ui->word01LineEdit->setFont(Global::Layout::scaleFont(word01LineEditQFontBack));
    ui->word02LineEdit->setGeometry(Global::Layout::scaleRect(word02LineEditQRectBack));
    ui->word02LineEdit->setFont(Global::Layout::scaleFont(word02LineEditQFontBack));
    ui->word03LineEdit->setGeometry(Global::Layout::scaleRect(word03LineEditQRectBack));
    ui->word03LineEdit->setFont(Global::Layout::scaleFont(word03LineEditQFontBack));
    ui->word04LineEdit->setGeometry(Global::Layout::scaleRect(word04LineEditQRectBack));
    ui->word04LineEdit->setFont(Global::Layout::scaleFont(word04LineEditQFontBack));
    ui->word05LineEdit->setGeometry(Global::Layout::scaleRect(word05LineEditQRectBack));
    ui->word05LineEdit->setFont(Global::Layout::scaleFont(word05LineEditQFontBack));
    ui->word06LineEdit->setGeometry(Global::Layout::scaleRect(word06LineEditQRectBack));
    ui->word06LineEdit->setFont(Global::Layout::scaleFont(word06LineEditQFontBack));
    ui->word07LineEdit->setGeometry(Global::Layout::scaleRect(word07LineEditQRectBack));
    ui->word07LineEdit->setFont(Global::Layout::scaleFont(word07LineEditQFontBack));
    ui->word08LineEdit->setGeometry(Global::Layout::scaleRect(word08LineEditQRectBack));
    ui->word08LineEdit->setFont(Global::Layout::scaleFont(word08LineEditQFontBack));
    ui->word09LineEdit->setGeometry(Global::Layout::scaleRect(word09LineEditQRectBack));
    ui->word09LineEdit->setFont(Global::Layout::scaleFont(word09LineEditQFontBack));
    ui->word10LineEdit->setGeometry(Global::Layout::scaleRect(word10LineEditQRectBack));
    ui->word10LineEdit->setFont(Global::Layout::scaleFont(word10LineEditQFontBack));
    ui->word11LineEdit->setGeometry(Global::Layout::scaleRect(word11LineEditQRectBack));
    ui->word11LineEdit->setFont(Global::Layout::scaleFont(word11LineEditQFontBack));
    ui->word12LineEdit->setGeometry(Global::Layout::scaleRect(word12LineEditQRectBack));
    ui->word12LineEdit->setFont(Global::Layout::scaleFont(word12LineEditQFontBack));
    /*ui->word13LineEdit->setGeometry(Global::Layout::scaleRect(word13LineEditQRectBack));
    ui->word13LineEdit->setFont(Global::Layout::scaleFont(word13LineEditQFontBack));
    ui->word14LineEdit->setGeometry(Global::Layout::scaleRect(word14LineEditQRectBack));
    ui->word14LineEdit->setFont(Global::Layout::scaleFont(word14LineEditQFontBack));
    ui->word15LineEdit->setGeometry(Global::Layout::scaleRect(word15LineEditQRectBack));
    ui->word15LineEdit->setFont(Global::Layout::scaleFont(word15LineEditQFontBack));
    ui->word16LineEdit->setGeometry(Global::Layout::scaleRect(word16LineEditQRectBack));
    ui->word16LineEdit->setFont(Global::Layout::scaleFont(word16LineEditQFontBack));
    ui->word17LineEdit->setGeometry(Global::Layout::scaleRect(word17LineEditQRectBack));
    ui->word17LineEdit->setFont(Global::Layout::scaleFont(word17LineEditQFontBack));
    ui->word18LineEdit->setGeometry(Global::Layout::scaleRect(word18LineEditQRectBack));
    ui->word18LineEdit->setFont(Global::Layout::scaleFont(word18LineEditQFontBack));
    ui->word19LineEdit->setGeometry(Global::Layout::scaleRect(word19LineEditQRectBack));
    ui->word19LineEdit->setFont(Global::Layout::scaleFont(word19LineEditQFontBack));
    ui->word20LineEdit->setGeometry(Global::Layout::scaleRect(word20LineEditQRectBack));
    ui->word20LineEdit->setFont(Global::Layout::scaleFont(word20LineEditQFontBack));
    ui->word21LineEdit->setGeometry(Global::Layout::scaleRect(word21LineEditQRectBack));
    ui->word21LineEdit->setFont(Global::Layout::scaleFont(word21LineEditQFontBack));
    ui->word22LineEdit->setGeometry(Global::Layout::scaleRect(word22LineEditQRectBack));
    ui->word22LineEdit->setFont(Global::Layout::scaleFont(word22LineEditQFontBack));
    ui->word23LineEdit->setGeometry(Global::Layout::scaleRect(word23LineEditQRectBack));
    ui->word23LineEdit->setFont(Global::Layout::scaleFont(word23LineEditQFontBack));
    ui->word24LineEdit->setGeometry(Global::Layout::scaleRect(word24LineEditQRectBack));
    ui->word24LineEdit->setFont(Global::Layout::scaleFont(word24LineEditQFontBack));*/
    ui->copyAllPushButton->setGeometry(Global::Layout::scaleRect(copyAllPushButtonQRectBack));
    ui->copyAllPushButton->setFont(Global::Layout::scaleFont(copyAllPushButtonQFontBack));
    ui->nextPushButton->setGeometry(Global::Layout::scaleRect(nextPushButtonQRectBack));
    ui->nextPushButton->setFont(Global::Layout::scaleFont(nextPushButtonQFontBack));
}

void PageShowSeed::setStyle() {
    Style::setWidgetStyle(ui->ShowSeedFrame);
    Style::setButtontOnHeaderStyle(ui->backPushButton);
    Style::setLabelStyle(ui->headerLabel);
    Style::setLineEditManagerPageStyle(ui->word01LineEdit);
    Style::setLineEditManagerPageStyle(ui->word02LineEdit);
    Style::setLineEditManagerPageStyle(ui->word03LineEdit);
    Style::setLineEditManagerPageStyle(ui->word04LineEdit);
    Style::setLineEditManagerPageStyle(ui->word05LineEdit);
    Style::setLineEditManagerPageStyle(ui->word06LineEdit);
    Style::setLineEditManagerPageStyle(ui->word07LineEdit);
    Style::setLineEditManagerPageStyle(ui->word08LineEdit);
    Style::setLineEditManagerPageStyle(ui->word09LineEdit);
    Style::setLineEditManagerPageStyle(ui->word10LineEdit);
    Style::setLineEditManagerPageStyle(ui->word11LineEdit);
    Style::setLineEditManagerPageStyle(ui->word12LineEdit);
    /*Style::setLineEditManagerPageStyle(ui->word13LineEdit);
    Style::setLineEditManagerPageStyle(ui->word14LineEdit);
    Style::setLineEditManagerPageStyle(ui->word15LineEdit);
    Style::setLineEditManagerPageStyle(ui->word16LineEdit);
    Style::setLineEditManagerPageStyle(ui->word17LineEdit);
    Style::setLineEditManagerPageStyle(ui->word18LineEdit);
    Style::setLineEditManagerPageStyle(ui->word19LineEdit);
    Style::setLineEditManagerPageStyle(ui->word20LineEdit);
    Style::setLineEditManagerPageStyle(ui->word21LineEdit);
    Style::setLineEditManagerPageStyle(ui->word22LineEdit);
    Style::setLineEditManagerPageStyle(ui->word23LineEdit);
    Style::setLineEditManagerPageStyle(ui->word24LineEdit);*/
    Style::setButtonTransparentStyle(ui->copyAllPushButton);
    Style::setButtonTransparentStyle(ui->nextPushButton);
}

void PageShowSeed::setVisibility(bool v) {
    this->setVisible(v);
}

bool PageShowSeed::getVisibility() {
    return isVisible();
}
