//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "DocumentsContract.h"
#include <QtAndroid>
#include "JniExceptionCheck.h"
#include "ContentResolver.h"
#include "DocumentsContractDocument.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

const char* DocumentsContract::JCLASS = "android/provider/DocumentsContract";

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentsContract::DocumentsContract(QAndroidJniEnvironment& env, QAndroidJniObject obj) :
    AndroidObject(env, JCLASS, obj)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::getDocumentId(QAndroidJniEnvironment& env, const QString& uri)
{
    JniExceptionCheck check(env);

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
                DocumentsContract::JCLASS,
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

QString DocumentsContract::getTreeDocumentId(QAndroidJniEnvironment& env, const QString& uri)
{
    JniExceptionCheck check(env);

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
                DocumentsContract::JCLASS,
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

QString DocumentsContract::buildChildDocumentsUri(QAndroidJniEnvironment& env, const QString& authority, const QString& parentDocumentId)
{
    JniExceptionCheck check(env);

    QAndroidJniObject _authority = QAndroidJniObject::fromString( authority );
    if ( !_authority.isValid() )
    {
        return QString();
    }

    QAndroidJniObject _parentDocumentId = QAndroidJniObject::fromString( parentDocumentId );

    QAndroidJniObject childDocumentsUri = QAndroidJniObject::callStaticObjectMethod(
                DocumentsContract::JCLASS,
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

QString DocumentsContract::buildChildDocumentsUriUsingTree(QAndroidJniEnvironment& env, const QString& uri, const QString& documentId)
{
    JniExceptionCheck check(env);

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
                DocumentsContract::JCLASS,
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

QString DocumentsContract::buildDocumentUri(QAndroidJniEnvironment& env, const QString& authority, const QString& documentId)
{
    JniExceptionCheck check(env);

    QAndroidJniObject _authority = QAndroidJniObject::fromString( authority );
    QAndroidJniObject _documentId = QAndroidJniObject::fromString( documentId );

    QAndroidJniObject documentUri = QAndroidJniObject::callStaticObjectMethod(
                DocumentsContract::JCLASS,
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

QString DocumentsContract::buildDocumentUriUsingTree(QAndroidJniEnvironment& env, const QString& uri, const QString& documentId)
{
    JniExceptionCheck check(env);

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
                JCLASS,
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

QString DocumentsContract::buildTreeDocumentUri(QAndroidJniEnvironment& env, const QString& authority, const QString& documentId)
{
    JniExceptionCheck check(env);

    QAndroidJniObject _authority = QAndroidJniObject::fromString( authority );
    QAndroidJniObject _documentId = QAndroidJniObject::fromString( documentId );

    QAndroidJniObject treeDocumentUri = QAndroidJniObject::callStaticObjectMethod(
                DocumentsContract::JCLASS,
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

bool DocumentsContract::isTreeUri(QAndroidJniEnvironment& env, const QString& uri)
{
    JniExceptionCheck check(env);

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
                DocumentsContract::JCLASS,
                "isTreeUri",
                "(Landroid/net/Uri;)Z",
                _uri.object());
    return (result != JNI_FALSE);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::mimeType(QAndroidJniEnvironment& env, const QString& uri)
{
    return ContentResolver(env).queryForString(uri, DocumentsContractDocument(env).COLUMN_MIME_TYPE());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentsContract::displayName(QAndroidJniEnvironment& env, const QString& uri)
{
    return ContentResolver(env).queryForString(uri, DocumentsContractDocument(env).COLUMN_DISPLAY_NAME());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

qint64 DocumentsContract::size(QAndroidJniEnvironment& env, const QString& uri)
{
    return ContentResolver(env).queryForLongLong(uri, DocumentsContractDocument(env).COLUMN_DISPLAY_NAME(), 0);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList DocumentsContract::documentIds(QAndroidJniEnvironment& env, const QString& uri)
{
    return ContentResolver(env).query(uri, DocumentsContractDocument(env).COLUMN_DOCUMENT_ID());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentsContract::exists(QAndroidJniEnvironment& env, const QString& uri)
{
    return documentIds(env, uri).length() > 0;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList DocumentsContract::childDocumentIds(QAndroidJniEnvironment& env, const QString& uri)
{
    QString treeDocumentId = getTreeDocumentId(env, uri);
    QString documentId = getDocumentId(env, uri);

    QString childDocumentsUri = buildChildDocumentsUriUsingTree(env, uri, !treeDocumentId.isEmpty() ? treeDocumentId : documentId);
    if (childDocumentsUri.isEmpty() || childDocumentsUri.isNull())
    {
        return QStringList();
    }

    QStringList result = ContentResolver(env).query(childDocumentsUri,  DocumentsContractDocument(env).COLUMN_DOCUMENT_ID());
    return result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList DocumentsContract::childDocumentUris(QAndroidJniEnvironment& env, const QString &uri)
{
    QStringList results;
    foreach (const QString childDocumentId, childDocumentIds(env, uri))
    {
        QString childDocumentUri = buildDocumentUriUsingTree(env, uri, childDocumentId);
        results.append(childDocumentUri);
    }
    return results;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentsContract::isDirectory(QAndroidJniEnvironment& env, const QString& uri)
{
    QString type = mimeType(env, uri);
    QString mimeTypeDir = DocumentsContractDocument(env).MIME_TYPE_DIR();
    bool result = (mimeTypeDir == type) || type.isEmpty() || type.isNull();
    return result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentsContract::isFile(QAndroidJniEnvironment& env, const QString& uri)
{
    QString type = ContentResolver(env).queryForString(uri, DocumentsContractDocument(env).COLUMN_MIME_TYPE());
    QString mimeTypeDir = DocumentsContractDocument(env).MIME_TYPE_DIR();
    bool result = (mimeTypeDir != type) && !type.isEmpty() && !type.isNull();
    return result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

