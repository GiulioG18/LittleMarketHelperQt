#ifndef MAINACTION_H
#define MAINACTION_H

#include "portfolio.h"

#include <QPushButton>

// BASE: This class is the base for every new main button added to the main window.
// Every new main button added has to be initialized inside the main window constructor.
// To be initialized, the new button Name has to implement:
//  . Name::Name(QWidget* Parent = nullptr);
//  . Name::Clicked()
//  . Name::Update()

// Helper macro to declare a new button
#define DECLARE_MAIN_BUTTON(Name)                       \
    class Name : public MainButton                      \
    {                                                   \
        friend class LittleMarketHelper;                \
        Q_OBJECT                                        \
    public:                                             \
        Name(QWidget* Parent = nullptr);                \
    protected:                                          \
        virtual void Clicked() override;                \
        virtual void Update() override;                 \
    };                                                  \



class MainButton : public QPushButton
{
    friend class LittleMarketHelper;

    Q_OBJECT

public:

    MainButton(QWidget* Parent = nullptr);

protected:

    void SetPortfolio(Portfolio* Portfolio);

    virtual void Clicked() = 0;
    virtual void Update() = 0;

    void SetNotInitializedTooltip();
    void SetNotAvailableTooltip();

protected:

    Portfolio* Portfolio_;
};



// Buttons declaration

DECLARE_MAIN_BUTTON(Initialize);
DECLARE_MAIN_BUTTON(Edit);
DECLARE_MAIN_BUTTON(Calibrate);
DECLARE_MAIN_BUTTON(History);
DECLARE_MAIN_BUTTON(Help);
DECLARE_MAIN_BUTTON(About);
DECLARE_MAIN_BUTTON(Exit);




#endif // MAINACTION_H



