#include "product.h"

Product::Product(QString& Name, QString& Isin, int Quantity, double Price, double OpenPosition, QVariant Weight, bool Include)
    :
      Name_(std::move(Name)),
      Isin_(std::move(Isin)),
      Quantity_(Quantity),
      Price_(Price),
      OpenPosition_(OpenPosition),
      Weight_(Weight),
      Include_(Include)
{

}

