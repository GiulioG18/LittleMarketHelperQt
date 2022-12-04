#include "MainButton.h"

#include "utils.h"

// BASE

MainButton::MainButton(QWidget* Parent)
    :
      QPushButton(Parent)
{
}

void MainButton::SetPortfolio(Portfolio* Portfolio)
{
    Portfolio_ = Portfolio;
}

void MainButton::SetNotInitializedTooltip()
{
    bool Initialized = Portfolio_->IsInitialized();

    // Disable button not ready
    this->setEnabled(Initialized);

    // Set tooltips for disabled button
    QString TooltipMsg = Initialized ? "" : TRANSLATE("Initialize a portfolio first!");
    this->setToolTip(TooltipMsg);
}

void MainButton::SetNotAvailableTooltip()
{
    // Disable button not implemented
    this->setEnabled(false);

    // Set tooltips for disabled button
    QString TooltipMsg = TRANSLATE("This functionality is not available yet");
    this->setToolTip(TooltipMsg);
}
