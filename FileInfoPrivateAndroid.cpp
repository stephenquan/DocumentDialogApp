
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QQmlEngine>
#include <QRegExp>
#include <QDebug>

#include "FileFolderPrivate.h"
#include "FileFolder.h"
#include "FileInfoPrivateAndroid.h"
#include "ContentUris.h"
#include "ContentResolver.h"
#include "DocumentsContract.h"
#include "DocumentsContractDocument.h"
#include "JniExceptionCheck.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

FileInfoPrivateAndroid::FileInfoPrivateAndroid(QObject* parent) :
    FileInfoPrivate(parent)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfoPrivateAndroid::absoluteFilePath() const
{
    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::absoluteFilePath();
    }

    return m_Url.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfoPrivateAndroid::absolutePath() const
{
    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::absolutePath();
    }

    return m_Url.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfoPrivateAndroid::baseName() const
{
    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::baseName();
    }

    return QFileInfo(fileName()).baseName();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool FileInfoPrivateAndroid::exists() const
{
    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::exists();
    }

    return isFile() || isDir();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfoPrivateAndroid::displayName() const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::displayName();
    }

    QString displayName = DocumentsContract(env).displayName(url().toString());
    return displayName;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfoPrivateAndroid::fileName() const
{
    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::fileName();
    }

    return m_Url.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfoPrivateAndroid::filePath() const
{
    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::filePath();
    }

    return m_Url.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

FileFolder* FileInfoPrivateAndroid::folder() const
{
    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::folder();
    }

    QString contentUri = url().toString();
    QString scheme;
    QString authority;
    QString treeOrDocument;
    QString type;
    QStringList path;
    if (!ContentUris::parseContentUri(contentUri, scheme, authority, treeOrDocument, type, path))
    {
        return nullptr;
    }
    path.pop_back();
    QString treeDocumentUri = ContentUris::buildContentUri(scheme, authority, "tree", type, path);

    FileFolder* fileFolder = new FileFolder();
    fileFolder->setPath(treeDocumentUri);
    QQmlEngine::setObjectOwnership(fileFolder, QQmlEngine::JavaScriptOwnership);
    return fileFolder;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool FileInfoPrivateAndroid::isDir() const
{
    QAndroidJniEnvironment env;
    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::isDir();
    }

    return DocumentsContract(env).isFolder(url().toString());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool FileInfoPrivateAndroid::isFile() const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::isDir();
    }

    return DocumentsContract(env).isFile(url().toString());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

