#include "littlemarkethelper.h"
#include "utils.h"
#include "portfolio.h"

#include <QApplication>
#include <QScopedPointer>

// TODO: Create dedicated class for every Ui object in the main window
// TODO: Create an update signal from LMH class and connect it to the various Ui objects that need to be updated
// TODO: Implement all the main buttons!
// TODO: Build an installer
// TODO: Properly implement exceptions
// TODO: Check other Q_ASSERT and replace when needed with an exception
// TODO: Add "include" column to portfolio table
// TODO: Turn off HistoryBtn until Implemented
// TODO: create class to turn off a signal RAII style

int main(int argc, char *argv[])
{
    try
    {
        // Create application, handles the events loop
        QApplication Application(argc, argv);

        // English, Italian, TODO: Maybe add chinese just for fun
        utils::SetupLanguages(Application);

        Portfolio FinancialPortfolio;

        // Main window of the application
        // LittleMarketHelper inherits from QMainWindow
        LittleMarketHelper LittleMarketHelperInterface(&FinancialPortfolio);
        LittleMarketHelperInterface.show();

        Application.exec();
    }
    catch (std::exception& Exception)
    {
        QString ErrorThrown = Exception.what();
        utils::SimpleDialog(
                    ("Fatal Error"),
                    (ErrorThrown + QString("\nThe application will be terminated, Please report this issue.")),
                    QMessageBox::Critical
                    );
    }

    return 0;
}


