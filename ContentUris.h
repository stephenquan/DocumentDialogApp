#ifndef __ContentUris__
#define __ContentUris__

#include <QObject>
#include <QVariant>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QUrl>
#include "InputStream.h"

class ContentUris : public QObject
{
    Q_OBJECT

public:
    ContentUris(QAndroidJniEnvironment& env, QObject* parent = nullptr);

    static bool isContentUri(const QString& uri);
    static QString parseAuthority(const QString& uri);

protected:
    QAndroidJniEnvironment& m_Env;

};

#endif
