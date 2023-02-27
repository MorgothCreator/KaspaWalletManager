
#include "pageaccountitemdelegate.h"
#include "pageaccountitemdelegateprivate.h"
#include <QPainter>

#include "global.h"
#include "style.h"

PageAccountItemDelegate::PageAccountItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent),
    m_ptr(new PageAccountItemDelegatePrivate)
{

}

PageAccountItemDelegate::~PageAccountItemDelegate()
{
    delete m_ptr;
}

QSize PageAccountItemDelegate::iconSize() const
{
    return m_ptr->iconSize;
}

void PageAccountItemDelegate::setIconSize(int width, int height)
{
    m_ptr->iconSize = QSize(width, height);
}

QMargins PageAccountItemDelegate::contentsMargins() const
{
    return m_ptr->margins;
}

void PageAccountItemDelegate::setContentsMargins(int left, int top, int right, int bottom)
{
    m_ptr->margins = QMargins(left, top, right, bottom);
}

int PageAccountItemDelegate::horizontalSpacing() const
{
    return m_ptr->spacingHorizontal;
}

void PageAccountItemDelegate::setHorizontalSpacing(int spacing)
{
    m_ptr->spacingHorizontal = spacing;
}

int PageAccountItemDelegate::verticalSpacing() const
{
    return m_ptr->spacingVertical;
}

void PageAccountItemDelegate::setVerticalSpacing(int spacing)
{
    m_ptr->spacingVertical = spacing;
}

void PageAccountItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                     const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);

    const QPalette &palette(opt.palette);
    const QRect &rect(opt.rect);
    const QRect &contentRect(rect.adjusted(m_ptr->margins.left(),
                                               m_ptr->margins.top(),
                                               -m_ptr->margins.right(),
                                               -m_ptr->margins.bottom()));
    const bool lastIndex = (index.model()->rowCount() - 1) == index.row();
    const bool hasIcon = !opt.icon.isNull();
    const int bottomEdge = rect.bottom();
    QFont f(opt.font);

    f.setPointSize(m_ptr->timestampFontPointSize(opt.font));

    painter->save();
    painter->setClipping(true);
    painter->setClipRect(rect);
    painter->setFont(opt.font);

    // Draw background
    //painter->fillRect(rect, /*opt.state & QStyle::State_Selected ?
    //                      palette.highlight().color() :*/
    //                      palette.light().color());
    painter->setBrush(palette.light().color());
    //painter->drawRoundedRect(rect, DEFAULT_BORDER_RADIUS, DEFAULT_BORDER_RADIUS);

    // Draw bottom line
    painter->setPen(lastIndex ? palette.dark().color()
                              : QColor(COLOR_LIGHT_MAIN_LIGHTEN));
    painter->drawLine(lastIndex ? rect.left() : m_ptr->margins.left(),
                      bottomEdge,
                      lastIndex ? rect.right() : contentRect.right(),
                      bottomEdge);

    QList<QString> values = index.data(Qt::UserRole).toString().split("\r");
    // Draw item icon
    if (hasIcon)
        painter->drawPixmap(contentRect.left(), contentRect.top(),
                            opt.icon.pixmap(m_ptr->iconSize));

    // Draw ""Address:" text
    QRect addrRect(0, 0, contentRect.right(), f.pointSizeF() * 1.5/*m_ptr->tickerBox(opt)*/);

    addrRect.moveTo(m_ptr->margins.left() + (hasIcon ? m_ptr->iconSize.width() : 0)
                         + m_ptr->spacingHorizontal - 5, contentRect.top());

    //f.setPointSizeF(PageAccountItemDelegatePrivate::timestampFontPointSize(option.font));
    painter->setFont(f);
    painter->setPen(palette.highlightedText().color());
    painter->drawText(addrRect, Qt::TextWrapAnywhere,
                      "Address:");

    // Draw Address
    QRect addrValueRect(0, 0, contentRect.right() - (m_ptr->spacingHorizontal * 2), f.pointSize() * 3/*m_ptr->tickerBox(opt)*/);

    addrValueRect.moveTo(m_ptr->margins.left() + (hasIcon ? m_ptr->iconSize.width() : 0)
                         + m_ptr->spacingHorizontal, addrRect.bottom());

    //f.setPointSizeF(PageAccountItemDelegatePrivate::timestampFontPointSize(option.font));
    painter->setFont(f);
    painter->setPen(palette.text().color());
    painter->drawText(addrValueRect, Qt::TextWrapAnywhere,
                      values.at(4)/*opt.text*/);

    // Draw "Amount:" text
    QRect amountRect(0, 0, contentRect.right(), f.pointSizeF() * 1.5);

    amountRect.moveTo(m_ptr->margins.left() + (hasIcon ? m_ptr->iconSize.width() : 0)
                         + m_ptr->spacingHorizontal - 5, addrValueRect.bottom());

    //f.setPointSizeF(PageAccountItemDelegatePrivate::timestampFontPointSize(option.font));
    painter->setFont(f);
    painter->setPen(palette.highlightedText().color());
    painter->drawText(amountRect, Qt::TextWrapAnywhere,
                      "Amount:");

    // Draw Amount
    QRect amountValueRect(0, 0, contentRect.right() - (m_ptr->spacingHorizontal * 2), f.pointSize() * 1.5);

    amountValueRect.moveTo(m_ptr->margins.left() + (hasIcon ? m_ptr->iconSize.width() : 0)
                         + m_ptr->spacingHorizontal, amountRect.bottom());

    //f.setPointSizeF(PageAccountItemDelegatePrivate::timestampFontPointSize(option.font));
    painter->setFont(f);
    painter->setPen(palette.text().color());
    painter->drawText(amountValueRect, Qt::TextWrapAnywhere,
                      values.at(0) + " KAS");

    // Draw value text
    QString txt = "= $" + values.at(1);
    QRect valueRect(m_ptr->valueBox(opt, txt));

    valueRect.moveTo(contentRect.right() - valueRect.width(), amountRect.bottom());

    //f.setPointSizeF(PageAccountItemDelegatePrivate::timestampFontPointSize(option.font));
    painter->setFont(f);
    painter->setPen(palette.highlightedText().color());
    painter->drawText(valueRect, Qt::TextSingleLine, txt);

    painter->restore();
}

