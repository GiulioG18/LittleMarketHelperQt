#ifndef PRODUCT_H
#define PRODUCT_H

#include <QVariant>
#include <QString>


class LittleMarketHelper;

class Product
{
    friend class LittleMarketHelper;
    friend class PortfolioUpdater;
    friend class PortfolioTableWidget;
    friend class PortfolioEditorTableWidget;

public:

    Product(
            QString& Name,
            QString& Isin,
            int Quantity,
            double Price,
            double OpenPosition,
            QVariant Weight,
            bool Include);

protected:

    QString Name_;
    QString Isin_;
    int Quantity_;
    double Price_;
    double OpenPosition_;
    QVariant Weight_;       // Either a double or a string
    bool Include_;
};

#endif // PRODUCT_H
