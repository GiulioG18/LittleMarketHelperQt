#include "parser.h"
#include "utils.h"

#include <QTextStream>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>



// PARSER base

Parser::Parser(Portfolio& Portfolio, QObject* Parent)
    :
      QObject{Parent},
      Portfolio_(Portfolio)
{
}

const std::map<QString, SUPPORTED_PARSER>& Parser::GetParsersMap()
{
    return Parser::parser_map;
}

std::unique_ptr<Parser> Parser::Construct(Portfolio& Portfolio, SUPPORTED_PARSER SupportedParser)
{
    std::unique_ptr<Parser> Output;

    switch (SupportedParser)
    {
    case SUPPORTED_PARSER::DEGIRO: Output = std::make_unique<DegiroParser>(Portfolio); break;

    default: Q_ASSERT(false);
    }

    return Output;
}

std::map<QString, SUPPORTED_PARSER> Parser::parser_map
{
    { "Degiro", DEGIRO}
};




// DEGIRO

// TODO: Inform user that only EUR is supported and he should edit file otherwise

DegiroParser::DegiroParser(Portfolio& Portfolio, QObject* Parent)
    :
      Parser{Portfolio, Parent}
{

}

bool DegiroParser::ConstructPortfolioFromReportFile(bool Save)
{
    bool Status = true;

    // Get file
    QString DownloadFolderPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString ReportFileName = QFileDialog::getOpenFileName(
                Q_NULLPTR,
                TRANSLATE("Portfolio Report"),
                DownloadFolderPath,
                TRANSLATE("DEGIRO Reports (*.csv)"));

    if (ReportFileName.isEmpty())
    {
        Status = false;
    }
    else
    {
        // Initialize Products_
        Status = ParseFile(ReportFileName);

        // Value_ is set only during updates
        Portfolio_.Value() = 0.0;

        Portfolio_.SetSave(Save);
        Portfolio_.SetInitialized(true);
    }

    return Status;
}

bool DegiroParser::ParseFile(const QString& ReportFileName)
{
    bool Status = true;

    // Create stream from file
    QFile ReportFile(ReportFileName);
    if (!ReportFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        utils::SimpleDialog(TRANSLATE("Portfolio Parser"), TRANSLATE("Could not properly read the file."), QMessageBox::Critical);
        return false;
    }

    QTextStream ReportStream(&ReportFile);
    QString Line;

    // Dirty solution to skip header lines (Not safe..)
    ReportStream.readLineInto(&Line);
    ReportStream.readLineInto(&Line);

    // Skip cash lines
    while(IsCashLine(Line))
    {
        ReportStream.readLineInto(&Line);
    }

    // Parse products
    do
    {
        // Adapt to older version of parser who used std::string
        std::string CurrentLine = Line.toStdString();

        size_t SectionStart, SectionEnd;

        // Name
        SectionStart = 0;
        SectionEnd = CurrentLine.find_first_of(',', SectionStart + 1);

        QString Name = QString::fromStdString(std::string(CurrentLine.begin() + SectionStart, CurrentLine.begin() + SectionEnd));

        // _Isin
        SectionStart = SectionEnd + 1;
        SectionEnd = CurrentLine.find_first_of(',', SectionStart + 1);

        QString Isin = QString::fromStdString(std::string(CurrentLine.begin() + SectionStart, CurrentLine.begin() + SectionEnd));

        // _Quantity
        SectionStart = SectionEnd + 1;
        SectionEnd = CurrentLine.find_first_of(',', SectionStart + 1);

        int Quantity = std::stol(std::string(CurrentLine.begin() + SectionStart, CurrentLine.begin() + SectionEnd));

        // _Price
        SectionStart = SectionEnd + 2; // + 2 since there is a " character after the ,
        SectionEnd = CurrentLine.find_first_of('"', SectionStart + 1);

        std::replace(CurrentLine.begin() + SectionStart, CurrentLine.begin() + SectionEnd, ',', '.');	 // Replace , with .

        double Price = std::stof(std::string(CurrentLine.begin() + SectionStart, CurrentLine.begin() + SectionEnd));

        // _OpenPosition
        SectionStart = SectionEnd + 1;
        SectionStart = CurrentLine.find_first_of('"', SectionStart + 1) + 1; // Set SectionStart at the right point
        SectionEnd = CurrentLine.find_first_of('"', SectionStart + 1);

        std::replace(CurrentLine.begin() + SectionStart, CurrentLine.begin() + SectionEnd, ',', '.');	 // Replace , with .

        double OpenPosition = std::stof(std::string(CurrentLine.begin() + SectionStart, CurrentLine.begin() + SectionEnd));

        Portfolio_.Products().emplaceBack(Name, Isin, Quantity, Price, OpenPosition, 0, true);

    } while (ReportStream.readLineInto(&Line));

    return Status;
}

bool DegiroParser::IsCashLine(const QString& Line) const
{
    // Cash line starts with CASH
    return Line.left(4) == "CASH";
}




