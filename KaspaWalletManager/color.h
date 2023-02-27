#ifndef COLOR_H
#define COLOR_H

#include <QString>
#include <QPushButton>

#define COLOR_LIGHT_MAIN    "#005660"
#define COLOR_LIGHT_MAIN_BUTTON    "#005660"
#define COLOR_LIGHT_MAIN_BUTTON_BORDER    "#007670"
#define COLOR_LIGHT_MAIN_BUTTON_PRESSED    "#008680"
#define COLOR_LIGHT_MAIN_BUTTON_HOVER    "#007670"
#define COLOR_LIGHT_MAIN_LIGHTEN    "#006A75"
#define COLOR_LIGHT_BACKGROUND  COLOR_LIGHT_MAIN
#define COLOR_LIGHT_BACKGROUND2 COLOR_LIGHT_MAIN_BUTTON_HOVER
#define COLOR_LIGHT_BACKGROUND_ACC  COLOR_LIGHT_MAIN_BUTTON_HOVER
#define COLOR_LIGHT_ADDITIONAL  "#02C076"
#define COLOR_LIGHT_TEXT1   "#EEEEEE"
#define COLOR_LIGHT_TEXT2   "#CECECE"
#define COLOR_LIGHT_TEXT_DISABLED   "#8E8E8E"
#define COLOR_PLACEHOLDER1   "#8E8E8E"

#define COLOR_DARK_MAIN    "#FCD535"
#define COLOR_DARK_MAIN_LIGHTEN    "#E3BC1C"
#define COLOR_DARK_BACKGROUND  "#181A20"
#define COLOR_DARK_BACKGROUND2 "#0B0E11"
#define COLOR_DARK_BACKGROUND_ACC  "#111518"
#define COLOR_DARK_ADDITIONAL  "#02C076"
#define COLOR_DARK_TEXT1   "#EAECEF"
#define COLOR_DARK_TEXT2   "#B7BDC6"

class Color {
public:
    static QString getMain() {
        return COLOR_LIGHT_MAIN;
    }
    static QString getMainLighten() {
        return COLOR_LIGHT_MAIN_LIGHTEN;
    }
    static QString getBackground() {
        return COLOR_LIGHT_BACKGROUND;
    }
    static QString getBackground2() {
        return COLOR_LIGHT_BACKGROUND2;
    }
    static QString getBackgroundAcc() {
        return COLOR_LIGHT_BACKGROUND_ACC;
    }
    static QString getAdditional() {
        return COLOR_LIGHT_ADDITIONAL;
    }
    static QString getText1() {
        return COLOR_LIGHT_TEXT1;
    }
    static QString getText2() {
        return COLOR_LIGHT_TEXT2;
    }
};

#endif // COLOR_H
