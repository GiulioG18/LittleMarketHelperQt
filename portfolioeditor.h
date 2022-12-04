#ifndef PORTFOLIOEDITOR_H
#define PORTFOLIOEDITOR_H

#include "portfolio.h"
#include "portfolioeditortablewidget.h"

#include <QTableWidget>
#include <QDialog>
#include <QPushButton>



class PortfolioEditor : public QDialog
{
    friend class PortfolioEditorTableWidget;

    Q_OBJECT

public:

    explicit PortfolioEditor(Portfolio& Portfolio);
    ~PortfolioEditor();

private:

    // TODO: find out why products are sorted by Isin inside vector (no clue..)
    void Done();
    void Cancel();

    bool AbortChanges();

    void DeleteSelectedProducts();

private:

    Portfolio& Portfolio_;
    QVector<Product> ProductsCopy_;
    QVector<int> ProductsToDelete_;

    // User Interface
    PortfolioEditorTableWidget*     PortfolioEditorTbl_;
    QPushButton*                    DoneBtn_;
    QPushButton*                    AddBtn_;
    QPushButton*                    CancelBtn_;
};

#endif // PORTFOLIOEDITOR_H
