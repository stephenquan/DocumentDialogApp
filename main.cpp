#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "DocumentDialog.h"
#include "FileInfo.h"
#include "FileFolder.h"
#include "AppFramework.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("StephenQuan");
    QCoreApplication::setOrganizationDomain("Stephen.Quan");
    QCoreApplication::setApplicationName("DocumentDialogApp");

    QGuiApplication app(argc, argv);

    qmlRegisterType<DocumentDialog>("StephenQuan", 1, 0, "DocumentDialog");
    qmlRegisterType<FileInfo>("StephenQuan", 1, 0, "FileInfo");
    qmlRegisterType<FileFolder>("StephenQuan", 1, 0, "FileFolder");
    qmlRegisterSingletonType<AppFramework>("StephenQuan", 1, 0, "AppFramework", AppFramework::singletonProvider);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
