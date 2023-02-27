#ifndef PAGEACCOUNTLIST_H
#define PAGEACCOUNTLIST_H

#include <QListView>

class PageAccountList : public QListView {
    Q_OBJECT
public:
    explicit PageAccountList(QWidget *parent = nullptr);
    void setScale();
    void setStyle();

public slots:
    void addMessage(const QString &ticker, const QString &address, const double &amount, const double &value, const double &tokenValue);
    void setTokenValue(QString ticker, double tokenValue);
    QList<QString> getTickers();
    void clearAll();
signals:
    void itemClicked(int item);
};

#endif // PAGEACCOUNTLIST_H
