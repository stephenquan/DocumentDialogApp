#include "FileInfoPrivateAndroid.h"
#include <QtAndroid>
#include "ContentResolver.h"
#include "DocumentsContract.h"
#include "JniExceptionCheck.h"
#include <QDebug>

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
    QVariant size = ContentResolver(env).query(url().toString(), "SIZE");
    return size.isValid() && !size.isNull();
}

QString FileInfoPrivateAndroid::displayName() const
{
    QAndroidJniEnvironment env;
    if (!isContentUri()) return FileInfoPrivate::displayName();
    QVariant displayName = ContentResolver(env).query(url().toString(), "DISPLAY_NAME");
    return displayName.toString();
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
    QVariant size = ContentResolver(env).query(url().toString(), "SIZE");
    if (!size.isValid() || size.isNull()) return -1;
    return size.toLongLong();
}

QByteArray FileInfoPrivateAndroid::readAll() const
{
    QAndroidJniEnvironment env;
    if (!isContentUri()) return FileInfoPrivate::readAll();

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

    qDebug() << Q_FUNC_INFO << __LINE__ << "url: " << url;

    QAndroidJniEnvironment env;
    JniExceptionCheck check(env);

    if (!ContentResolver::isContentUri(_url)) return FileInfoPrivate::setUrl(_url);

    /*
    DocumentsContract documentsContract(env);
    QString documentId = documentsContract.getDocumentId(_url);
    qDebug() << Q_FUNC_INFO << __LINE__ << "documentId: " << documentId;
    if (!documentId.isEmpty() && !documentId.isNull())
    {
        qDebug() << Q_FUNC_INFO << __LINE__;
        if (documentId.startsWith("raw:"))
        {
            qDebug() << Q_FUNC_INFO << __LINE__;
            FileInfoPrivate::setUrl(documentId.remove(0, 4));
            return;
        }

        qDebug() << Q_FUNC_INFO << __LINE__;
        QRegExp re("^\\d*$");
        if (re.exactMatch(_url))
        {
            qDebug() << Q_FUNC_INFO << __LINE__;
            _url = QString("content://downloads/public_documents/") + documentId;
        }
    }
    */

    ContentResolver contentResolver(env);
    QVariant data = contentResolver.query(_url, QStringLiteral("DATA"));
    qDebug() << Q_FUNC_INFO << __LINE__ << "data: " << data;
    if (data.isValid() && !data.isNull() && !data.toString().isEmpty())
    {
        _url = data.toString();
    }

    FileInfoPrivate::setUrl(_url);
}

QVariant FileInfoPrivateAndroid::extra() const
{
    qDebug() << Q_FUNC_INFO << __LINE__;
    //return QVariant(); // QString("123");
#ifndef ABC
    QAndroidJniEnvironment env;
    qDebug() << Q_FUNC_INFO << __LINE__;
    //JniExceptionCheck check(env);
    qDebug() << Q_FUNC_INFO << __LINE__;
    if (!isContentUri()) return FileInfoPrivate::extra();
    qDebug() << Q_FUNC_INFO << __LINE__;
    QVariantMap map;
    qDebug() << Q_FUNC_INFO << __LINE__;
    ContentResolver contentResolver(env);
    qDebug() << Q_FUNC_INFO << __LINE__;
    DocumentsContract documentsContract(env);
    qDebug() << Q_FUNC_INFO << __LINE__;
    map["ContentResolver.SIZE"] = contentResolver.query(url().toString(), "SIZE");
    qDebug() << Q_FUNC_INFO << __LINE__;
    map["ContentResolver.MIME_TYPE"] = contentResolver.query(url().toString(), "MIME_TYPE");
    qDebug() << Q_FUNC_INFO << __LINE__;
    map["ContentResolver.DISPLAY_NAME"] = contentResolver.query(url().toString(), "DISPLAY_NAME");
    qDebug() << Q_FUNC_INFO << __LINE__;
    map["DocumentsContract.documentId"] = documentsContract.getDocumentId(url().toString());
    qDebug() << Q_FUNC_INFO << __LINE__ << "map: " << map;
    return map;
#endif
}
