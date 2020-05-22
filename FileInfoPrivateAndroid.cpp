
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
    QStringList displayName = ContentResolver(env).query(url().toString(), "android/provider/MediaStore$MediaColumns", "DISPLAY_NAME");
    if (displayName.isEmpty() || displayName.length() == 0) return QString();
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
    QAndroidJniEnvironment env;
    if (!isContentUri()) return FileInfoPrivate::folder();
    QString _url = url().toString();
    DocumentsContract documentsContract(env);

    //QString authority = ContentUris::parseAuthority(_url);
    //QString treeDocumentUri = documentsContract.buildTreeDocumentUri(authority, _url);
    //if (treeDocumentUri.isEmpty() || treeDocumentUri.isNull())
    //{
        //return nullptr;
    //}

    /*
    QRegExp rx("^(content):\\/\\/([^\\/]*)\\/((?:.*\\/)?)(document)\\/(.*)\\%2F(.*?)$");
    qDebug() << Q_FUNC_INFO << __LINE__ << "rx: " << rx.pattern();
    if (rx.indexIn(_url) != 0)
    {
        qDebug() << Q_FUNC_INFO << __LINE__ << "url: " << _url;
        return nullptr;
    }

    qDebug() << Q_FUNC_INFO << __LINE__;
    QString scheme = rx.cap(1);
    QString authority = rx.cap(2);
    QString parentFolder = rx.cap(3);
    QString documentTag = rx.cap(4);
    QString subFolder = rx.cap(5);
    QString fileName = rx.cap(6);
    QString treeDocumentUri = scheme + "://" + authority + "/" + parentFolder + "tree/" + subFolder;
    FileFolder* fileFolder = new FileFolder();
    fileFolder->setPath(treeDocumentUri);
    QQmlEngine::setObjectOwnership(fileFolder, QQmlEngine::JavaScriptOwnership);
    return fileFolder;
    */

    QRegExp rx("^(content:\\/\\/.*)/document/(.*)%2F.*%");
    qDebug() << Q_FUNC_INFO << __LINE__ << "rx: " << rx.pattern();
    if (rx.indexIn(_url) != 0)
    {
        qDebug() << Q_FUNC_INFO << __LINE__ << "url: " << _url;
        return nullptr;
    }

    qDebug() << Q_FUNC_INFO << __LINE__ << "rx.cap[1]: " << rx.cap(1);
    qDebug() << Q_FUNC_INFO << __LINE__ << "rx.cap[2]: " << rx.cap(2);
    QString treeDocumentUri = rx.cap(1) + "/tree/" + rx.cap(2);
    qDebug() << Q_FUNC_INFO << __LINE__ << "treeDocumentUri: " << treeDocumentUri;
    FileFolder* fileFolder = new FileFolder();
    fileFolder->setPath(treeDocumentUri);
    QQmlEngine::setObjectOwnership(fileFolder, QQmlEngine::JavaScriptOwnership);
    return fileFolder;
}

bool FileInfoPrivateAndroid::isFile() const
{
    QAndroidJniEnvironment env;
    DocumentsContract documentsContract(env);
    if (!isContentUri()) return FileInfoPrivate::isFile();
    QString _url = url().toString();
    QString documentId = documentsContract.getDocumentId(_url);
    return !documentId.isNull() && !documentId.isEmpty();
}

bool FileInfoPrivateAndroid::isDir() const
{
    QAndroidJniEnvironment env;
    DocumentsContract documentsContract(env);
    if (!isContentUri()) return FileInfoPrivate::isDir();
    QString _url = url().toString();
    QString treeDocumentId = documentsContract.getTreeDocumentId(_url);
    return !treeDocumentId.isNull() && !treeDocumentId.isEmpty();
}

qint64 FileInfoPrivateAndroid::size() const
{
    QAndroidJniEnvironment env;
    if (!isContentUri()) return FileInfoPrivate::size();
    QStringList size = ContentResolver(env).query(url().toString(), "android/provider/MediaStore$MediaColumns", "SIZE");
    if (size.isEmpty() || size.length() == 0) return -1;
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

    QString authority = ContentUris::parseAuthority(_uri);
    map["Authority"] = authority;

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
