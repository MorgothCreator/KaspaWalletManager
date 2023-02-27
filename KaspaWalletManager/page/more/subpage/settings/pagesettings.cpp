#include "pagesettings.h"
#include "QtWidgets/qstyleditemdelegate.h"
#include "ui_pagesettings.h"

#include <QPixmap>
#include <QStandardItemModel>

#include "global.h"
#include "color.h"
#include "style.h"
#include "storage/storagesettings.h"
#include "storage/storageinternal.h"

PageSettings::PageSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageSettings) {
    ui->setupUi(this);

    // Backup items geometry, size and font.
    backPushButtonQRectBack = ui->backPushButton->geometry();
    backPushButtonQSizeBack = ui->backPushButton->iconSize();
    headerFrameQRectBack = ui->headerFrame->geometry();
    titleLabelQRectBack = ui->titleLabel->geometry();
    titleLabelQFontBack = ui->titleLabel->font();

    languageComboBoxQRectBack = ui->languageComboBox->geometry();
    languageComboBoxQSizeBack = ui->languageComboBox->iconSize();
    languageComboBoxQFontBack = ui->languageComboBox->font();
    networkComboBoxQRectBack = ui->networkComboBox->geometry();
    networkComboBoxQSizeBack = ui->networkComboBox->iconSize();
    networkComboBoxQFontBack = ui->networkComboBox->font();
    scaleComboBoxQRectBack = ui->scaleComboBox->geometry();
    scaleComboBoxQSizeBack = ui->scaleComboBox->iconSize();
    scaleComboBoxQFontBack = ui->scaleComboBox->font();
    showSeedPushButtonQRectBack = ui->showSeedPushButton->geometry();
    showSeedPushButtonQSizeBack = ui->showSeedPushButton->iconSize();
    showSeedPushButtonQFontBack = ui->showSeedPushButton->font();
    backupWalletPushButtonQRectBack = ui->backupWalletPushButton->geometry();
    backupWalletPushButtonQSizeBack = ui->backupWalletPushButton->iconSize();
    backupWalletPushButtonQFontBack = ui->backupWalletPushButton->font();

    setStyle();
    setScale();

    ui->languageComboBox->setView(new QListView);
    ui->networkComboBox->setView(new QListView);
    ui->scaleComboBox->setView(new QListView);

    Style::invertPushButtonIcon(ui->backPushButton, true);
    Style::invertPushButtonIcon(ui->showSeedPushButton, true);
    Style::invertPushButtonIcon(ui->backupWalletPushButton, true);

    /*QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->networkComboBox->model());
    if(model) {
        QStandardItem *item = model->item(2);
        item->setEnabled(false);
    }*/

    connect(ui->scaleComboBox, &QComboBox::currentTextChanged, this, [=](QString s){
        if(!initialized)
            return;
        StorageSettings::genSet("windowScale", s.remove("Scale: "));
        QMessageBox::information(parent, "INFO", "To apply the new scale\n restart the application.");
    });
    initialized = true;
}

PageSettings::~PageSettings() {
    delete ui;
}

void PageSettings::open() {
    initialized = false;
    ui->languageComboBox->clear();
    ui->languageComboBox->setIconSize(QSize(20, 20));
    QListView *list = (QListView *)ui->languageComboBox->view();
    list->setSpacing(0);
    ui->languageComboBox->addItem(QPixmap(":/flag/res/flag/us.png"), "ENG");
    ui->networkComboBox->clear();
    ui->networkComboBox->addItems(networkNameList);
    ui->networkComboBox->setCurrentText(StorageSettings::get("network"));
    ui->scaleComboBox->clear();
    ui->scaleComboBox->addItems(QStringList({"Scale: 1.0", "Scale: 1.2", "Scale: 1.4", "Scale: 1.6", "Scale: 1.8", "Scale: 2.0"}));
    ui->scaleComboBox->setCurrentText("Scale: " + StorageSettings::genGet("windowScale", "1.0"));
    initialized = true;
}

void PageSettings::close() {

}

