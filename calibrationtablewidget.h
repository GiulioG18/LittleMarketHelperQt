#ifndef CALIBRATIONTABLEWIDGET_H
#define CALIBRATIONTABLEWIDGET_H

#include "portfolio.h"

#include <QTableWidget>


class CalibrationTableWidget : public QTableWidget
{
    Q_OBJECT

public:

    explicit CalibrationTableWidget(QWidget* Parent = nullptr);

public:

    void Update();

private:

    void InsertCell(int Row, int Column, QVariant Valu);

private:

    Portfolio* Portfolio_;

    QVector<Product>    IncludedProducts_;
    QVector<int>        BuySell_;

    int NumberOfColumns_;
    QStringList HeaderLabels_;

    bool Calibrated_;
};


#endif // CALIBRATIONTABLEWIDGET_H
