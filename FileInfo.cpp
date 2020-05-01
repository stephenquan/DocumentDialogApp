#include "FileInfo.h"
#ifndef Q_OS_ANDROID
#include "FileInfoPrivate.h"
#endif
#ifdef Q_OS_ANDROID
#include "FileInfoPrivateAndroid.h"
#endif
#include <QDebug>

FileInfo::FileInfo(QObject* parent) :
    QObject(parent)
#ifndef Q_OS_ANDROID
    , m_FileInfoPrivate(new FileInfoPrivate(this))
#endif
#ifdef Q_OS_ANDROID
    , m_FileInfoPrivate(new FileInfoPrivateAndroid(this))
#endif
{
    connect(m_FileInfoPrivate, &FileInfoPrivate::fileInfoChanged, this, &FileInfo::fileInfoChanged);
}

FileInfo::~FileInfo()
{
    disconnect(m_FileInfoPrivate, &FileInfoPrivate::fileInfoChanged, this, &FileInfo::fileInfoChanged);
    delete m_FileInfoPrivate;
    m_FileInfoPrivate = nullptr;
}

QString FileInfo::absoluteFilePath() const
{
    return m_FileInfoPrivate->absoluteFilePath();
}

QString FileInfo::absolutePath() const
{
    return m_FileInfoPrivate->absolutePath();
}

QString FileInfo::baseName() const
{
    return m_FileInfoPrivate->baseName();
}

bool FileInfo::exists() const
{
    return m_FileInfoPrivate->exists();
}

QString FileInfo::fileName() const
{
    return m_FileInfoPrivate->fileName();
}

QString FileInfo::filePath() const
{
    return m_FileInfoPrivate->filePath();
}

qint64 FileInfo::size() const
{
    return m_FileInfoPrivate->size();
}

QVariant FileInfo::url() const
{
    return m_FileInfoPrivate->url();
}

QByteArray FileInfo::readAll() const
{
    return m_FileInfoPrivate->readAll();
}

void FileInfo::setUrl(const QVariant& url)
{
    qDebug() << Q_FUNC_INFO << __LINE__ << "url: " << url;
    m_FileInfoPrivate->setUrl(url);
    qDebug() << Q_FUNC_INFO << __LINE__ << "url: " << FileInfo::url();
}

QVariant FileInfo::dataUri() const
{
    QByteArray bytes = readAll();
    if (bytes.isEmpty() || bytes.isNull())
    {
        return QVariant();
    }
    qDebug() << Q_FUNC_INFO << "bytes.length: " << bytes.length();

    return QStringLiteral("data:application/octet-stream;base64,") + bytes.toBase64();
}