QSize PageAccountItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);

    //int textHeight = m_ptr->tickerBox(opt).height()
            //+ m_ptr->spacingVertical + m_ptr->messageBox(opt).height();
    /*int iconHeight = m_ptr->iconSize.height();
    //int h = textHeight > iconHeight ? textHeight : iconHeight;*/
    int h = (m_ptr->tickerBox(opt).height() * 1.5 * 2) + (m_ptr->tickerBox(opt).height() * 3 * 1);

    return QSize(opt.rect.width(), m_ptr->margins.top() + h
                 + m_ptr->margins.bottom());
}

PageAccountItemDelegatePrivate::PageAccountItemDelegatePrivate() :
    iconSize(16, 16),
    margins(0, 0, 0, 0),
    spacingHorizontal(0),
    spacingVertical(0)
{

}

QRect PageAccountItemDelegatePrivate::tickerBox(const QStyleOptionViewItem &option) const
{
    QFont f(option.font);

    f.setPointSizeF(timestampFontPointSize(option.font));

    return QFontMetrics(f).boundingRect(option.text)
            .adjusted(0, 0, 1, 1);
}

QRect PageAccountItemDelegatePrivate::nameBox(const QStyleOptionViewItem &option,
                             QString str) const
{
    QFont f(option.font);

    f.setPointSizeF(timestampFontPointSize(option.font));

    return QFontMetrics(f).boundingRect(str)
            .adjusted(0, 0, 1, 1);
}

QRect PageAccountItemDelegatePrivate::amountBox(const QStyleOptionViewItem &option, QString str) const
{
    QFont f(option.font);

    f.setPointSizeF(timestampFontPointSize(option.font));

    return QFontMetrics(f).boundingRect(str)
            .adjusted(0, 0, 1, 1);
}

QRect PageAccountItemDelegatePrivate::valueBox(const QStyleOptionViewItem &option, QString str) const
{
    QFont f(option.font);

    f.setPointSizeF(timestampFontPointSize(option.font));

    return QFontMetrics(f).boundingRect(str)
            .adjusted(0, 0, 1, 1);
}

QRect PageAccountItemDelegatePrivate::tokenValueBox(const QStyleOptionViewItem &option, QString str) const
{
    QFont f(option.font);

    f.setPointSizeF(timestampFontPointSize(option.font));

    return QFontMetrics(f).boundingRect(str)
            .adjusted(0, 0, 1, 1);
}

qreal PageAccountItemDelegatePrivate::timestampFontPointSize(const QFont &f)
{
    return f.pointSize() * (1/Global::Layout::getXScale());
}

QRect PageAccountItemDelegatePrivate::messageBox(const QStyleOptionViewItem &option) const
{
    return option.fontMetrics.boundingRect(option.text).adjusted(0, 0, 1, 1);
}
