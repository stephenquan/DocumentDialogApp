#include "DocumentsContract.h"
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QtAndroid>
#include "JniExceptionCheck.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentsContract::DocumentsContract(QAndroidJniEnvironment& env, QObject* parent) :
    QObject(parent),
    m_Env(env)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentsContract::~DocumentsContract()
{
    JniExceptionCheck check(m_Env);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

/*
bool DocumentsContract::isContentUri(const QString& uri)
{
    return uri.startsWith("content://");
}
*/

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::getDocumentId(const QString& uri)
{
    qDebug() << Q_FUNC_INFO << __LINE__ << "uri: " << uri;

    JniExceptionCheck check(m_Env);

    QAndroidJniObject urlString = QAndroidJniObject::fromString( uri );

    QAndroidJniObject _uri = QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri",
                "parse",
                "(Ljava/lang/String;)Landroid/net/Uri;",
                urlString.object< jstring >() );
    qDebug() << Q_FUNC_INFO << __LINE__ << "_uri.isValid: " << _uri.isValid();
    if ( !_uri.isValid() )
    {
        return QString();
    }

    QAndroidJniObject documentId = QAndroidJniObject::callStaticObjectMethod(
                "android/provider/DocumentsContract",
                "getDocumentId",
                "(Landroid/net/Uri;)Ljava/lang/String;",
                _uri.object());
    qDebug() << Q_FUNC_INFO << __LINE__ << "documentId.isValid: " << documentId.isValid();
    qDebug() << Q_FUNC_INFO << __LINE__ << "documentId.toString: " << documentId.toString();
    if ( !documentId.isValid() )
    {
        return QString();
    }

    return documentId.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
