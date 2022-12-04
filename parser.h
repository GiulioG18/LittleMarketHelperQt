#ifndef PARSER_H
#define PARSER_H

#include "portfolio.h"

#include <QObject>

#include <map>


// Keep synchronized with:
// . std::map<QString, SUPPORTED_PARSER> Parser::parser_map initialization
// . std::unique_ptr<Parser> Parser::Construct(SUPPORTED_PARSER SupportedParser)
enum SUPPORTED_PARSER
{
    DEGIRO
};



class Parser : public QObject
{
    Q_OBJECT

public:

    explicit Parser(Portfolio& Portfolio, QObject* Parent = nullptr);

signals:

public:

    virtual bool ConstructPortfolioFromReportFile(bool Save) = 0;
    static const std::map<QString, SUPPORTED_PARSER>& GetParsersMap();
    static std::unique_ptr<Parser> Construct(Portfolio& Portfolio, SUPPORTED_PARSER SupportedParser);

protected:

    static std::map<QString, SUPPORTED_PARSER> parser_map;
    Portfolio& Portfolio_;
};



// DEGIRO

class DegiroParser : public Parser
{
    Q_OBJECT

public:

    explicit DegiroParser(Portfolio& Portfolio, QObject* Parent = nullptr);

signals:

public:

    bool ConstructPortfolioFromReportFile(bool Save) override;
    bool ParseFile(const QString& ReportFileName);
    bool IsCashLine(const QString& Line) const;
};

#endif // PARSER_H
