#ifndef PORTFOLIOTABLEWIDGET_H
#define PORTFOLIOTABLEWIDGET_H

#include "portfolio.h"

#include <QTableWidget>


class PortfolioTableWidget : public QTableWidget
{
    friend class LittleMarketHelper;

    Q_OBJECT

public:

    PortfolioTableWidget(QWidget* Parent = nullptr);

public:

    void SetPortfolio(Portfolio* Portfolio);
    Portfolio& GetPortfolio();

protected:

    virtual void Update();

protected:

    void InsertCell(int Row, int Column, QVariant Value);
    void InsertCellCheck(int Row, int Column, QVariant Value, bool Check);
    void SetInclude(QTableWidgetItem* Item);

protected:

    Portfolio* Portfolio_;
    int NumberOfColumns_;
    QStringList HeaderLabels_;
    QMetaObject::Connection ItemChangedConnection_;     // Stored to disabled it during table creation

};

#endif // PORTFOLIOTABLEWIDGET_H
