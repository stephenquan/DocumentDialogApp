
#include <QQmlEngine>
#include <QRegExp>
#include <QDebug>

#include "FileFolderPrivate.h"
#include "FileFolder.h"
#include "FileInfoPrivateAndroid.h"
#include "ContentUris.h"
#include "ContentResolver.h"
#include "DocumentsContract.h"
#include "JniExceptionCheck.h"

FileInfoPrivateAndroid::FileInfoPrivateAndroid(QObject* parent) :
    FileInfoPrivate(parent)
{
}

QString FileInfoPrivateAndroid::absoluteFilePath() const
{
    if (!isContentUri()) return FileInfoPrivate::absoluteFilePath();
    return m_Url.toString();
}

QString FileInfoPrivateAndroid::absolutePath() const
{
    if (!isContentUri()) return FileInfoPrivate::absolutePath();
    return m_Url.toString();
}

QString FileInfoPrivateAndroid::baseName() const
{
    if (!isContentUri()) return FileInfoPrivate::baseName();
    return QFileInfo(fileName()).baseName();
}

bool FileInfoPrivateAndroid::exists() const
{
    QAndroidJniEnvironment env;
    if (!isContentUri()) return FileInfoPrivate::exists();
    return isFile() || isDir();
}

QString FileInfoPrivateAndroid::displayName() const
{
    QAndroidJniEnvironment env;
    if (!isContentUri()) return FileInfoPrivate::displayName();

    QString _uri = url().toString();

    QStringList displayName = ContentResolver(env).query(_uri, "android/provider/MediaStore$MediaColumns", "DISPLAY_NAME");
    if (displayName.isEmpty() || displayName.length() == 0)
    {
        return QString();
    }

    return displayName[0];
}

QString FileInfoPrivateAndroid::fileName() const
{
    if (!isContentUri()) return FileInfoPrivate::fileName();
    return m_Url.toString();
}

QString FileInfoPrivateAndroid::filePath() const
{
    if (!isContentUri()) return FileInfoPrivate::filePath();
    return m_Url.toString();
}

