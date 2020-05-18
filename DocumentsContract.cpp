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

QString DocumentsContract::getDocumentId(const QString& uri)
{
    JniExceptionCheck check(m_Env);

    QAndroidJniObject urlString = QAndroidJniObject::fromString( uri );

    QAndroidJniObject _uri = QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri",
                "parse",
                "(Ljava/lang/String;)Landroid/net/Uri;",
                urlString.object< jstring >() );
    if ( !_uri.isValid() )
    {
        return QString();
    }

    QAndroidJniObject documentId = QAndroidJniObject::callStaticObjectMethod(
                "android/provider/DocumentsContract",
                "getDocumentId",
                "(Landroid/net/Uri;)Ljava/lang/String;",
                _uri.object());
    if ( !documentId.isValid() )
    {
        return QString();
    }

    return documentId.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::getTreeDocumentId(const QString& uri)
{
    JniExceptionCheck check(m_Env);

    QAndroidJniObject urlString = QAndroidJniObject::fromString( uri );

    QAndroidJniObject _uri = QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri",
                "parse",
                "(Ljava/lang/String;)Landroid/net/Uri;",
                urlString.object< jstring >() );
    if ( !_uri.isValid() )
    {
        return QString();
    }

    QAndroidJniObject treeDocumentId = QAndroidJniObject::callStaticObjectMethod(
                "android/provider/DocumentsContract",
                "getTreeDocumentId",
                "(Landroid/net/Uri;)Ljava/lang/String;",
                _uri.object());
    if ( !treeDocumentId.isValid() )
    {
        return QString();
    }

    return treeDocumentId.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
