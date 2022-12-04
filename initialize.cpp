#include "mainbutton.h"
#include "portfolioupdater.h"
#include "utils.h"
#include "portfolioinitializationdialog.h"

#include <QMessageBox>

#include <stdexcept>


Initialize::Initialize(QWidget* Parent)
    :
      MainButton(Parent)
{
    QObject::connect(this, &QPushButton::clicked, this, &Initialize::Clicked);
}

void Initialize::Clicked()
{
    Q_ASSERT(MainButton::Portfolio_);

    UPDATE_ON_RETURN(Portfolio_);

    // When already there, ask user if he wants to overwrite it
    if (MainButton::Portfolio_->IsInitialized())
    {
        QMessageBox Warning;

        Warning.setText(TRANSLATE("An existing portfolio is already there."));
        Warning.setInformativeText(TRANSLATE("Do you wish to overwrite it?"));
        Warning.setIcon(QMessageBox::Warning);
        Warning.setStandardButtons(QMessageBox::No);
        Warning.setDefaultButton(QMessageBox::No);
        Warning.addButton(TRANSLATE("Overwrite"), QMessageBox::YesRole);

        if (Warning.exec() == QMessageBox::No)
        {
            return;
        }

        MainButton::Portfolio_->Reset();
    }

    // How should the portfolio be initialized?
    PortfolioInitializationDialog* Dialog = new PortfolioInitializationDialog(*MainButton::Portfolio_, this);
    Dialog->exec();
}

void Initialize::Update()
{
    throw std::runtime_error("Initialize button should not be updated!");
}