FileFolder* FileInfoPrivateAndroid::folder() const
{
    if (!isContentUri()) return FileInfoPrivate::folder();
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

bool FileInfoPrivateAndroid::isFile() const
{
    QAndroidJniEnvironment env;
    if (!isContentUri())
    {
        return FileInfoPrivate::isDir();
    }

    QString _url = url().toString();

    ContentResolver contentResolver(env);
    QStringList mimeTypes = contentResolver.query(_url, "android/provider/MediaStore$MediaColumns", "MIME_TYPE");
    QString mimeType = mimeTypes.length() > 0 ? mimeTypes[0] : "";
    bool isFolder = (mimeType == "vnd.android.document/directory" || mimeType == "");
    bool isFile = !isFolder;
    return isFile;
}



bool FileInfoPrivateAndroid::isDir() const
{
    QAndroidJniEnvironment env;
    if (!isContentUri())
    {
        return FileInfoPrivate::isDir();
    }

    QString _url = url().toString();

    ContentResolver contentResolver(env);
    QStringList mimeTypes = contentResolver.query(_url, "android/provider/MediaStore$MediaColumns", "MIME_TYPE");
    QString mimeType = mimeTypes.length() > 0 ? mimeTypes[0] : "";
    bool isFolder = (mimeType == "vnd.android.document/directory" || mimeType == "");
    return isFolder;
}

qint64 FileInfoPrivateAndroid::size() const
{
    QAndroidJniEnvironment env;
    if (!isContentUri()) return FileInfoPrivate::size();

    QString _uri = url().toString();

    QStringList size = ContentResolver(env).query(url().toString(), "android/provider/MediaStore$MediaColumns", "SIZE");
    if (size.isEmpty() || size.length() == 0)
    {
        return -1;
    }

    return size[0].toLongLong();
}

QByteArray FileInfoPrivateAndroid::readAll() const
{
    QAndroidJniEnvironment env;
    JniExceptionCheck check(env);

    if (!isContentUri()) return FileInfoPrivate::readAll();

    DocumentsContract documentsContract(env);
    QString documentId = documentsContract.getDocumentId(url().toString());
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

bool FileInfoPrivateAndroid::isContentUri() const
{
    return ContentUris::isContentUri(url().toString());
}

void FileInfoPrivateAndroid::setUrl(const QVariant& url)
{
    QString _url = url.toString();

    QAndroidJniEnvironment env;
    JniExceptionCheck check(env);

    if (!ContentUris::isContentUri(_url)) return FileInfoPrivate::setUrl(_url);


    /*
    DocumentsContract documentsContract(env);
    QString documentId = documentsContract.getDocumentId(_url);
    if (!documentId.isEmpty() && !documentId.isNull())
    {
        if (documentId.startsWith("raw:"))
        {
            FileInfoPrivate::setUrl(documentId.remove(0, 4));
            return;
        }

        QRegExp re("^\\d*$");
        if (re.exactMatch(_url))
        {
            _url = QString("content://downloads/public_documents/") + documentId;
        }
    }
    */

    ContentResolver contentResolver(env);
    QVariant data = contentResolver.query(_url, "android/provider/MediaStore$MediaColumns", "DATA");
    if (data.isValid() && !data.isNull() && !data.toString().isEmpty())
    {
        _url = data.toString();
    }

    FileInfoPrivate::setUrl(_url);
}

QVariant FileInfoPrivateAndroid::extra() const
{
    QAndroidJniEnvironment env;
    if (!isContentUri()) return FileInfoPrivate::extra();

    ContentResolver contentResolver(env);
    DocumentsContract documentsContract(env);
    QString _uri = url().toString();

    QVariantMap map;

    QString documentId = documentsContract.getDocumentId(_uri);
    map["DocumentId"] = documentId;

    QString treeDocumentId = documentsContract.getTreeDocumentId(_uri);
    map["TreeDocumentId"] = treeDocumentId;

    if (!documentId.isEmpty() && !documentId.isNull())
    {
        map["MediaStore$MediaColumns.SIZE"] = contentResolver.query(_uri, "android/provider/MediaStore$MediaColumns", "SIZE");
        map["MediaStore$MediaColumns.MIME_TYPE"] = contentResolver.query(_uri, "android/provider/MediaStore$MediaColumns", "MIME_TYPE");
        map["MediaStore$MediaColumns.DISPLAY_NAME"] = contentResolver.query(_uri, "android/provider/MediaStore$MediaColumns", "DISPLAY_NAME");
        map["DocumentsContract$Document.COLUMN_DOCUMENT_ID"] = contentResolver.query(_uri, "android/provider/DocumentsContract$Document", "COLUMN_DOCUMENT_ID");
    }

    if (!treeDocumentId.isEmpty() && !treeDocumentId.isNull())
    {
        QString childDocumentsUri = documentsContract.buildChildDocumentsUriUsingTree(_uri, treeDocumentId);
        map["ChildDocumentsUri"] = childDocumentsUri;

        QStringList childDocumentIds = contentResolver.query(childDocumentsUri,  "android/provider/DocumentsContract$Document", "COLUMN_DOCUMENT_ID");
        if (childDocumentIds.length() > 0)
        {
            QVariantList childDocumentList;
            foreach (QString childDocumentId, childDocumentIds)
            {
                QVariantMap childDocument;
                QString childDocumentUri = documentsContract.buildDocumentUriUsingTree(_uri, childDocumentId);
                childDocument["documentId"] = childDocumentId;
                childDocument["documentUri"] = childDocumentUri;
                childDocument["documentId2"] = documentsContract.getDocumentId(childDocumentId);
                childDocument["treeDocumentId"] = documentsContract.getDocumentId(childDocumentId);
                childDocument["displayName"] = contentResolver.query(childDocumentUri, "android/provider/MediaStore$MediaColumns", "DISPLAY_NAME");
                childDocument["size"] = contentResolver.query(childDocumentUri, "android/provider/MediaStore$MediaColumns", "SIZE");
                childDocument["mimeType"] = contentResolver.query(childDocumentUri, "android/provider/MediaStore$MediaColumns", "MIME_TYPE");
                childDocument["DocumentsContract$Document.COLUMN_DOCUMENT_ID"] = contentResolver.query(childDocumentUri, "android/provider/DocumentsContract$Document", "COLUMN_DOCUMENT_ID");
                childDocumentList.append(childDocument);
            }
            map["childDocuments"] = childDocumentList;
        }
    }

    map["Version"] = 20200520;
    return map;
}
