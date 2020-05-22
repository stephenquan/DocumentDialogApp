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

QString DocumentsContract::buildChildDocumentsUriUsingTree(const QString& uri, const QString& documentId)
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

    QAndroidJniObject _documentId = QAndroidJniObject::fromString( documentId );

    QAndroidJniObject childDocumentsUri = QAndroidJniObject::callStaticObjectMethod(
                "android/provider/DocumentsContract",
                "buildChildDocumentsUriUsingTree",
                "(Landroid/net/Uri;Ljava/lang/String;)Landroid/net/Uri;",
                _uri.object(),
                _documentId.object());
    if ( !childDocumentsUri.isValid() )
    {
        return QString();
    }

    return childDocumentsUri.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::buildDocumentUri(const QString& authority, const QString& documentId)
{
    JniExceptionCheck check(m_Env);

    QAndroidJniObject _authority = QAndroidJniObject::fromString( authority );
    QAndroidJniObject _documentId = QAndroidJniObject::fromString( documentId );

    QAndroidJniObject documentUri = QAndroidJniObject::callStaticObjectMethod(
                "android/provider/DocumentsContract",
                "buildDocumentUri",
                "(Ljava/lang/String;Ljava/lang/String;)Landroid/net/Uri;",
                _authority.object(),
                _documentId.object());
    if ( !documentUri.isValid() )
    {
        return QString();
    }

    return documentUri.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::buildDocumentUriUsingTree(const QString& uri, const QString& documentId)
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

    QAndroidJniObject _documentId = QAndroidJniObject::fromString( documentId );

    QAndroidJniObject documentsUri = QAndroidJniObject::callStaticObjectMethod(
                "android/provider/DocumentsContract",
                "buildDocumentUriUsingTree",
                "(Landroid/net/Uri;Ljava/lang/String;)Landroid/net/Uri;",
                _uri.object(),
                _documentId.object());
    if ( !documentsUri.isValid() )
    {
        return QString();
    }

    return documentsUri.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::buildTreeDocumentUri(const QString& authority, const QString& documentId)
{
    JniExceptionCheck check(m_Env);

    QAndroidJniObject _authority = QAndroidJniObject::fromString( authority );
    QAndroidJniObject _documentId = QAndroidJniObject::fromString( documentId );

    QAndroidJniObject treeDocumentUri = QAndroidJniObject::callStaticObjectMethod(
                "android/provider/DocumentsContract",
                "buildTreeDocumentUri",
                "(Ljava/lang/String;Ljava/lang/String;)Landroid/net/Uri;",
                _authority.object(),
                _documentId.object());
    if ( !treeDocumentUri.isValid() )
    {
        return QString();
    }

    return treeDocumentUri.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentsContract::isTreeUri(const QString& uri)
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
        return false;
    }

    jboolean result = QAndroidJniObject::callStaticMethod<jboolean>(
                "android/provider/DocumentsContract",
                "isTreeUri",
                "(Landroid/net/Uri;)Z",
                _uri.object());
    return (result != JNI_FALSE);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
