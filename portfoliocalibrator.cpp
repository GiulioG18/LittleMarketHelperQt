#include "portfoliocalibrator.h"
#include "utils.h"

#include <QPushButton>

#include <QGridLayout>


PortfolioCalibrator::PortfolioCalibrator(Portfolio& Portfolio)
    :
      Portfolio_(Portfolio)
{
    setWindowTitle(TRANSLATE("Portfolio Calibrator"));
    resize(600, 300);

    // Init widgets
    CalibrationTableTbl_ = new CalibrationTableWidget(this);
    DetailsBtn_ = new QPushButton(this);
    LaunchBtn_ = new QPushButton(this);
    CancelBtn_ = new QPushButton(this);

    // Allocate widgets in the grid
    QGridLayout* Grid = new QGridLayout(this);
    Grid->addWidget(CalibrationTableTbl_, 1, 0, 1, 1);

    QHBoxLayout* HorizontalLayout = new QHBoxLayout();
    HorizontalLayout->addWidget(DetailsBtn_);
    HorizontalLayout->addWidget(LaunchBtn_);
    HorizontalLayout->addWidget(CancelBtn_);

    Grid->addLayout(HorizontalLayout, 2, 0, 1, 1);

    // Name the buttons
    DetailsBtn_->setText(TRANSLATE("Details"));
    LaunchBtn_->setText(TRANSLATE("Launch"));
    CancelBtn_->setText(TRANSLATE("Cancel"));

    // Connect buttons to main functions
    QObject::connect(this->DetailsBtn_, &QPushButton::clicked, this, &PortfolioCalibrator::Details);
    QObject::connect(this->LaunchBtn_, &QPushButton::clicked, this, &PortfolioCalibrator::Launch);
    QObject::connect(this->CancelBtn_, &QPushButton::clicked, this, &PortfolioCalibrator::Cancel);

    // Show portfolio table
    CalibrationTableTbl_->Update();
}

void PortfolioCalibrator::Details()
{

}

void PortfolioCalibrator::Launch()
{

}

void PortfolioCalibrator::Cancel()
{

}



