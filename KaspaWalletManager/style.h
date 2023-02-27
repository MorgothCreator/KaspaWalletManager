#ifndef STYLE_H
#define STYLE_H

#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QFrame>
#include <QIcon>
#include <QPixmap>
#include <QImage>

#include "color.h"
#include "global.h"

#define DEFAULT_BORDER_RADIUS Global::Layout::scaleValue(10)
#define DEFAULT_BORDER_RADIUS_STR QString::number(DEFAULT_BORDER_RADIUS)
#define DEFAULT_H_PADDING Global::Layout::scaleValue(4)
#define DEFAULT_H_PADDING_STR QString::number(DEFAULT_H_PADDING)

#define DEFAULT_COLOR   QString(COLOR_LIGHT_TEXT1)
#define DEFAULT_BORDER_COLOR   QString(COLOR_LIGHT_MAIN_LIGHTEN)

class Style {
public:
    static void invertPushButtonIcon(QPushButton *button, bool invert) {
        if(invert) {
            QIcon icon = button->icon();
            QList<QSize> sizes = icon.availableSizes();
            QPixmap pixmap = icon.pixmap(sizes[0].width(), sizes[0].height());
            QImage i = pixmap.toImage();
            i.invertPixels(QImage::InvertMode::InvertRgb);
            pixmap = pixmap.fromImage(i);
            button->setIcon(QIcon(pixmap));
        }
    }
    static void setMainTabStyle(QTabWidget *tabWidget ) {
        tabWidget->setStyleSheet(
                    "QTabWidget::pane { /* The tab widget frame */"
                    "   border-top: " + QString::number(Global::Layout::scaleValue(2)) + "px solid " + Color::getMainLighten() +";"
                    "}"
                    "QTabWidget::tab-bar {"
                    "   left: 0px; /* move to the right by 5px */"
                    "}"
                    "/* Style the tab using the tab sub-control. Note that it reads QTabBar _not_ QTabWidget */"
                    "QTabBar::tab {"
                    "   background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 " + Color::getMainLighten() +", stop: 0.4 " + Color::getMain() +", stop: 0.5 " + Color::getMain() +", stop: 1.0 " + Color::getMainLighten() +");"
                    "   border: " + QString::number(Global::Layout::scaleValue(0)) + "px solid " + Color::getMainLighten() +";"
                    "   border-bottom-color: " + Color::getMainLighten() +"; /* same as the pane color */"
                    "   color: " + Color::getText2() +";"
                    "   border-top-left-radius: " + QString::number(Global::Layout::scaleValue(6)) + "px;"
                    "   border-top-right-radius: " + QString::number(Global::Layout::scaleValue(6)) + "px;"
                    "   min-width: " + QString::number(Global::Layout::scaleValue(PAGE_WIDTH / 2)) + "px;"
                    "   min-height: " + QString::number(Global::Layout::scaleValue(MENU_BAR_HEIGHT)) + "px;"
                    "   padding: 0px;"
                    "}"
                    "QTabBar::tab:selected, QTabBar::tab:hover {"
                    "   background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 " + Color::getMainLighten() +", stop: 0.4 " + Color::getMainLighten() +", stop: 0.5 " + Color::getMainLighten() +", stop: 1.0 " + Color::getMainLighten() +");"
                    "}"
                    "QTabBar::tab:selected {"
                    "   border-color: " + Color::getMain() + ";"
                    "   border-bottom-color: " + Color::getMainLighten() +"; /* same as pane color */"
                    "}"
                    "QTabBar::tab:!selected {"
                    "   margin-top: " + QString::number(Global::Layout::scaleValue(4)) + "px; /* make non-selected tabs look smaller */"
                    "}"
                    );
    }
#if 0
#define ON_MOBILE 0
#if defined(__APPLE__) || defined(Q_OS_ANDROID)
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE || defined(Q_OS_ANDROID)
#undef ON_MOBILE
#define ON_MOBILE 1
#endif
#endif
    static void setButtonStyle(QPushButton *button ) {
        button->setStyleSheet(
                    "QPushButton {"
                    "   background-color: " + Color::getMainLighten() + ";"
                    "   color: " + Color::getText2() + ";"
                    "   border-style: outset;"
                    "   border-width: " + QString::number(Global::Layout::scaleValue(1)) + "px;"
                    "   border-radius: " + QString::number(Global::Layout::scaleValue(6)) + "px;"
                    "   border-color: beige;"
                    // "   font: bold " + (char)Global::scaleValue(14 * FONT_OFFSET) + "px;"
                    // "   min-width: " + QString::number(Global::scaleValue(10)) + "em;"
                    "   padding: " + QString::number(Global::Layout::scaleValue(6)) + "px;"
                    "}"
                    "QPushButton::hover {"
                    "   background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 " + Color::getMain() +", stop: 0.4 " + Color::getMain() +", stop: 0.5 " + Color::getMain() +", stop: 1.0 " + Color::getMain() +");"
                    "}"
                    "QPushButton::pressed {"
#if ON_MOBILE
                   "   border-color: " + Color::getMainLighten() + ";"
                   // "   border-bottom-color: " + Color::getMainLighten() +"; /* same as pane color */"
                   "   background-color: " + Color::getMain() + ";"
#else
                    "   border-color: " + Color::getMain() + ";"
                    // "   border-bottom-color: " + Color::getMainLighten() +"; /* same as pane color */"
                    "   background-color: " + Color::getMainLighten() + ";"
#endif
                    "}");
    }
    static void setButtonRoundStyle(QPushButton *button ) {
        button->setStyleSheet(
                    "QPushButton {"
                    "   background-color: " + Color::getMainLighten() + ";"
                    "   color: " + Color::getText2() + ";"
                    "   border-style: solid;"
                    "   border-width: " + QString::number(Global::Layout::scaleValue(4)) + "px;"
                    "   border-radius: " + QString::number(Global::Layout::scaleValue(29)) + "px;"
                    "   border-color: " + Color::getBackgroundAcc() + ";"
                    "}"
                    "QPushButton::hover {"
                    "   background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 " + Color::getMain() +", stop: 0.4 " + Color::getMain() +", stop: 0.5 " + Color::getMain() +", stop: 1.0 " + Color::getMain() +");"
                    "}"
                    "QPushButton::pressed {"
#if ON_MOBILE
                   "   border-color: " + Color::getMainLighten() + ";"
                   // "   border-bottom-color: " + Color::getMainLighten() +"; /* same as pane color */"
                   "   background-color: " + Color::getMain() + ";"
#else
                    "   border-color: " + Color::getMain() + ";"
                    // "   border-bottom-color: " + Color::getMainLighten() +"; /* same as pane color */"
                    "   background-color: " + Color::getMainLighten() + ";"
#endif
                    "   border-style: solid;"
                    "   border-width: " + QString::number(Global::Layout::scaleValue(4)) + "px;"
                    "   border-color: " + Color::getBackgroundAcc() + ";"
                    "}");
    }
#endif
    static void setFrameStyle(QFrame *frame ) {
        frame->setStyleSheet(
                    "background-color: " + QString(COLOR_LIGHT_MAIN_BUTTON) + ";"
                    );
    }

