#ifndef PORTFOLIOEDITORTABLEWIDGET_H
#define PORTFOLIOEDITORTABLEWIDGET_H

#include "portfoliotablewidget.h"

#include <QVector>
#include <QPushButton>

class PortfolioEditor;

class PortfolioEditorTableWidget : public PortfolioTableWidget
{
    friend class PortfolioEditor;

    Q_OBJECT

public:

    explicit PortfolioEditorTableWidget(PortfolioEditor* PortfolioEditor);

private:

    void UpdateProducts(QTableWidgetItem* Item);

    void UpdateName(QVariant Value, int ProductIndex);
    void UpdateIsin(QVariant Value, int ProductIndex);
    void UpdateQuantity(QVariant Value, int ProductIndex);
    void UpdatePrice(QVariant Value, int ProductIndex);

    void AddProduct();
    void DeleteProductLater(int Row);

protected:

    virtual void Update() override;

    void InsertDeleteCell(int Row, int Column);
    void InsertCellEdit(int Row, int Column, QVariant Value);

private:

    QVector<Product>& ProductsCopy_;
    QVector<int>* ProductsToDelete_;
};


#endif // PORTFOLIOEDITORTABLEWIDGET_H
