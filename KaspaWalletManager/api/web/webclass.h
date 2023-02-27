#ifndef WEBCLASS_H
#define WEBCLASS_H

#include <QString>
#include <QList>
#include <QPair>

namespace WebClass {
    class CoinGecko {
    private:
        bool valid = false;
    public:
        CoinGecko(QString data);
        bool getValid() { return valid; }
    };
};

#endif // WEBCLASS_H
