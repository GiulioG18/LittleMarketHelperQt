#include "portfolioupdater.h"
#include "utils.h"

#include <QMessageBox>

#include <algorithm>
#include <stdexcept>




PortfolioUpdater::PortfolioUpdater(Portfolio& Portfolio, bool Validate, QObject* Parent)
    :
      QObject{Parent},
      Portfolio_(Portfolio),
      Validate_(Validate)
{
}

PortfolioUpdater::~PortfolioUpdater()
{
    if (Validate_)
    {
        ValidatePortfolio();
    }

    UpdatePortfolioValueAndWeights();

    emit Portfolio_.Modified();
}

// TODO: Add check for Quantity to be non negative
void PortfolioUpdater::ValidatePortfolio()
{
    // Validate price and quantity
    Portfolio_.Products().erase(
                std::remove_if(
                    std::begin(Portfolio_.Products()),
                    std::end(Portfolio_.Products()),
                    [] (const Product& Product)
                    {
                        if (Product.Price_ > 0 && Product.Quantity_ >= 0)
                        {
                            return false;
                        }
                        else if (Product.Price_ <= 0)
                        {
                            QString WarningMessage =
                                    Product.Name_ +
                                    QString(TRANSLATE(" had non-positive Price and so has been removed from the portfolio."));

                            utils::SimpleDialog(TRANSLATE("Validating Portfolio"), WarningMessage, QMessageBox::Warning);

                            return true;
                        }
                        else if (Product.Quantity_ < 0)
                        {
                            QString WarningMessage =
                                    Product.Name_ +
                                    QString(TRANSLATE(" had negative Quantity and so has been removed from the portfolio."));

                            utils::SimpleDialog(TRANSLATE("Validating Portfolio"), WarningMessage, QMessageBox::Warning);

                            return true;
                        }
                        else
                        {
                            throw std::runtime_error("Unexpected flow.");
                        }
                    }),
                    std::end(Portfolio_.Products())
                );

    // Warn user of duplicate products (by Isin)
    std::sort(std::begin(Portfolio_.Products()), std::end(Portfolio_.Products()),
        [] (const Product& First, const Product& Second)
            {
                return First.Isin_ < Second.Isin_;
            }
        );

    auto Iterator = std::adjacent_find(std::begin(Portfolio_.Products()), std::end(Portfolio_.Products()),
        [](const Product& First, const Product& Second)
            {
                return First.Isin_ == Second.Isin_;
            }
        );

    if (Iterator != std::end(Portfolio_.Products()))
    {
        utils::SimpleDialog(
                    TRANSLATE("Validating Portfolio"),
                    TRANSLATE("There are 2 or more identical products. Consider editing portfolio."),
                    QMessageBox::Warning);
    }

    //// OpenPosition / Price * Quantity compatibility check
    //for (const auto& Product : Portfolio_.Products())
    //{
    //    // Assert that OpenPosition is (Quantity * Price)
    //    const double ToleranceLevel = 1e-2;
    //    if (std::abs(Product.OpenPosition_ - Product.Price_ * static_cast<double>(Product.Quantity_)) > ToleranceLevel)
    //    {
    //        throw std::runtime_error("Price/OpenPosition not compatible.");
    //    }
    //}
}

void PortfolioUpdater::UpdatePortfolioValueAndWeights()
{
    if (Portfolio_.IsInitialized())
    {
        Portfolio_.Value() = 0.0;

        if (!Portfolio_.IsEmpty())
        {            
            // OPEN POSITION
            for (auto& Product : Portfolio_.Products())
            {
                if (Product.Price_ <= 0.0)
                {
                    throw std::runtime_error("Price is assumed to be checked before this function call.");
                }

                Product.OpenPosition_ = Product.Price_ * Product.Quantity_;
            }

            // PORTFOLIO VALUE
            for (const auto& Product : Portfolio_.Products())
            {
                if (!Product.Include_)
                {
                    continue;
                }

                if (Product.Price_ <= 0.0)
                {
                    throw std::runtime_error("Price is assumed to be checked before this function call.");
                }

                Portfolio_.Value() += Product.OpenPosition_;
            }

            // WEIGHT
            double WeightsSum = 0.0;

            // If every product has 0 quantity
            if (Portfolio_.Value() == 0.0)                      // TODO: This if statement is dangerous, should modify this algorithm
            {
                // We set equal weights in this scenario
                double Weight = (1 / static_cast<double>(Portfolio_.Products().size())) * 100.00;

                for (auto& Product : Portfolio_.Products())
                {
                    if (!Product.Include_)
                    {
                        Product.Weight_ = 0.0;
                        continue;
                    }

                    Product.Weight_ = Weight;
                    WeightsSum += Weight;
                }
            }
            else
            {
                for (auto& Product : Portfolio_.Products())
                {
                    if (!Product.Include_)
                    {
                        Product.Weight_ = 0.0;
                        continue;
                    }

                    double OpenPosition = Product.OpenPosition_;
                    double Weight = OpenPosition / Portfolio_.Value() * 100.00f;

                    Product.Weight_ = Weight;
                    WeightsSum += Weight;
                }
            }

            // Check sum of weights to be 100.00
            if (WeightsSum != 0.0)                  // When every product is unchecked, skip
            {
                const double ToleranceLevel = 1e-5;
                if (std::abs(WeightsSum - 100.00000) > ToleranceLevel)
                {
                     throw std::runtime_error("Sum of weights is not 100.00.");
                }
            }
        }
    }
}



