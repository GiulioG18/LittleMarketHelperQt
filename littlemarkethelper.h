#ifndef LITTLEMARKETHELPER_H
#define LITTLEMARKETHELPER_H

#include "portfolio.h"

#include <QMainWindow>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class LittleMarketHelper; }
QT_END_NAMESPACE

class LittleMarketHelper : public QMainWindow
{
    Q_OBJECT

public:

    LittleMarketHelper(Portfolio* const Portfolio, QWidget *Parent = nullptr);
    ~LittleMarketHelper();

signals:

    void UpdateMainWindow();

private:

    // Ooverride method to show dialog before closing
    void closeEvent (QCloseEvent *event);

    // Initialize Portfolio_ member for UI elements
    // UiElement must implement ::SetPortfolio() function
    template<typename... UiElement>
    void SetPortfolio(UiElement* ...Element);

    // Connects the UpdateMainWindow signals to every Ui element that needs
    // to be updated. UiElement must implement ::Update() function
    template<typename... UiElement>
    void ConnectUpdateSignal(UiElement* ...Element);


private:

    Ui::LittleMarketHelper* UserInterface;
    Portfolio*              Portfolio_;
};

#endif // LITTLEMARKETHELPER_H
