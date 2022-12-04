#include "mainbutton.h"


Calibrate::Calibrate(QWidget* Parent)
    :
      MainButton(Parent)
{
    QObject::connect(this, &QPushButton::clicked, this, &Calibrate::Clicked);
}

void Calibrate::Clicked()
{
    Q_ASSERT(MainButton::Portfolio_);
}

void Calibrate::Update()
{
    Q_ASSERT(MainButton::Portfolio_);

    MainButton::SetNotInitializedTooltip();
}

