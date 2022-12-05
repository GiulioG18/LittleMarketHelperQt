#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "product.h"

#include <QObject>
#include <QVector>


class PortfolioUpdater;


class Portfolio : public QObject
{
    Q_OBJECT

public:

    explicit Portfolio(QObject *Parent = nullptr);

signals:

    // This signal triggers the update of the values in the main window
    void Modified();

public: // Getters and Setters

    inline bool IsSave() const { return Save_; }
    inline void SetSave(bool Save) { Save_ = Save; }

    inline double Value() const { return Value_; }
    inline double& Value() { return Value_; }

    inline bool IsInitialized() const { return Initialized_; }
    inline void SetInitialized(bool Value) { Initialized_ = Value; }

    inline bool IsCalibrated() const { return Calibrated_; }
    inline void SetCalibrated(bool Calibrated) { Calibrated_ = Calibrated; }

    inline QVector<Product>& Products() { return Products_; }
    inline const QVector<Product>& Products() const { return Products_; }

public:

    bool IsEmpty() const;
    void MakeEmpty(bool Save);
    void Reset();
    QVector<Product> IncludedProducts();

private:

    QVector<Product>    Products_;
    double              Value_;
    bool                Initialized_;
    bool                Calibrated_;
    bool                Save_;              // Save log to History file
};

#endif // PORTFOLIO_H
