#include "littlemarkethelper.h"
#include "./ui_littlemarkethelper.h"
#include "utils.h"

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QCheckBox>
#include <QScreen>


LittleMarketHelper::LittleMarketHelper(Portfolio* const Portfolio, QWidget *Parent)
    :
      QMainWindow(Parent),
      UserInterface(new Ui::LittleMarketHelper),
      Portfolio_(Portfolio)
{
    // This calls every UI element constructor and some resizing function on those elements
    UserInterface->setupUi(this);    

    // Set full screen
    //QScreen* ThisScreen = QGuiApplication::primaryScreen();
    //QRect Rect = ThisScreen->availableGeometry();
    //int Height = Rect.height();
    //int Width = Rect.width();
    //resize(Height, Width);

    // Initialize Portfolio_ member for every UI element that needs it
    SetPortfolio(
                UserInterface->PortfolioTbl,
                UserInterface->InitializeBtn,
                UserInterface->EditBtn,
                UserInterface->CalibrateBtn,
                UserInterface->HistoryBtn,
                UserInterface->HelpBtn,
                UserInterface->AboutBtn,
                UserInterface->ExitBtn,
                UserInterface->PortfolioValueLbl
                );

    // Slots connections
    QObject::connect(this->Portfolio_, &Portfolio::Modified, this, &LittleMarketHelper::UpdateMainWindow);

    // Connects the UpdateMainWindow() signals to every UI element that needs to be updated
    ConnectUpdateSignal(
                UserInterface->PortfolioTbl,
                UserInterface->EditBtn,
                UserInterface->CalibrateBtn,
                UserInterface->HistoryBtn,
                UserInterface->HelpBtn,
                UserInterface->AboutBtn,
                UserInterface->PortfolioValueLbl
                );

    // Emit signal to update UI for the first time
    emit UpdateMainWindow();
}

LittleMarketHelper::~LittleMarketHelper()
{
    delete UserInterface;
}

template<typename... UiElement>
void LittleMarketHelper::SetPortfolio(UiElement* ...Element)
{
    (Element->SetPortfolio(Portfolio_), ...);
}

template<typename... UiElement>
void LittleMarketHelper::ConnectUpdateSignal(UiElement* ...Element)
{
    (QObject::connect(this, &LittleMarketHelper::UpdateMainWindow, Element, &UiElement::Update),
            ...);
}

void LittleMarketHelper::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton Answer = QMessageBox::question(this, "Little Market Helper", TRANSLATE("Are you sure you want to quit?"));

    if (Answer == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}



