#ifndef PORTFOLIOUPDATER_H
#define PORTFOLIOUPDATER_H

#include "portfolio.h"

// Must be called whenever the portfolio is modified
// Usable in classes containing a Portfolio_ instance.
// Calls UpdatePortfolioValueAndWeights() in destructor, which triggers bakcend and UI update.

#define UPDATE_ON_RETURN(PortfolioPointer)                          \
    PortfolioUpdater Updater(*PortfolioPointer, true)               \

// To use only when there is no need to validate
#define UPDATE_ON_RETURN_NO_VALIDATE(PortfolioPointer)              \
    PortfolioUpdater Updater(*PortfolioPointer, false)              \



class PortfolioUpdater : public QObject
{
    Q_OBJECT

    friend class PortfolioInitializationDialog;

public:

    PortfolioUpdater(Portfolio& Portfolio, bool Validate, QObject* Parent = nullptr);

public:

    // Emits Modified() signal
    ~PortfolioUpdater();

private:

    void ValidatePortfolio();
    void UpdatePortfolioValueAndWeights();

private:

    Portfolio& Portfolio_;
    bool Validate_;
};

#endif // PORTFOLIOUPDATER_H
