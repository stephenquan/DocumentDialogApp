#ifndef __ContentResolver__
#define __ContentResolver__

#include <QObject>
#include <QVariant>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include "InputStream.h"

class ContentResolver : public QObject
{
    Q_OBJECT

public:
    ContentResolver(QAndroidJniEnvironment& env, QObject* parent = nullptr);
    ~ContentResolver();

    static bool isContentUri(const QString& uri);

    QVariant query(const QString& uri, const QString& columnName);
    InputStream openInputStream(const QString& uri);

protected:
    QAndroidJniEnvironment& m_Env;
    QAndroidJniObject m_ContentResolver;

    QAndroidJniObject contentResolver();
    InputStream _openInputStream(const QString& uri);

};

#endif
