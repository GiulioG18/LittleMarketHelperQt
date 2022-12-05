#include "calibrationtablewidget.h"
#include "utils.h"

#include <QHeaderView>

CalibrationTableWidget::CalibrationTableWidget(QWidget* Parent)
    :
      QTableWidget(Parent),
      NumberOfColumns_(4),
      Calibrated_(false)
{
    // Stretch column headers to cover the whole table window
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Table headers
    HeaderLabels_ = QStringList{
        TRANSLATE("Name"),
        TRANSLATE("Isin"),
        TRANSLATE("Buy/Sell"),
        TRANSLATE("Estimated Weight")
    };

    Q_ASSERT(HeaderLabels_.size() == NumberOfColumns_);

    setColumnCount(NumberOfColumns_);
    setHorizontalHeaderLabels(HeaderLabels_);

    // Do not allow the user to modify the table
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);

    setSortingEnabled(false);
}

void CalibrationTableWidget::Update()
{
    Q_ASSERT(Portfolio_);
    Q_ASSERT(Portfolio_->IsInitialized());

    // Clear Memory and UI

    IncludedProducts_.clear();
    BuySell_.clear();
    clearContents();

    // Update Memory and UI

    IncludedProducts_ = Portfolio_->IncludedProducts();
    int RowCount = IncludedProducts_.size();
    setRowCount(RowCount);

    if (!Calibrated_)
    {

    }
    else
    {

    }

    for (int Row = 0; Row < rowCount(); Row++)
    {
        const Product& Product = IncludedProducts.at(Row);

        InsertCell(Row, 0, Product.Name_);
        InsertCell(Row, 1, Product.Isin_);
        InsertCell(Row, 2, TRANSLATE(""));
        InsertCell(Row, 3, TRANSLATE(""));
    }
}

void CalibrationTableWidget::InsertCell(int Row, int Column, QVariant Value)
{
    QTableWidgetItem* Cell = new QTableWidgetItem();
    Cell->setData(Qt::DisplayRole, Value);
    Cell->setTextAlignment(Qt::AlignCenter);

    setItem(Row, Column, Cell);
}




