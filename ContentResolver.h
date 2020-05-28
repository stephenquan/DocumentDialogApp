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
#include "InputStream.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class ContentResolver : public QObject
{
    Q_OBJECT

public:
    ContentResolver(QAndroidJniEnvironment& env, QObject* parent = nullptr);

    QStringList query(const QString& uri, const QString& columnName);

    QString queryForString(const QString& uri, const QString& columnName);
    qint64 queryForLongLong(const QString& uri, const QString& columnName, qint64 defaultValue);

    InputStream openInputStream(const QString& uri);

protected:
    QAndroidJniEnvironment& m_Env;
    QAndroidJniObject m_ContentResolver;

    QAndroidJniObject contentResolver();

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
