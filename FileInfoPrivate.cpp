#include "FileInfoPrivate.h"
#include <QUrl>
#include <QFileInfo>

FileInfoPrivate::FileInfoPrivate(QObject* parent) :
    QObject(parent)
{
}

QString FileInfoPrivate::absoluteFilePath() const
{
    return fileInfo().absoluteFilePath();
}

QString FileInfoPrivate::absolutePath() const
{
    return fileInfo().absolutePath();
}

QString FileInfoPrivate::baseName() const
{
    return fileInfo().baseName();
}

QString FileInfoPrivate::displayName() const
{
    return fileInfo().fileName();
}

bool FileInfoPrivate::exists() const
{
    return fileInfo().exists();
}

QString FileInfoPrivate::fileName() const
{
    return fileInfo().fileName();
}

QString FileInfoPrivate::filePath() const
{
    return fileInfo().filePath();
}

QByteArray FileInfoPrivate::readAll() const
{
    QFile file(filePath());
    if (!file.open(QFile::ReadOnly))
    {
        return QByteArray();
    }
    return file.readAll();
}

qint64 FileInfoPrivate::size() const
{
    return fileInfo().size();
}

void FileInfoPrivate::setUrl(const QVariant& url)
{
    if (m_Url.toString().compare(url.toString()) == 0)
    {
        return;
    }

    m_Url = url;

    emit fileInfoChanged();
}

QFileInfo FileInfoPrivate::fileInfo() const
{
    QUrl fileUrl = m_Url.toUrl();
    if (!fileUrl.isValid())
    {
        return QFileInfo();
    }

    return QFileInfo(fileUrl.toLocalFile());
}

QFileInfo FileInfoPrivate::fileInfo(const QVariant& fileSource)
{
    if (fileSource.type() == QVariant::Url)
    {
        return fileInfo(fileSource.toUrl());
    }

    if (fileSource.type() == QVariant::String)
    {
        return fileInfo(fileSource.toString());
    }

    return QFileInfo();
}

QFileInfo FileInfoPrivate::fileInfo(const QUrl& fileUrl)
{
    if (!fileUrl.isValid())
    {
        return QFileInfo();
    }

    return fileInfo(fileUrl.toLocalFile());
}

QFileInfo FileInfoPrivate::fileInfo(const QString& filePath)
{
    return QFileInfo(filePath);
}

QVariant FileInfoPrivate::extra() const
{
    return QVariant();
}
