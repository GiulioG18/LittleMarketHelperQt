#include "portfolioinitializationdialog.h"
#include "ui_portfolioinitializationdialog.h"
#include "portfolioupdater.h"
#include "parser.h"
#include "utils.h"

#include <QPushButton>
#include <QCheckBox>
#include <QInputDialog>
#include <QMessageBox>




PortfolioInitializationDialog::PortfolioInitializationDialog(Portfolio& Portfolio, QWidget* Parent)
    :
      QDialog(Parent),
      UserInterface_(new Ui::PortfolioInitializationDialog),
      Portfolio_(Portfolio)
{
    UserInterface_->setupUi(this);
    QWidget::adjustSize();

    // Interface buttons connection
    QObject::connect(UserInterface_->ImportBtn, &QPushButton::clicked, this, &PortfolioInitializationDialog::Import);
    QObject::connect(UserInterface_->MakeEmptyBtn, &QPushButton::clicked, this, &PortfolioInitializationDialog::EmptyInitialize);
    QObject::connect(UserInterface_->AbortBtn, &QPushButton::clicked, this, &QWidget::close);
}

PortfolioInitializationDialog::~PortfolioInitializationDialog()
{
    delete UserInterface_;
}

void PortfolioInitializationDialog::Import()
{
    // Get Parser type from user
    QStringList SupportedParsers;
    for (const auto& SupportedParser : Parser::GetParsersMap())
    {
        SupportedParsers.append(SupportedParser.first);
    }


    bool Ok;
    auto ParserType = Parser::GetParsersMap().find(QInputDialog::getItem(
                this,
                TRANSLATE("Broker type"),
                TRANSLATE("Select a broker from the list below."),
                SupportedParsers,
                0,
                false,
                &Ok
                ));

    // If closes or cancels, inform and return
    if (!Ok)
    {
        utils::SimpleDialog(
                    TRANSLATE("Constructing Portfolio"),
                    TRANSLATE("If your broker is not supported, initialize an empty portfolio by selecting Make Empty."),
                    QMessageBox::Information);

        return;
    }

    // Construct and run parser
    std::unique_ptr<Parser> ParserInstance = Parser::Construct(Portfolio_, ParserType->second);
    bool Status = ParserInstance->ConstructPortfolioFromReportFile(!UserInterface_->AnonymousBtn->checkState());
    if (!Status)
    {
        utils::SimpleDialog(
                    TRANSLATE("Constructing Portfolio"),
                    TRANSLATE("Portfolio not initialized."),
                    QMessageBox::Information);

        return;
    }

    close();
}

void PortfolioInitializationDialog::EmptyInitialize()
{
    Portfolio_.MakeEmpty(!UserInterface_->AnonymousBtn->checkState());
    close();
}
