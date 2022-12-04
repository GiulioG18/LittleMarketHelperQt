#include "productitem.h"

ProductItem::ProductItem(const QVariant& Value)
    :
      QTableWidgetItem()
{
    // Set value in the cell as display only
    QTableWidgetItem::setData(Qt::DisplayRole, Value);

    QTableWidgetItem::setTextAlignment(Qt::AlignCenter);
}
