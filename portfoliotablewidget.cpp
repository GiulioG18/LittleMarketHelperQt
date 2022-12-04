#include "portfoliotablewidget.h"
#include "portfolioupdater.h"
#include "utils.h"

#include "qheaderview.h"

PortfolioTableWidget::PortfolioTableWidget(QWidget* Parent)
    :
      QTableWidget(Parent),
      NumberOfColumns_(6)
{
    // Stretch column headers to cover the whole table window
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Table headers
    HeaderLabels_ = QStringList{
        TRANSLATE("Name"),
        TRANSLATE("Isin"),
        TRANSLATE("Quantity"),
        TRANSLATE("Price"),
        TRANSLATE("Open Position"),
        TRANSLATE("Weight")
    };

    Q_ASSERT(HeaderLabels_.size() == NumberOfColumns_);

    setColumnCount(NumberOfColumns_);
    setHorizontalHeaderLabels(HeaderLabels_);

    // Do not allow the user to modify the table
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);

    // Sorting is disabled so that products/table-rows do not mismatch
    setSortingEnabled(false);
}

// This is the only slot connected to the itemChanged signal
// NB: We assume that this is the only editable field in the table
void PortfolioTableWidget::SetInclude(QTableWidgetItem* Item)
{
    UPDATE_ON_RETURN_NO_VALIDATE(Portfolio_);

    int ProductRow = Item->row();

    if (Item->checkState() == Qt::Checked)
    {
        Portfolio_->Products()[ProductRow].Include_ = true;
    }
    else
    {
        Portfolio_->Products()[ProductRow].Include_ = false;
    }
}

void PortfolioTableWidget::SetPortfolio(Portfolio* Portfolio)
{
    Portfolio_ = Portfolio;
}

Portfolio& PortfolioTableWidget::GetPortfolio()
{
    return *Portfolio_;
}

void PortfolioTableWidget::InsertCell(int Row, int Column, QVariant Value)
{
    QTableWidgetItem* Cell = new QTableWidgetItem();
    Cell->setData(Qt::DisplayRole, Value);
    Cell->setTextAlignment(Qt::AlignCenter);

    setItem(Row, Column, Cell);
}

void PortfolioTableWidget::InsertCellCheck(int Row, int Column, QVariant Value, bool Check)
{
    QTableWidgetItem* Cell = new QTableWidgetItem();

    // Include check button
    Qt::CheckState State = Check ? Qt::CheckState::Checked : Qt::CheckState::Unchecked;
    Cell->setCheckState(State);

    Cell->setData(Qt::DisplayRole, Value);
    Cell->setTextAlignment(Qt::AlignCenter);
    Cell->setToolTip(TRANSLATE("Include/Exclude"));

    setItem(Row, Column, Cell);
}

void PortfolioTableWidget::Update()
{
    Q_ASSERT(Portfolio_);

    clearContents();

    if (!Portfolio_->IsInitialized())
    {
        setRowCount(0);
    }
    else
    {
        // Disable connection during table creation
        QObject::disconnect(ItemChangedConnection_);

        const QVector<Product>& Products = Portfolio_->Products();

        setRowCount(Products.size());

        for (int Row = 0; Row < rowCount(); Row++)
        {
            const Product& Product = Products.at(Row);

            InsertCellCheck(Row, 0, Product.Name_, Product.Include_);
            InsertCell(Row, 1, Product.Isin_);
            InsertCell(Row, 2, Product.Quantity_);
            InsertCell(Row, 3, Product.Price_);
            InsertCell(Row, 4, Product.OpenPosition_);
            InsertCell(Row, 5, Product.Weight_);
        }

        // setItem() emits itemChanged, so we connect just after
        // When this row's checkbox's state changes, Portfolio is modified
        ItemChangedConnection_ = QObject::connect(
                    this, &PortfolioTableWidget::itemChanged,
                    this, &PortfolioTableWidget::SetInclude
        );
    }
}



