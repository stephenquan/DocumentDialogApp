//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "FileInfo.h"
#ifndef Q_OS_ANDROID
#include "FileInfoPrivate.h"
#endif
#ifdef Q_OS_ANDROID
#include "FileInfoPrivateAndroid.h"
#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

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

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

FileInfo::~FileInfo()
{
    disconnect(m_FileInfoPrivate, &FileInfoPrivate::fileInfoChanged, this, &FileInfo::fileInfoChanged);
    delete m_FileInfoPrivate;
    m_FileInfoPrivate = nullptr;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfo::absoluteFilePath() const
{
    return m_FileInfoPrivate->absoluteFilePath();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfo::absolutePath() const
{
    return m_FileInfoPrivate->absolutePath();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfo::baseName() const
{
    return m_FileInfoPrivate->baseName();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

FileFolder* FileInfo::folder() const
{
    return m_FileInfoPrivate->folder();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfo::displayName() const
{
    return m_FileInfoPrivate->displayName();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool FileInfo::exists() const
{
    return m_FileInfoPrivate->exists();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfo::fileName() const
{
    return m_FileInfoPrivate->fileName();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileInfo::filePath() const
{
    return m_FileInfoPrivate->filePath();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool FileInfo::isFile() const
{
    return m_FileInfoPrivate->isFile();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool FileInfo::isDir() const
{
    return m_FileInfoPrivate->isDir();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

qint64 FileInfo::size() const
{
    return m_FileInfoPrivate->size();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QVariant FileInfo::url() const
{
    return m_FileInfoPrivate->url();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QByteArray FileInfo::readAll() const
{
    return m_FileInfoPrivate->readAll();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void FileInfo::setUrl(const QVariant& url)
{
    m_FileInfoPrivate->setUrl(url);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QVariant FileInfo::dataUri() const
{
    QByteArray bytes = readAll();
    if (bytes.isEmpty() || bytes.isNull())
    {
        return QVariant();
    }

    return QStringLiteral("data:application/octet-stream;base64,") + bytes.toBase64();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QVariant FileInfo::extra() const
{
    return m_FileInfoPrivate->extra();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
