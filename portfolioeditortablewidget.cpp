#include "portfolioeditortablewidget.h"
#include "portfolioeditor.h"
#include "utils.h"

#include <QBoxLayout>

#include <stdexcept>


PortfolioEditorTableWidget::PortfolioEditorTableWidget(PortfolioEditor* PortfolioEditor)
    :
      PortfolioTableWidget(),
      ProductsCopy_(PortfolioEditor->ProductsCopy_)
{
    PortfolioTableWidget::SetPortfolio(&PortfolioEditor->Portfolio_);
    ProductsToDelete_ = &PortfolioEditor->ProductsToDelete_;

    // Overwrite PortfolioTableWidget NoEditTriggers setting
    setEditTriggers(QAbstractItemView::AllEditTriggers);

    // Overwrite headers
    NumberOfColumns_ = 5;
    setColumnCount(NumberOfColumns_);
    HeaderLabels_ = QStringList{
        TRANSLATE("Name"),
        TRANSLATE("Isin"),
        TRANSLATE("Quantity"),
        TRANSLATE("Price"),
        TRANSLATE(""),
    };

    setHorizontalHeaderLabels(HeaderLabels_);
}

void PortfolioEditorTableWidget::Update()
{
    Q_ASSERT(Portfolio_);
    Q_ASSERT(Portfolio_->IsInitialized());

    clearContents();

    // Disable connection during UI Updates
    QObject::disconnect(ItemChangedConnection_);

    int RowCount = ProductsCopy_.size();
    setRowCount(RowCount);

    for (int Row = 0; Row < rowCount(); Row++)
    {
        const Product& Product = ProductsCopy_.at(Row);

        InsertCellEdit(Row, 0, Product.Name_);
        InsertCellEdit(Row, 1, Product.Isin_);
        InsertCellEdit(Row, 2, Product.Quantity_);
        InsertCellEdit(Row, 3, Product.Price_);
        // Insert Delete button
        InsertDeleteCell(Row, 4);
    }

    ItemChangedConnection_ = QObject::connect(
                this, &PortfolioTableWidget::itemChanged,
                this, &PortfolioEditorTableWidget::UpdateProducts
    );
}

void PortfolioEditorTableWidget::InsertDeleteCell(int Row, int Column)
{
    QPushButton* DeleteBtn = new QPushButton();

    DeleteBtn->setText("Delete");

    //setLayout(Layout);
    setCellWidget(Row, Column, DeleteBtn);

    QObject::connect(DeleteBtn, &QPushButton::clicked, this, [Row, this] () { this->DeleteProductLater(Row); });
}

void PortfolioEditorTableWidget::InsertCellEdit(int Row, int Column, QVariant Value)
{
    QTableWidgetItem* Cell = new QTableWidgetItem();
    Cell->setData(Qt::EditRole, Value);
    Cell->setTextAlignment(Qt::AlignCenter);

    setItem(Row, Column, Cell);
}

// Saves the changes done at UI level to the products' vector
void PortfolioEditorTableWidget::UpdateProducts(QTableWidgetItem* Item)
{
    switch (Item->column())
    {
    case 0: UpdateName(Item->data(Qt::EditRole), Item->row());        break;
    case 1: UpdateIsin(Item->data(Qt::EditRole), Item->row());        break;
    case 2: UpdateQuantity(Item->data(Qt::EditRole), Item->row());    break;
    case 3: UpdatePrice(Item->data(Qt::EditRole), Item->row());       break;

    default: throw std::runtime_error("Wrong Column signaled from itemChanged.");
    }
}


// This functions are used to validate an user update
// NB: They assume that QVariant has the correct type for the product's member

void PortfolioEditorTableWidget::UpdateName(QVariant Value, int ProductIndex)
{
    // Make sure that we are within the products vector bounds
    if (ProductIndex > ProductsCopy_.size())
    {
        throw std::runtime_error("Wrong Row signaled from itemChanged.");
    }

    ProductsCopy_[ProductIndex].Name_ = Value.toString();
}

