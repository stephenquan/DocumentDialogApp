#ifndef __AppFramework__
#define __AppFramework__

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

class FileInfo;
class FileFolder;

class AppFramework : public QObject
{
    Q_OBJECT

public:
    AppFramework(QObject* parent = nullptr);

    Q_INVOKABLE FileFolder* fileFolder(const QVariant& url);
    Q_INVOKABLE FileInfo* fileInfo(const QVariant& url);

    static QObject* singletonProvider(QQmlEngine *, QJSEngine *);

};

#endif
