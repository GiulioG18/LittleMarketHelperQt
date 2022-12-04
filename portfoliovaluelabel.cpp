#include "portfoliovaluelabel.h"

PortfolioValueLabel::PortfolioValueLabel(QWidget* Parent)
    :
      QLabel(Parent)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
}

void PortfolioValueLabel::SetPortfolio(Portfolio* Portfolio)
{
    Portfolio_ = Portfolio;
}

void PortfolioValueLabel::Update()
{
    setText(QString("Portfolio Value :  ") + QString::number(Portfolio_->Value()) + QString(" EUR"));
}
