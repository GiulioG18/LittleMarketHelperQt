#include "mainbutton.h"



Help::Help(QWidget* Parent)
    :
      MainButton(Parent)
{
    QObject::connect(this,  &QPushButton::clicked, this, &Help::Clicked);
}

void Help::Clicked()
{
    Q_ASSERT(MainButton::Portfolio_);
}

void Help::Update()
{
    SetNotAvailableTooltip();
}
