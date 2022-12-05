#include "mainbutton.h"
#include "portfoliocalibrator.h"
#include "portfolioupdater.h"


Calibrate::Calibrate(QWidget* Parent)
    :
      MainButton(Parent)
{
    QObject::connect(this, &QPushButton::clicked, this, &Calibrate::Clicked);
}

void Calibrate::Clicked()
{
    Q_ASSERT(MainButton::Portfolio_);
    Q_ASSERT(MainButton::Portfolio_->IsInitialized());

    UPDATE_ON_RETURN(Portfolio_);

    PortfolioCalibrator* Calibrator = new PortfolioCalibrator(*MainButton::Portfolio_);
    Calibrator->exec();
}

void Calibrate::Update()
{
    Q_ASSERT(MainButton::Portfolio_);

    MainButton::SetNotInitializedTooltip();
}

