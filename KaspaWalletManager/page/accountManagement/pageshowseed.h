#ifndef PAGESHOWSEED_H
#define PAGESHOWSEED_H

#include <QWidget>

#include <QRect>
#include <QFont>
#include <QSize>

namespace Ui {
class PageShowSeed;
}

class PageShowSeed : public QWidget
{
    Q_OBJECT

public:
    explicit PageShowSeed(QWidget *parent = nullptr);
    ~PageShowSeed();
    void open();
    void setScale();
    void setStyle();
    void setVisibility(bool v);
    bool getVisibility();

private:
    Ui::PageShowSeed *ui;
    QRect backPushButtonQRectBack;
    QSize backPushButtonQSizeBack;
    QRect headerLabelQRectBack;
    QFont headerLabelQFontBack;
    QRect word01LineEditQRectBack;
    QFont word01LineEditQFontBack;
    QRect word02LineEditQRectBack;
    QFont word02LineEditQFontBack;
    QRect word03LineEditQRectBack;
    QFont word03LineEditQFontBack;
    QRect word04LineEditQRectBack;
    QFont word04LineEditQFontBack;
    QRect word05LineEditQRectBack;
    QFont word05LineEditQFontBack;
    QRect word06LineEditQRectBack;
    QFont word06LineEditQFontBack;
    QRect word07LineEditQRectBack;
    QFont word07LineEditQFontBack;
    QRect word08LineEditQRectBack;
    QFont word08LineEditQFontBack;
    QRect word09LineEditQRectBack;
    QFont word09LineEditQFontBack;
    QRect word10LineEditQRectBack;
    QFont word10LineEditQFontBack;
    QRect word11LineEditQRectBack;
    QFont word11LineEditQFontBack;
    QRect word12LineEditQRectBack;
    QFont word12LineEditQFontBack;
    /*QRect word13LineEditQRectBack;
    QFont word13LineEditQFontBack;
    QRect word14LineEditQRectBack;
    QFont word14LineEditQFontBack;
    QRect word15LineEditQRectBack;
    QFont word15LineEditQFontBack;
    QRect word16LineEditQRectBack;
    QFont word16LineEditQFontBack;
    QRect word17LineEditQRectBack;
    QFont word17LineEditQFontBack;
    QRect word18LineEditQRectBack;
    QFont word18LineEditQFontBack;
    QRect word19LineEditQRectBack;
    QFont word19LineEditQFontBack;
    QRect word20LineEditQRectBack;
    QFont word20LineEditQFontBack;
    QRect word21LineEditQRectBack;
    QFont word21LineEditQFontBack;
    QRect word22LineEditQRectBack;
    QFont word22LineEditQFontBack;
    QRect word23LineEditQRectBack;
    QFont word23LineEditQFontBack;
    QRect word24LineEditQRectBack;
    QFont word24LineEditQFontBack;*/
    QRect copyAllPushButtonQRectBack;
    QFont copyAllPushButtonQFontBack;
    QRect nextPushButtonQRectBack;
    QFont nextPushButtonQFontBack;
};

#endif // PAGESHOWSEED_H
