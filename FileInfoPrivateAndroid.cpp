#include "FileInfoPrivateAndroid.h"
#include <QtAndroid>
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
    QStringList size = ContentResolver(env).query(url().toString(), "android/provider/MediaStore$MediaColumns", "SIZE");
    if (size.isEmpty() || size.length() == 0) return false;
    return true;
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
    return ContentResolver::isContentUri(url().toString());
}

void FileInfoPrivateAndroid::setUrl(const QVariant& url)
{
    QString _url = url.toString();

    QAndroidJniEnvironment env;
    JniExceptionCheck check(env);

    if (!ContentResolver::isContentUri(_url)) return FileInfoPrivate::setUrl(_url);

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
    map["MediaStore$MediaColumns.SIZE"] = contentResolver.query(_uri, "android/provider/MediaStore$MediaColumns", "SIZE");
    map["MediaStore$MediaColumns.MIME_TYPE"] = contentResolver.query(_uri, "android/provider/MediaStore$MediaColumns", "MIME_TYPE");
    map["MediaStore$MediaColumns.DISPLAY_NAME"] = contentResolver.query(_uri, "android/provider/MediaStore$MediaColumns", "DISPLAY_NAME");
    map["DocumentsContract$Document.COLUMN_DOCUMENT_ID"] = contentResolver.query(_uri, "android/provider/DocumentsContract$Document", "COLUMN_DOCUMENT_ID");

    QString documentId = documentsContract.getTreeDocumentId(_uri);
    QString treeDocumentId = documentsContract.getTreeDocumentId(_uri);
    map["documentId"] = documentId;
    map["treeDocumentId"] = treeDocumentId;
    if (!treeDocumentId.isEmpty() && !treeDocumentId.isNull())
    {
        QString childDocumentsUri = documentsContract.buildChildDocumentsUriUsingTree(_uri, treeDocumentId);
        map["childDocumentsUri"] = childDocumentsUri;

        if (!childDocumentsUri.isEmpty() && !childDocumentsUri.isNull())
        {
            map["childDocuments"] = contentResolver.query(childDocumentsUri,  "android/provider/DocumentsContract$Document", "COLUMN_DOCUMENT_ID");
        }
    }

    map["Version"] = 1004;
    return map;
}
