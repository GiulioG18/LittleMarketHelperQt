#ifndef PORTFOLIOCALIBRATOR_H
#define PORTFOLIOCALIBRATOR_H

#include "calibrationtablewidget.h"
#include "portfolio.h"

#include <QDialog>

class PortfolioCalibrator : public QDialog
{
    Q_OBJECT

public:

    explicit PortfolioCalibrator(Portfolio& Portfolio);

private:

    void Details();
    void Launch();
    void Cancel();

private:

    Portfolio& Portfolio_;

    // User Interface
    CalibrationTableWidget*     CalibrationTableTbl_;
    QPushButton*                DetailsBtn_;
    QPushButton*                LaunchBtn_;
    QPushButton*                CancelBtn_;

};

#endif // PORTFOLIOCALIBRATOR_H
