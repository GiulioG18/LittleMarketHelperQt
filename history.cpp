#include "mainbutton.h"



History::History(QWidget* Parent)
    :
      MainButton(Parent)
{
    QObject::connect(this,  &QPushButton::clicked, this, &History::Clicked);
}

void History::Clicked()
{
    Q_ASSERT(MainButton::Portfolio_);
}

void History::Update()
{
    SetNotAvailableTooltip();
}

