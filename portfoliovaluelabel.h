#ifndef PORTFOLIOVALUELABEL_H
#define PORTFOLIOVALUELABEL_H

#include "portfolio.h"

#include <QLabel>

class PortfolioValueLabel : public QLabel
{
    friend class LittleMarketHelper;

    Q_OBJECT

public:

    explicit PortfolioValueLabel(QWidget* Parent = nullptr);

protected:

    void SetPortfolio(Portfolio* Portfolio);
    void Update();

private:

    Portfolio* Portfolio_;
};

#endif // PORTFOLIOVALUELABEL_H
