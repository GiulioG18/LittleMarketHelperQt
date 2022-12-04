#include "mainbutton.h"

#include <QApplication>

#include <stdexcept>



Exit::Exit(QWidget* Parent)
    :
      MainButton(Parent)
{
    QObject::connect(this,  &QPushButton::clicked, this, &Exit::Clicked);
}

void Exit::Clicked()
{
    Q_ASSERT(MainButton::Portfolio_);
    QApplication::instance()->quit();
}

void Exit::Update()
{
    throw std::runtime_error("Exit button should not be updated!");
}