qint64 FileInfoPrivateAndroid::size() const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::size();
    }

    return DocumentsContract(env).size(url().toString());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QByteArray FileInfoPrivateAndroid::readAll() const
{
    QAndroidJniEnvironment env;
    JniExceptionCheck check(env);

    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::readAll();
    }

    QString documentId = DocumentsContract(env).getDocumentId(url().toString());
    if (documentId.isEmpty() || documentId.isNull())
    {
        return QByteArray();
    }

    InputStream inputStream = ContentResolver(env).openInputStream(url().toString());
    if (!inputStream.isValid())
    {
        return QByteArray();
    }

    QByteArray fileBytes;
    QByteArray more = inputStream.read(1024);
    while (more.length() > 0)
    {
        fileBytes.append(more);
        more = inputStream.read(1024);
    }

    inputStream.close();

    return fileBytes;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void FileInfoPrivateAndroid::setUrl(const QVariant& url)
{
    QString _url = url.toString();

    QAndroidJniEnvironment env;
    JniExceptionCheck check(env);

    if (!ContentUris::isContentUri(_url))
    {
        return FileInfoPrivate::setUrl(_url);
    }

    /*
    QVariant data = ContentResolver(env).query(_url, "android/provider/MediaStore$MediaColumns", "DATA");
    if (data.isValid() && !data.isNull() && !data.toString().isEmpty())
    {
        _url = data.toString();
    }
    */

    FileInfoPrivate::setUrl(_url);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QVariant FileInfoPrivateAndroid::extra() const
{
    QAndroidJniEnvironment env;
    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::extra();
    }

    QString _uri = url().toString();

    QVariantMap map;

    QString documentId = DocumentsContract(env).getDocumentId(_uri);
    map["DocumentId"] = documentId;

    QString treeDocumentId = DocumentsContract(env).getTreeDocumentId(_uri);
    map["TreeDocumentId"] = treeDocumentId;

    if (!documentId.isEmpty() && !documentId.isNull())
    {
        map["MediaStore$MediaColumns.SIZE"] = ContentResolver(env).query(_uri, AndroidObject::staticString("android/provider/MediaStore$MediaColumns", "SIZE", env));
        map["MediaStore$MediaColumns.MIME_TYPE"] = ContentResolver(env).query(_uri, AndroidObject::staticString("android/provider/MediaStore$MediaColumns", "MIME_TYPE", env));
        map["MediaStore$MediaColumns.DISPLAY_NAME"] = ContentResolver(env).query(_uri, AndroidObject::staticString("android/provider/MediaStore$MediaColumns", "DISPLAY_NAME", env));
        map["DocumentsContract$Document.COLUMN_DOCUMENT_ID"] = ContentResolver(env).query(_uri, DocumentsContractDocument(env).COLUMN_DOCUMENT_ID());
    }

    if (!treeDocumentId.isEmpty() && !treeDocumentId.isNull())
    {
        QString childDocumentsUri = DocumentsContract(env).buildChildDocumentsUriUsingTree(_uri, treeDocumentId);
        map["ChildDocumentsUri"] = childDocumentsUri;

        //QStringList childDocumentIds = ContentResolver(env).query(childDocumentsUri,  "android/provider/DocumentsContract$Document", "COLUMN_DOCUMENT_ID");
        QStringList childDocumentIds = ContentResolver(env).query(childDocumentsUri,  DocumentsContractDocument(env).COLUMN_DOCUMENT_ID());
        if (childDocumentIds.length() > 0)
        {
            QVariantList childDocumentList;
            foreach (QString childDocumentId, childDocumentIds)
            {
                QVariantMap childDocument;
                QString childDocumentUri = DocumentsContract(env).buildDocumentUriUsingTree(_uri, childDocumentId);
                QString authority = QUrl(_uri).host();
                childDocument["authority"] = authority;
                childDocument["documentId"] = childDocumentId;
                childDocument["documentUri"] = childDocumentUri;
                childDocument["documentId2"] = DocumentsContract(env).getDocumentId(childDocumentId);
                childDocument["treeDocumentId"] = DocumentsContract(env).getDocumentId(childDocumentId);
                childDocument["displayName"] = ContentResolver(env).query(childDocumentUri, AndroidObject::staticString("android/provider/MediaStore$MediaColumns", "DISPLAY_NAME", env));
                childDocument["size"] = ContentResolver(env).query(childDocumentUri, AndroidObject::staticString("android/provider/MediaStore$MediaColumns", "SIZE", env));
                childDocument["mimeType"] = ContentResolver(env).query(childDocumentUri, AndroidObject::staticString("android/provider/MediaStore$MediaColumns", "MIME_TYPE", env));
                //childDocument["DocumentsContract$Document.COLUMN_DOCUMENT_ID"] = ContentResolver(env).query(childDocumentUri, "android/provider/DocumentsContract$Document", "COLUMN_DOCUMENT_ID");
                childDocument["DocumentsContract$Document.COLUMN_DOCUMENT_ID"] = ContentResolver(env).query(childDocumentUri, DocumentsContractDocument(env).COLUMN_DOCUMENT_ID());
                childDocument["buildDocumentUri"] = DocumentsContract(env).buildDocumentUri(authority, childDocumentId);
                childDocument["buildDocumentUriUsingTree"] = DocumentsContract(env).buildDocumentUriUsingTree(_uri, childDocumentId);
                childDocumentList.append(childDocument);
            }
            map["childDocuments"] = childDocumentList;
        }
    }

    map["Version"] = 20200527;
    return map;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
