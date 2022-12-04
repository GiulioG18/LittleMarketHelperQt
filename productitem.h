#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QTableWidgetItem>

class ProductItem : public QTableWidgetItem
{
public:

    ProductItem(const QVariant& Value);
};

#endif // PRODUCTITEM_H
