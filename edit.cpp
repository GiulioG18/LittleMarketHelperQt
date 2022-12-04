#include "mainbutton.h"
#include "portfolioeditor.h"
#include "portfolioupdater.h"

#include <QEventLoop>



Edit::Edit(QWidget* Parent)
    :
      MainButton(Parent)
{
    QObject::connect(this,  &QPushButton::clicked, this, &Edit::Clicked);
}

void Edit::Clicked()
{
    Q_ASSERT(MainButton::Portfolio_);
    Q_ASSERT(MainButton::Portfolio_->IsInitialized());

    UPDATE_ON_RETURN(Portfolio_);

    PortfolioEditor* Editor = new PortfolioEditor(*MainButton::Portfolio_);
    Editor->exec();
}

void Edit::Update()
{
    Q_ASSERT(MainButton::Portfolio_);

    MainButton::SetNotInitializedTooltip();
}

