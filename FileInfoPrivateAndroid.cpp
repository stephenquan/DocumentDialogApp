
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QQmlEngine>
#include <QRegExp>

#include "FileFolderPrivate.h"
#include "FileFolder.h"
#include "FileInfoPrivateAndroid.h"
#include "ContentUris.h"
#include "ContentResolver.h"
#include "DocumentsContract.h"
#include "DocumentsContractDocument.h"
#include "JniExceptionCheck.h"
#include "DocumentFile.h"

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
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::exists();
    }

    DocumentFile documentFile = DocumentFile::fromUri(env, url().toString());
    return documentFile.exists();
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

    DocumentFile documentFile = DocumentFile::fromUri(env, url().toString());
    return documentFile.getName();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfoPrivateAndroid::fileName() const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::fileName();
    }

    return url().toString();
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

    return url().toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

FileFolder* FileInfoPrivateAndroid::folder() const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::folder();
    }

    DocumentFile documentFile = DocumentFile::fromUri(env, url().toString());
    if (!documentFile.isValid())
    {
        return nullptr;
    }

    DocumentFile parentFile = documentFile.getParentFile();
    if (!parentFile.isValid())
    {
        return nullptr;
    }

    FileFolder* fileFolder = new FileFolder();
    fileFolder->setPath(parentFile.getUri());
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

    DocumentFile documentFile = DocumentFile::fromUri(env, url().toString());
    return documentFile.isDirectory();
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

    DocumentFile documentFile = DocumentFile::fromUri(env, url().toString());
    return documentFile.isFile();
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

    DocumentFile documentFile = DocumentFile::fromUri(env, url().toString());
    return documentFile.length();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfoPrivateAndroid::type() const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::type();
    }

    DocumentFile documentFile = DocumentFile::fromUri(env, url().toString());
    QString _type = documentFile.getType();
    return _type;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QByteArray FileInfoPrivateAndroid::readAll() const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(url().toString()))
    {
        return FileInfoPrivate::readAll();
    }

    QString documentId = DocumentsContract::getDocumentId(env, url().toString());
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
    QAndroidJniEnvironment env;
    JniExceptionCheck check(env);

    QString _url = url.toString();

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

    return QVariant();

    QString _uri = url().toString();

    QVariantMap map;

    QString documentId = DocumentsContract::getDocumentId(env, _uri);
    map["DocumentId"] = documentId;

    QString treeDocumentId = DocumentsContract::getTreeDocumentId(env, _uri);
    map["TreeDocumentId"] = treeDocumentId;

    if (!documentId.isEmpty() && !documentId.isNull())
    {
        map["MediaStore$MediaColumns.SIZE"] = ContentResolver(env).query(_uri, AndroidObject::staticString(env, "android/provider/MediaStore$MediaColumns", "SIZE"));
        map["MediaStore$MediaColumns.MIME_TYPE"] = ContentResolver(env).query(_uri, AndroidObject::staticString(env, "android/provider/MediaStore$MediaColumns", "MIME_TYPE"));
        map["MediaStore$MediaColumns.DISPLAY_NAME"] = ContentResolver(env).query(_uri, AndroidObject::staticString(env, "android/provider/MediaStore$MediaColumns", "DISPLAY_NAME"));
        map["DocumentsContract$Document.COLUMN_DOCUMENT_ID"] = ContentResolver(env).query(_uri, DocumentsContractDocument::COLUMN_DOCUMENT_ID(env));
    }

    if (!treeDocumentId.isEmpty() && !treeDocumentId.isNull())
    {
        QString childDocumentsUri = DocumentsContract::buildChildDocumentsUriUsingTree(env, _uri, treeDocumentId);
        map["ChildDocumentsUri"] = childDocumentsUri;

        //QStringList childDocumentIds = ContentResolver(env).query(childDocumentsUri,  "android/provider/DocumentsContract$Document", "COLUMN_DOCUMENT_ID");
        QStringList childDocumentIds = ContentResolver(env).query(childDocumentsUri,  DocumentsContractDocument::COLUMN_DOCUMENT_ID(env));
        if (childDocumentIds.length() > 0)
        {
            QVariantList childDocumentList;
            foreach (QString childDocumentId, childDocumentIds)
            {
                QVariantMap childDocument;
                QString childDocumentUri = DocumentsContract::buildDocumentUriUsingTree(env, _uri, childDocumentId);
                QString authority = QUrl(_uri).host();
                childDocument["authority"] = authority;
                childDocument["documentId"] = childDocumentId;
                childDocument["documentUri"] = childDocumentUri;
                childDocument["documentId2"] = DocumentsContract::getDocumentId(env, childDocumentId);
                childDocument["treeDocumentId"] = DocumentsContract::getDocumentId(env, childDocumentId);
                childDocument["displayName"] = ContentResolver(env).query(childDocumentUri, AndroidObject::staticString(env, "android/provider/MediaStore$MediaColumns", "DISPLAY_NAME"));
                childDocument["size"] = ContentResolver(env).query(childDocumentUri, AndroidObject::staticString(env, "android/provider/MediaStore$MediaColumns", "SIZE"));
                childDocument["mimeType"] = ContentResolver(env).query(childDocumentUri, AndroidObject::staticString(env, "android/provider/MediaStore$MediaColumns", "MIME_TYPE"));
                //childDocument["DocumentsContract$Document.COLUMN_DOCUMENT_ID"] = ContentResolver(env).query(childDocumentUri, "android/provider/DocumentsContract$Document", "COLUMN_DOCUMENT_ID");
                childDocument["DocumentsContract$Document.COLUMN_DOCUMENT_ID"] = ContentResolver(env).query(childDocumentUri, DocumentsContractDocument::COLUMN_DOCUMENT_ID(env));
                childDocument["buildDocumentUri"] = DocumentsContract::buildDocumentUri(env, authority, childDocumentId);
                childDocument["buildDocumentUriUsingTree"] = DocumentsContract::buildDocumentUriUsingTree(env, _uri, childDocumentId);
                childDocumentList.append(childDocument);
            }
            map["childDocuments"] = childDocumentList;
        }
    }

    map["Version"] = 20200601;
    return map;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
