#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontUseNativeMenuBar);
    app.setWindowIcon(QIcon(":/icons/Resources/UpdateWIZARD.ico"));
    app.setOrganizationName(QStringLiteral("Wizardsoft"));
    app.setApplicationName(QStringLiteral("Wizard"));
    app.setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "Wizard_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            app.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.showMaximized();
    return app.exec();
}
