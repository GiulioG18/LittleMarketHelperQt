#ifndef PORTFOLIOINITIALIZATIONDIALOG_H
#define PORTFOLIOINITIALIZATIONDIALOG_H

#include "portfolio.h"

#include <QDialog>
#include <QScopedPointer>

namespace Ui {
class PortfolioInitializationDialog;
}

class PortfolioInitializationDialog : public QDialog
{
    Q_OBJECT

public:

    explicit PortfolioInitializationDialog(Portfolio& Portfolio, QWidget* Parent = nullptr);
    ~PortfolioInitializationDialog();

public slots:

    void Import();
    void EmptyInitialize();

private:

    Ui::PortfolioInitializationDialog* UserInterface_;
    Portfolio& Portfolio_;
};

#endif // PORTFOLIOINITIALIZATIONDIALOG_H
