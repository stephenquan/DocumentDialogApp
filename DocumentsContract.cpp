//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "DocumentsContract.h"
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QtAndroid>
#include "JniExceptionCheck.h"
#include "ContentResolver.h"
#include "DocumentsContractDocument.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentsContract::DocumentsContract(QAndroidJniEnvironment& env, QObject* parent) :
    AndroidObject(env, parent)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::getDocumentId(const QString& uri) const
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
                jclass(),
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

QString DocumentsContract::getTreeDocumentId(const QString& uri) const
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
                jclass(),
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

QString DocumentsContract::buildChildDocumentsUri(const QString& authority, const QString& parentDocumentId) const
{
    JniExceptionCheck check(m_Env);

    QAndroidJniObject _authority = QAndroidJniObject::fromString( authority );
    if ( !_authority.isValid() )
    {
        return QString();
    }

    QAndroidJniObject _parentDocumentId = QAndroidJniObject::fromString( parentDocumentId );

    QAndroidJniObject childDocumentsUri = QAndroidJniObject::callStaticObjectMethod(
                jclass(),
                "buildChildDocumentsUri",
                "(Ljava/lang/String;Ljava/lang/String;)Landroid/net/Uri;",
                _authority.object(),
                _parentDocumentId.object());
    if ( !childDocumentsUri.isValid() )
    {
        return QString();
    }

    return childDocumentsUri.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::buildChildDocumentsUriUsingTree(const QString& uri, const QString& documentId) const
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
                jclass(),
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

QString DocumentsContract::buildDocumentUri(const QString& authority, const QString& documentId) const
{
    JniExceptionCheck check(m_Env);

    QAndroidJniObject _authority = QAndroidJniObject::fromString( authority );
    QAndroidJniObject _documentId = QAndroidJniObject::fromString( documentId );

    QAndroidJniObject documentUri = QAndroidJniObject::callStaticObjectMethod(
                jclass(),
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

QString DocumentsContract::buildDocumentUriUsingTree(const QString& uri, const QString& documentId) const
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
                jclass(),
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

QString DocumentsContract::buildTreeDocumentUri(const QString& authority, const QString& documentId) const
{
    JniExceptionCheck check(m_Env);

    QAndroidJniObject _authority = QAndroidJniObject::fromString( authority );
    QAndroidJniObject _documentId = QAndroidJniObject::fromString( documentId );

    QAndroidJniObject treeDocumentUri = QAndroidJniObject::callStaticObjectMethod(
                jclass(),
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

bool DocumentsContract::isTreeUri(const QString& uri) const
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
                jclass(),
                "isTreeUri",
                "(Landroid/net/Uri;)Z",
                _uri.object());
    return (result != JNI_FALSE);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::mimeType(const QString& uri) const
{
    return ContentResolver(m_Env).queryForString(uri, DocumentsContractDocument(m_Env).COLUMN_MIME_TYPE());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::displayName(const QString& uri) const
{
    return ContentResolver(m_Env).queryForString(uri, DocumentsContractDocument(m_Env).COLUMN_DISPLAY_NAME());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

qint64 DocumentsContract::size(const QString& uri) const
{
    return ContentResolver(m_Env).queryForLongLong(uri, DocumentsContractDocument(m_Env).COLUMN_DISPLAY_NAME(), 0);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList DocumentsContract::documentIds(const QString& uri) const
{
    return ContentResolver(m_Env).query(uri, DocumentsContractDocument(m_Env).COLUMN_DOCUMENT_ID());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentsContract::exists(const QString& uri) const
{
    return documentIds(uri).length() > 0;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList DocumentsContract::childDocumentIds(const QString& uri) const
{
    QString treeDocumentId = getTreeDocumentId(uri);

    QString childDocumentsUri = buildChildDocumentsUriUsingTree(uri, treeDocumentId);
    if (childDocumentsUri.isEmpty() || childDocumentsUri.isNull())
    {
        return QStringList();
    }

    QStringList result = ContentResolver(m_Env).query(childDocumentsUri,  DocumentsContractDocument(m_Env).COLUMN_DOCUMENT_ID());
    return result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList DocumentsContract::childDocumentUris(const QString &uri) const
{
    QStringList results;
    foreach (const QString childDocumentId, childDocumentIds(uri))
    {
        QString childDocumentUri = buildDocumentUriUsingTree(uri, childDocumentId);
        results.append(childDocumentUri);
    }
    return results;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentsContract::isFolder(const QString& uri) const
{
    QString type = mimeType(uri);
    QString mimeTypeDir = DocumentsContractDocument(m_Env).MIME_TYPE_DIR();
    bool result = (mimeTypeDir == type) || type.isEmpty() || type.isNull();
    return result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentsContract::isFile(const QString& uri) const
{
    QString type = ContentResolver(m_Env).queryForString(uri, DocumentsContractDocument(m_Env).COLUMN_MIME_TYPE());
    QString mimeTypeDir = DocumentsContractDocument(m_Env).MIME_TYPE_DIR();
    bool result = (mimeTypeDir != type) && !type.isEmpty() && !type.isNull();
    return result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