    static void setTitleStyle(QLabel *label ) {
        label->setStyleSheet(
                    "color: " + DEFAULT_COLOR + ";"
                    "background-color: transparent;"
                    );
    }

    static void setWidgetStyle(QWidget *widget ) {
        widget->setStyleSheet(
                    "QWidget { border-style: solid; background-color: transparent; border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px;"
                    "border-width: 1px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + "; color: " + DEFAULT_COLOR + "; }"
                    );
    }

    static void setGroupBoxStyle(QGroupBox *groupBox ) {
        groupBox->setStyleSheet(
                                "border-style: solid; border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px; "
                                "border-width: 1px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + ";"
                    );
    }

    static void setButtonSendReceiveStyle(QPushButton *button ) {
        button->setStyleSheet(
                    "QPushButton { border-style: solid; background-color: " + QString(COLOR_LIGHT_MAIN_BUTTON) + "; border-radius: " + QString::number(Global::Layout::scaleValue(29)) + "px;"
                    "border-width: " + QString::number(Global::Layout::scaleValue(4)) + "px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + "; color: " + DEFAULT_COLOR + "; }"
                    "QPushButton:hover { background-color: rgba(0, 0, 0, 24); }"
                    "QPushButton:pressed { background-color: rgba(0, 0, 0, 64); }"
                    "QPushButton:disabled { color: rgba(142, 142, 142, 128); }"
                    );
    }
    static void setButtonTransparentStyle(QPushButton *button ) {
        button->setStyleSheet(
                    "QPushButton { border-style: solid; background-color: rgba(0, 0, 0, 8); border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px;"
                    "border-width: 1px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + "; color: " + DEFAULT_COLOR + "; }"
                    "QPushButton:hover { background-color: rgba(0, 0, 0, 24); }"
                    "QPushButton:pressed { background-color: rgba(0, 0, 0, 64); }"
                    "QPushButton:disabled { color: rgba(142, 142, 142, 128); }"
                    );
    }
    static void setButtonTransparentAlignLeftStyle(QPushButton *button ) {
        button->setStyleSheet(
                    "QPushButton { border-style: solid; background-color: rgba(0, 0, 0, 8); border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px;"
                    "border-width: 1px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + "; color: " + DEFAULT_COLOR + "; text-align:left; "
                    "padding-left: " + QString::number(Global::Layout::scaleValue(6)) + "px;}"
                    "QPushButton:hover { background-color: rgba(0, 0, 0, 24); }"
                    "QPushButton:pressed { background-color: rgba(0, 0, 0, 64); }"
                    "QPushButton:disabled { color: rgba(142, 142, 142, 128); }"
                    );
    }
    static void setButtontOnHeaderStyle(QPushButton *button) {
        button->setStyleSheet(
                    /*"QPushButton { border-style: solid; background-color: rgba(255, 255, 255, 16); border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px;"
                    "border-width: 1px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + "; color: " + DEFAULT_COLOR + "; }"
                    "QPushButton:hover { background-color: rgba(255, 255, 255, 64); }"
                    "QPushButton:pressed { background-color: rgba(255, 255, 255, 128); }"
                    "QPushButton:disabled { color: rgba(0, 0, 0, 128); }"*/
                    "QPushButton { border-style: solid; background-color: rgba(0, 0, 0, 8); border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px;"
                    "border-width: 1px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + "; color: " + DEFAULT_COLOR + "; }"
                    "QPushButton:hover { background-color: rgba(0, 0, 0, 24); }"
                    "QPushButton:pressed { background-color: rgba(0, 0, 0, 64); }"
                    "QPushButton:disabled { color: rgba(142, 142, 142, 128); }"
                    );
    }
    static void setButtonManagerPageStyle(QPushButton *button ) {
        button->setStyleSheet(
                    "QPushButton { border-style: solid; background-color: rgba(255, 255, 255, 16); border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px;"
                    "border-width: 1px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + "; color: " + DEFAULT_COLOR + "; }"
                    "QPushButton:hover { background-color: rgba(0, 0, 0, 24); }"
                    "QPushButton:pressed { background-color: rgba(0, 0, 0, 64); }"
                    "QPushButton:disabled { color: rgba(142, 142, 142, 128); }"
                    );
    }
    static void setLabelStyle(QLabel *label) {
        label->setStyleSheet(
                    "QLabel {"
                    "   background-color: transparent;"
                    "   border-color: transparent;"
                    "   color: " + DEFAULT_COLOR + ";"
                    "}"
                    );
    }
    static void setOnlineLabelStyle(QLabel *label) {
        label->setStyleSheet(
                    "QLabel {"
                    "   background-color: transparent;"
                    "   border-color: transparent;"
                    "   color: lightgreen;"
                    "}"
                    );
    }
    static void setOfflineLabelStyle(QLabel *label) {
        label->setStyleSheet(
                    "QLabel {"
                    "   background-color: transparent;"
                    "   border-color: transparent;"
                    "   color: red;"
                    "}"
                    );
    }
    static void setAditionalColorLabelStyle(QLabel *label) {
        label->setStyleSheet(
                    "QLabel {"
                    "   background-color: transparent;"
                    "   border-color: transparent;"
                    "   color: " COLOR_LIGHT_ADDITIONAL ";"
                    "}"
                    );
    }
    static void setLineEditManagerPageStyle(QLineEdit *label, QString textColor = DEFAULT_COLOR) {
        Q_UNUSED(textColor)
        label->setStyleSheet(
            "QLineEdit { border-style: solid; background-color: rgba(255, 255, 255, 16); border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px;"
            "border-width: 1px; border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + "; color: " + DEFAULT_COLOR + "; padding-left: " + DEFAULT_H_PADDING_STR + "px; padding-right: " + DEFAULT_H_PADDING_STR + "px; }"
            "QLineEdit[text=\"\"]{ color:" + QString(COLOR_PLACEHOLDER1) + "; }"
            );
    }
    static void setLineEditlWhiteStyle(QLineEdit *lineEdit, QString textColor = DEFAULT_COLOR) {
        Q_UNUSED(textColor)
        lineEdit->setStyleSheet(
                    "QLineEdit[text=\"\"]{ color: " + QString(COLOR_PLACEHOLDER1) + "; }"
                    "QLineEdit{ color:" + DEFAULT_COLOR + "; border-style: solid; border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px; border-width: 1px; "
                    "border-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_BORDER) + ";"
                    "padding-left: " + DEFAULT_H_PADDING_STR + "px; padding-right: " + DEFAULT_H_PADDING_STR + "px; }"
        );
    }
    // Actualised
    static void setComboBoxStyle(QComboBox *combobox, QFont backupFont) {
        combobox->setStyleSheet(
                    "QComboBox { background-color: rgba(0, 0, 0, 0); color:" + DEFAULT_COLOR + "; border: 1px solid " + DEFAULT_BORDER_COLOR + "; border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px; "
                    "padding: 1px 18px 1px 3px; min-width: 6em; padding-left: " + QString::number(Global::Layout::scaleValue(12)) + "px; }"
                    "QComboBox QAbstractItemView { outline: none; }"
                    "QComboBox:on { padding-top: 3px; padding-left: 4px; }"
                    "QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: top right; width: " + QString::number(Global::Layout::scaleValue(20)) + "px; border-left-width: 1px;"
                    "border-left-color: darkgray; border-left-style: solid; /* just a single line */ border-top-right-radius: " + DEFAULT_BORDER_RADIUS_STR + "px; /* same radius as the QComboBox */"
                    "border-bottom-right-radius: " + DEFAULT_BORDER_RADIUS_STR + "px; }"
                    "QComboBox::drop-down::hover { background-color: rgba(0, 0, 0, 16); }"
                    "QComboBox::drop-down::pressed { background-color: rgba(0, 0, 0, 64); }"
                    "QComboBox::down-arrow { image: url(:/res/ic/res/ic/dropDownArrow.png); width: " + QString::number(Global::Layout::scaleValue(12)) + "px; height: " + QString::number(Global::Layout::scaleValue(12)) + "px; }"
                    "QComboBox::down-arrow:on { /* shift the arrow when popup is open */ top: 1px; left: 1px; }"
                    "QListView { /*font-family: Times New Roman; font-style: italic; */font-size: " + QString::number(Global::Layout::scaleFontOffset(backupFont).pointSize()) +  "pt; /*font-weight: bold;*/ }"
                    "QListView::item { height: " + QString::number(Global::Layout::scaleValue(31)) + "px; background-color: " + QString(COLOR_LIGHT_MAIN_BUTTON) + "; color: " + DEFAULT_COLOR + "; padding-left: " + QString::number(Global::Layout::scaleValue(12)) + "px; }"
                    "QListView::item:selected:!active, QListView::item:selected:active { background-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_PRESSED) + "; color: " + DEFAULT_COLOR + "; }"
                    "QListView::item::hover { background-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_HOVER) + "; /*font: url(:/Resources/Fonts/GameJam.ttf);*/ color: " + DEFAULT_COLOR + "; }"
                    );
        combobox->update();
    }
    static void setComboBoxSmallStyle(QComboBox *combobox, QFont backupFont) {
        combobox->setStyleSheet(
                    "QComboBox { border: 1px solid " + DEFAULT_BORDER_COLOR + "; border-radius: " + DEFAULT_BORDER_RADIUS_STR + "px; "
                    "padding: 1px 18px 1px 3px; min-width: 6em; color:black; }"
                    "QComboBox:on { /* shift the text when the popup opens */ padding-top: 3px; padding-left: 4px; }"
                    "QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: top right; width: " + QString::number(Global::Layout::scaleValue(20)) + "px; border-left-width: 1px;"
                    "border-left-color: darkgray; border-left-style: solid; /* just a single line */ border-top-right-radius: " + DEFAULT_BORDER_RADIUS_STR + "px; /* same radius as the QComboBox */"
                    "border-bottom-right-radius: " + DEFAULT_BORDER_RADIUS_STR + "px; }"
                    "QComboBox::drop-down::hover { background-color: rgba(0, 0, 0, 16); }"
                    "QComboBox::drop-down::pressed { background-color: rgba(0, 0, 0, 64); }"
                    "QComboBox::down-arrow { image: url(:/res/ic/res/ic/dropDownArrow.png); width: " + QString::number(Global::Layout::scaleValue(12)) + "px; height: " + QString::number(Global::Layout::scaleValue(12)) + "px; }"
                    "QComboBox::down-arrow:on { /* shift the arrow when popup is open */ top: 1px; left: 1px; }"
                    "QListView { /*font-family: Times New Roman; font-style: italic; */font-size: " + QString::number(Global::Layout::scaleFontOffset(backupFont).pointSize()) +  "pt; /*font-weight: bold;*/ }"
                    "QListView::item { height: " + QString::number(Global::Layout::scaleValue(31)) + "px; background-color: " + QString(COLOR_LIGHT_MAIN_BUTTON) + "; color: " + DEFAULT_COLOR + "; }"
                    "QListView::item:selected:!active, QListView::item:selected:active { background-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_PRESSED) + "; color: " + DEFAULT_COLOR + "; }"
                    "QListView::item::hover { background-color: " + QString(COLOR_LIGHT_MAIN_BUTTON_HOVER) + "; /*font: url(:/Resources/Fonts/GameJam.ttf);*/ color: " + DEFAULT_COLOR + "; padding-left: " + QString::number(Global::Layout::scaleValue(3)) + "px; }"
                    );
        combobox->update();
    }
};

#endif // STYLE_H
