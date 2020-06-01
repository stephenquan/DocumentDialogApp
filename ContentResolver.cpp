//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "ContentResolver.h"
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QtAndroid>
#include "DocumentsContract.h"
#include "DocumentsContractDocument.h"
#include "JniExceptionCheck.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

const char* ContentResolver::JCLASS = "android/content/ContentResolver";

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

ContentResolver::ContentResolver(QAndroidJniEnvironment& env) :
    AndroidObject(env, JCLASS, contentResolver(env))
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

ContentResolver::ContentResolver(ContentResolver& other) :
    AndroidObject(other.m_Env, JCLASS, other)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

ContentResolver::ContentResolver(ContentResolver&& other) :
    AndroidObject(other.m_Env, JCLASS, other)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList ContentResolver::query(const QString& uri, const QString& columnName)
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return QStringList();
    }

    QAndroidJniObject urlString = QAndroidJniObject::fromString( uri );

    QAndroidJniObject _uri = QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri",
                "parse",
                "(Ljava/lang/String;)Landroid/net/Uri;",
                urlString.object< jstring >() );
    if ( !_uri.isValid() )
    {
        return QStringList();
    }

    QAndroidJniObject _columnName = QAndroidJniObject::fromString(columnName);
    if ( !_columnName.isValid() )
    {
        return QStringList();
    }

    jobjectArray stringArray = m_Env->NewObjectArray( 1, m_Env->FindClass("java/lang/String"), nullptr);
    m_Env->SetObjectArrayElement( stringArray, 0, _columnName.object<jstring>() );

    QAndroidJniObject cursor = callObjectMethod(
            "query",
            "(Landroid/net/Uri;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;Landroid/os/CancellationSignal;)Landroid/database/Cursor;",
            _uri.object(),
            stringArray,
            nullptr,
            nullptr,
            nullptr,
            nullptr
            );
    if ( !cursor.isValid() )
    {
        return QStringList();
    }

    QStringList list;

    jboolean ok = cursor.callMethod<jboolean>( "moveToFirst" );
    while ( ok )
    {
        QAndroidJniObject str = cursor.callObjectMethod( "getString", "(I)Ljava/lang/String;", 0 );
        list.append(str.toString());
        ok = cursor.callMethod<jboolean>( "moveToNext" );
    }

    return list;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

InputStream ContentResolver::openInputStream(const QString& uri)
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return InputStream(m_Env);
    }

    QAndroidJniObject _uri = QAndroidJniObject::fromString(uri);
    if (!_uri.isValid())
    {
        return InputStream(m_Env);
    }

    QAndroidJniObject __uri = QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri",
                "parse",
                "(Ljava/lang/String;)Landroid/net/Uri;",
                _uri.object<jstring>() );
    if (!__uri.isValid())
    {
        return InputStream(m_Env);
    }

    QAndroidJniObject _inputStream = callObjectMethod(
                "openInputStream",
                "(Landroid/net/Uri;)Ljava/io/InputStream;",
                __uri.object());

    return InputStream(m_Env, nullptr, _inputStream);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString ContentResolver::queryForString(const QString& uri, const QString& columnName)
{
    QStringList results = query(uri, columnName);
    QString result = results.length() > 0 ? results[0] : QString();
    return result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

qint64 ContentResolver::queryForLongLong(const QString& uri, const QString& columnName, qint64 defaultValue)
{
    QString resultString = queryForString(uri, columnName);
    bool ok = false;
    qint64 resultLongLong = resultString.toLongLong(&ok);
    return ok ? resultLongLong : defaultValue;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QAndroidJniObject ContentResolver::contentResolver(QAndroidJniEnvironment& env)
{
    JniExceptionCheck check(env);

    QAndroidJniObject context = QtAndroid::androidContext();
    if ( !context.isValid() )
    {
        return QAndroidJniObject();
    }

    QAndroidJniObject contentResolver = context.callObjectMethod(
                "getContentResolver",
                "()Landroid/content/ContentResolver;" );
    return contentResolver;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
