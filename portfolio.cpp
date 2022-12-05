#include "portfolio.h"
#include "utils.h"

#include <QTimer>

Portfolio::Portfolio(QObject *Parent)
    :
      QObject{Parent},
      Value_(0.0),
      Initialized_(false),
      Calibrated_(false),
      Save_(false)
{
}

bool Portfolio::IsEmpty() const
{
    Q_ASSERT(Initialized_);

    return Products_.isEmpty();
}

void Portfolio::MakeEmpty(bool Save)
{
    Q_ASSERT(!Initialized_);

    Products_.clear();
    Value_ = 0.0;
    Initialized_ = true;
    Save_ = Save;
}

void Portfolio::Reset()
{
    Products_.clear();
    Value_ = 0.0;
    Initialized_ = false;
    Save_ = false;
}

QVector<Product> Portfolio::IncludedProducts()
{
    QVector<Product> IncludedProducts;

    for (const auto& Product : Products_)
    {
        if (Product.Include_)
        {
            IncludedProducts.emplaceBack(Product);
        }
    }

    return IncludedProducts;
}