void PageSettings::setScale() {
    this->setGeometry(Global::Layout::getTabLayoutGeometryScaled());
    ui->backPushButton->setGeometry(Global::Layout::scaleRect(backPushButtonQRectBack));
    ui->backPushButton->setIconSize(Global::Layout::scaleSize(backPushButtonQSizeBack));
    ui->headerFrame->setGeometry(Global::Layout::scaleRect(headerFrameQRectBack));
    ui->titleLabel->setGeometry(Global::Layout::scaleRect(titleLabelQRectBack));
    ui->titleLabel->setFont(Global::Layout::scaleFontOffset(titleLabelQFontBack));

    ui->languageComboBox->setGeometry(Global::Layout::scaleRect(languageComboBoxQRectBack));
    ui->languageComboBox->setIconSize(Global::Layout::scaleSize(languageComboBoxQSizeBack));
    ui->languageComboBox->setFont(Global::Layout::scaleFontOffset(languageComboBoxQFontBack));
    QListView *list = (QListView *)ui->languageComboBox->view();
    list->setIconSize(Global::Layout::scaleSize(languageComboBoxQSizeBack));
    list->update();
    ui->networkComboBox->setGeometry(Global::Layout::scaleRect(networkComboBoxQRectBack));
    ui->networkComboBox->setIconSize(Global::Layout::scaleSize(networkComboBoxQSizeBack));
    ui->networkComboBox->setFont(Global::Layout::scaleFontOffset(networkComboBoxQFontBack));
    ui->scaleComboBox->setGeometry(Global::Layout::scaleRect(scaleComboBoxQRectBack));
    ui->scaleComboBox->setIconSize(Global::Layout::scaleSize(scaleComboBoxQSizeBack));
    ui->scaleComboBox->setFont(Global::Layout::scaleFontOffset(scaleComboBoxQFontBack));
    ui->showSeedPushButton->setGeometry(Global::Layout::scaleRect(showSeedPushButtonQRectBack));
    ui->showSeedPushButton->setIconSize(Global::Layout::scaleSize(showSeedPushButtonQSizeBack));
    ui->showSeedPushButton->setFont(Global::Layout::scaleFontOffset(showSeedPushButtonQFontBack));
    ui->backupWalletPushButton->setGeometry(Global::Layout::scaleRect(backupWalletPushButtonQRectBack));
    ui->backupWalletPushButton->setIconSize(Global::Layout::scaleSize(backupWalletPushButtonQSizeBack));
    ui->backupWalletPushButton->setFont(Global::Layout::scaleFontOffset(backupWalletPushButtonQFontBack));

}

void PageSettings::setStyle() {
    Style::setFrameStyle(ui->headerFrame);
    Style::setTitleStyle(ui->titleLabel);
    Style::setComboBoxStyle(ui->languageComboBox, languageComboBoxQFontBack);
    Style::setComboBoxStyle(ui->networkComboBox, networkComboBoxQFontBack);
    Style::setComboBoxStyle(ui->scaleComboBox, scaleComboBoxQFontBack);
    Style::setButtontOnHeaderStyle(ui->backPushButton);
    Style::setButtonTransparentAlignLeftStyle(ui->showSeedPushButton);
    Style::setButtonTransparentAlignLeftStyle(ui->backupWalletPushButton);
}

void PageSettings::loop() {

}

void PageSettings::on_backPushButton_clicked() {
    Global::Page::goManagerPage(Global::Page::MORE);
}


void PageSettings::on_languageComboBox_currentTextChanged(const QString &arg1){
    if(!initialized)
        return;
    StorageSettings::set("language", arg1);
}


void PageSettings::on_networkComboBox_currentIndexChanged(int index) {
    if(!initialized)
        return;
    Global::Network::setNetwork((networkName_e)index);
    StorageSettings::set("network", Global::Network::getNetworkName((networkName_e)index));
    Global::Page::goManagerPage(Global::Page::ACCOUNT);
}

void PageSettings::on_backupWalletPushButton_clicked() {
    StorageInternal::walletExport();
}

void PageSettings::on_showSeedPushButton_clicked() {
    Global::Page::goManagerPage(Global::Page::SHOW_SEED);
}

