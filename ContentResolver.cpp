#include "ContentResolver.h"
#include <QAndroidJniObject>
#include <QtAndroid>
#include "JniEnvironment.h"

ContentResolver::ContentResolver(QObject* parent) :
    QObject(parent)
{
}

bool ContentResolver::isContentUri(const QString& uri)
{
    return uri.startsWith("content://");
}

QVariant ContentResolver::queryContentUri(const QString& uri, const QString& columnName)
{
    JniEnvironment env;

    QAndroidJniObject urlString = QAndroidJniObject::fromString( uri );

    QAndroidJniObject _uri = QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri",
                "parse",
                "(Ljava/lang/String;)Landroid/net/Uri;",
                urlString.object< jstring >() );
    if ( !_uri.isValid() )
    {
        return QVariant();
    }

    QAndroidJniObject context = QtAndroid::androidContext();
    if ( !context.isValid() )
    {
        return QVariant();
    }

    QAndroidJniObject contentResolver = context.callObjectMethod( "getContentResolver", "()Landroid/content/ContentResolver;" );
    if ( !contentResolver.isValid() )
    {
        return QVariant();
    }

    QAndroidJniObject _columnName = QAndroidJniObject::getStaticObjectField<jstring>( "android/provider/MediaStore$MediaColumns", columnName.toUtf8().data() );
    if ( !_columnName.isValid() )
    {
        return QVariant();
    }

    jobjectArray stringArray = env->NewObjectArray( 1, env->FindClass("java/lang/String"), nullptr);
    env->SetObjectArrayElement( stringArray, 0, _columnName.object<jstring>() );

    QAndroidJniObject cursor = contentResolver.callObjectMethod(
            "query",
            "(Landroid/net/Uri;[Ljava/lang/String;Landroid/os/Bundle;Landroid/os/CancellationSignal;)Landroid/database/Cursor;",
            _uri.object(),
            stringArray,
            nullptr,
            nullptr
            );
    if ( !cursor.isValid() )
    {
        return QVariant();
    }

    jboolean ok = cursor.callMethod<jboolean>( "moveToFirst" );
    if ( !ok )
    {
        return QVariant();
    }

    QAndroidJniObject str = cursor.callObjectMethod( "getString", "(I)Ljava/lang/String;", 0 );
    if ( !ok )
    {
        return QVariant();
    }

    return str.toString();
}
