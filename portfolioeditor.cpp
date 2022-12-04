#include "portfolioeditor.h"
#include "utils.h"

#include <QGridLayout>

#include <stdexcept>


PortfolioEditor::PortfolioEditor(Portfolio& Portfolio)
    :
      QDialog(),
      Portfolio_(Portfolio)
{
    setWindowTitle(TRANSLATE("Portfolio Editor"));
    resize(800, 300);

    // Create copy of products
    ProductsCopy_ = Portfolio.Products();

    // Init widgets
    PortfolioEditorTbl_ = new PortfolioEditorTableWidget(this);
    DoneBtn_ = new QPushButton(this);
    AddBtn_ = new QPushButton(this);
    CancelBtn_ = new QPushButton(this);

    // Allocate widgets in the grid
    QGridLayout* Grid = new QGridLayout(this);
    Grid->addWidget(PortfolioEditorTbl_, 1, 0, 1, 1);

    QHBoxLayout* HorizontalLayout = new QHBoxLayout();
    HorizontalLayout->addWidget(DoneBtn_);
    HorizontalLayout->addWidget(AddBtn_);
    HorizontalLayout->addWidget(CancelBtn_);

    Grid->addLayout(HorizontalLayout, 2, 0, 1, 1);

    // Name the buttons
    DoneBtn_->setText(TRANSLATE("Done"));
    AddBtn_->setText(TRANSLATE("Add"));
    CancelBtn_->setText(TRANSLATE("Cancel"));

    // Connect buttons to main functions
    QObject::connect(this->DoneBtn_, &QPushButton::clicked, this, &PortfolioEditor::Done);
    QObject::connect(this->AddBtn_, &QPushButton::clicked, this->PortfolioEditorTbl_, &PortfolioEditorTableWidget::AddProduct);
    QObject::connect(this->CancelBtn_, &QPushButton::clicked, this, &PortfolioEditor::Cancel);

    // Show portfolio table
    PortfolioEditorTbl_->Update();
}

PortfolioEditor::~PortfolioEditor()
{
}


// Main functions

void PortfolioEditor::Done()
{
    QMessageBox::StandardButton Answer = QMessageBox::question(this, TRANSLATE("Portfolio Editor"), TRANSLATE("Do you want to save your changes"));

    if (Answer == QMessageBox::Yes)
    {
        // Add and Delete products
        Portfolio_.Products().clear();
        Portfolio_.Products() = ProductsCopy_;
        DeleteSelectedProducts();
    }
    else if (Answer == QMessageBox::No) // TODO: when pressing X, it ends up in here. This is not ideal (it should cancel the operation instead)
    {
        utils::SimpleDialog(TRANSLATE("Portfolio Editor"), TRANSLATE("Changes discarded"), QMessageBox::Information);
    }
    else
    {
        throw std::runtime_error("Unexpected flow.");
    }

    close();
}

void PortfolioEditor::Cancel()
{
    QMessageBox::StandardButton Answer = QMessageBox::question(
                this,
                TRANSLATE("Portfolio Editor"),
                TRANSLATE("Every change applied will be discarded. Continue?")
                );

    if (Answer == QMessageBox::Yes)
    {
        utils::SimpleDialog(TRANSLATE("Portfolio Editor"), TRANSLATE("Changes discarded"), QMessageBox::Information);
    }
    else if (Answer == QMessageBox::No)
    {
        return;
    }
    else
    {
        throw std::runtime_error("Unexpected flow.");
    }

    close();

}

//// Override closeEvent function to run PortfolioEditor::AbortChanges
//void PortfolioEditor::closeEvent(QCloseEvent *event)
//{
//    if (PortfolioEditor::AbortChanges())
//    {
//        event->accept();
//    }
//    else
//    {
//        event->ignore();
//    }
//}

void PortfolioEditor::DeleteSelectedProducts()
{
    if (ProductsToDelete_.isEmpty())
    {
        return;
    }

    // Sorting the indeces and removing them with an inverse order
    // "should" not invalidate the iterator...
    std::sort(std::begin(ProductsToDelete_), std::end(ProductsToDelete_));

    for (int ProductIndex = ProductsToDelete_.size() - 1; ProductIndex >= 0; ProductIndex--)
    {
        Portfolio_.Products().erase(Portfolio_.Products().begin() + ProductsToDelete_[ProductIndex]);
    }
}






