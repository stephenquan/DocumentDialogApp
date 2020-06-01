//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __ContentResolver__
#define __ContentResolver__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QObject>
#include <QVariant>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include "AndroidObject.h"
#include "InputStream.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class ContentResolver : public AndroidObject
{
public:
    ContentResolver(QAndroidJniEnvironment& env);
    ContentResolver(ContentResolver& other);
    ContentResolver(ContentResolver&& other);

    static const char* JCLASS;

    QStringList query(const QString& uri, const QString& columnName);
    QString queryForString(const QString& uri, const QString& columnName);
    qint64 queryForLongLong(const QString& uri, const QString& columnName, qint64 defaultValue);
    InputStream openInputStream(const QString& uri);

    static QAndroidJniObject contentResolver(QAndroidJniEnvironment& env);

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
