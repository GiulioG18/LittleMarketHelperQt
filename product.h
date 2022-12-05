#ifndef PRODUCT_H
#define PRODUCT_H

#include <QVariant>
#include <QString>


class LittleMarketHelper;

struct Product
{
    Product(
            QString& Name,
            QString& Isin,
            int Quantity,
            double Price,
            double OpenPosition,
            QVariant Weight,
            bool Include);

    QString Name_;
    QString Isin_;
    int Quantity_;
    double Price_;
    double OpenPosition_;
    QVariant Weight_;       // Either a double or a string
    bool Include_;
};

#endif // PRODUCT_H
