#include "mainbutton.h"

About::About(QWidget* Parent)
    :
      MainButton(Parent)
{
    QObject::connect(this,  &QPushButton::clicked, this, &About::Clicked);
}

void About::Clicked()
{
    Q_ASSERT(MainButton::Portfolio_);
}

void About::Update()
{
    SetNotAvailableTooltip();
}
