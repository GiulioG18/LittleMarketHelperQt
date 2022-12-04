#ifndef UTILS_H
#define UTILS_H

#endif // UTILS_H

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>
// TODO: Create a macro for debugging
#include <QDebug>

#define TRANSLATE(arg) tr(arg)

namespace utils {

void inline SetupLanguages(const QApplication& Application)
{
    QTranslator Translator;
    const QStringList UserInterfaceLanguages = QLocale::system().uiLanguages();

    for (const QString &Locale : UserInterfaceLanguages)
    {
        const QString BaseName = "LMH_" + QLocale(Locale).name();

        if (Translator.load(":/i18n/" + BaseName))
        {
            Application.installTranslator(&Translator);
            break;
        }
    }
}

void inline SimpleDialog(const QString& WindowTitle, const QString& Message, QMessageBox::Icon Icon)
{
    QMessageBox SimpleDialog;
    SimpleDialog.setWindowTitle(WindowTitle);
    SimpleDialog.setText(Message);
    SimpleDialog.setIcon(Icon);
    SimpleDialog.exec();
}

} // utils