void PortfolioEditorTableWidget::UpdateIsin(QVariant Value, int ProductIndex)
{
    // Make sure that we are within the products vector bounds
    if (ProductIndex > ProductsCopy_.size())
    {
        throw std::runtime_error("Wrong Row signaled from itemChanged.");
    }

     ProductsCopy_[ProductIndex].Isin_ = Value.toString();
}

void PortfolioEditorTableWidget::UpdateQuantity(QVariant Value, int ProductIndex)
{
    // Make sure that we are within the products vector bounds
    if (ProductIndex > ProductsCopy_.size())
    {
        throw std::runtime_error("Wrong Row signaled from itemChanged.");
    }

    // Validate
    if (Value.toInt() < 0)
    {
        utils::SimpleDialog(TRANSLATE("Portfolio Editor"), TRANSLATE("Please insert non-negative value for Quantity, else the product won't be validated"), QMessageBox::Critical);
    }

    ProductsCopy_[ProductIndex].Quantity_ = Value.toInt();
}

void PortfolioEditorTableWidget::UpdatePrice(QVariant Value, int ProductIndex)
{
    // Make sure that we are within the products vector bounds
    if (ProductIndex > ProductsCopy_.size())
    {
        throw std::runtime_error("Wrong Row signaled from itemChanged.");
    }

    // Validate
    if (Value.toInt() < 0)
    {
        utils::SimpleDialog(TRANSLATE("Portfolio Editor"), TRANSLATE("Please insert positive value for Price, else the product won't be validated"), QMessageBox::Critical);
    }


    ProductsCopy_[ProductIndex].Price_ = Value.toDouble();
}

void PortfolioEditorTableWidget::AddProduct()
{
    // Disable connection during new row creation
    QObject::disconnect(ItemChangedConnection_);

    int ProductIndex = rowCount();
    setRowCount(rowCount() + 1);

    QString Name = QString("Name ") + QString::number(ProductIndex + 1);
    QString Isin = QString("Isin ") + QString::number(ProductIndex + 1);
    // Add empty product to the vector copy
    ProductsCopy_.emplaceBack(
                Name,
                Isin,
                0, 0.0, 0.0, 0.0,
                true);

    const Product& Product = ProductsCopy_.at(ProductIndex);

    // Add newly created empty product to the UI
    InsertCellEdit(ProductIndex, 0, Product.Name_);
    InsertCellEdit(ProductIndex, 1, Product.Isin_);
    InsertCellEdit(ProductIndex, 2, Product.Quantity_);
    InsertCellEdit(ProductIndex, 3, Product.Price_);
    // Insert Delete button
    InsertDeleteCell(ProductIndex, 4);

    ItemChangedConnection_ = QObject::connect(
                this, &PortfolioTableWidget::itemChanged,
                this, &PortfolioEditorTableWidget::UpdateProducts
                );
}

// NB: The products are actually removed from the vector only when the dialog returns
void PortfolioEditorTableWidget::DeleteProductLater(int Row)
{
    // Disable connection that updates products
    // This is needed since setBackground(Qt::red) modifies the item
    // and internally calls for setData()
    QObject::disconnect(ItemChangedConnection_);

    if (!(*ProductsToDelete_).contains(Row))
    {
        QPushButton* Button = qobject_cast<QPushButton*>(sender());
        Button->setText("Undo");

        for (int Column = 0; Column < columnCount() - 1; Column++)
        {
            item(Row, Column)->setBackground(Qt::red);
        }

        ProductsToDelete_->push_back(Row);
    }
    else
    {

        QPushButton* Button = qobject_cast<QPushButton*>(sender());
        Button->setText("Delete");

        for (int Column = 0; Column < columnCount() - 1; Column++)
        {
            item(Row, Column)->setBackground(Qt::color0);
        }

        ProductsToDelete_->remove(ProductsToDelete_->indexOf(Row));
    }

    ItemChangedConnection_ = QObject::connect(
                this, &PortfolioTableWidget::itemChanged,
                this, &PortfolioEditorTableWidget::UpdateProducts
    );
}






