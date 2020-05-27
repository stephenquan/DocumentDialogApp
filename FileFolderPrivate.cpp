#include "FileFolderPrivate.h"
#include <QUrl>
#include <QFileInfo>

FileFolderPrivate::FileFolderPrivate(QObject* parent) :
    QObject(parent)
{
}

QString FileFolderPrivate::path() const
{
    return m_Path;
}

void FileFolderPrivate::setPath(const QString& path)
{
    if (m_Path == path)
    {
        return;
    }

    m_Path = path;

    emit fileFolderChanged();
}

QStringList FileFolderPrivate::fileNames(const QVariant& nameFilter, bool subFolders) const
{
    QStringList files;

    names(files, dir(), nameFilters(nameFilter), QString(), subFolders, true);

    return files;
}

QStringList FileFolderPrivate::folderNames(const QVariant& nameFilter, bool subFolders) const
{
    QStringList folders;

    names(folders, dir(), nameFilters(nameFilter), QString(), subFolders, false);

    return folders;
}

QDir FileFolderPrivate::dir() const
{
    return QDir(m_Path);
}

QString FileFolderPrivate::filePath(const QString& fileName) const
{
    return dir().filePath(fileName);
}

QVariant FileFolderPrivate::fileUrl(const QString& fileName) const
{
    return QUrl::fromLocalFile(filePath(fileName)).toString();
}

//------------------------------------------------------------------------------

void FileFolderPrivate::names(QStringList& entryList, const QDir& dir, const QStringList& nameFilters, const QString &basePath, bool recurse, bool files) const
{
    QDir::Filters filters = QDir::NoDotAndDotDot | QDir::Dirs;
    if (files)
    {
        filters |= QDir::Files;
    }

    auto entries = dir.entryList(nameFilters, filters, QDir::Name);

    foreach (const auto& entry, entries)
    {
        auto filePath = dir.filePath(entry);
        QFileInfo fileInfo(filePath);

        QString entryPath;
        if (basePath.isEmpty())
        {
            entryPath = entry;
        }
        else
        {
            entryPath = basePath + QDir::separator() + entry;
        }

        if (fileInfo.isDir())
        {
            if (!files)
            {
                entryList << entryPath;
            }

            if (recurse)
            {
                names(entryList, QDir(filePath), nameFilters, entryPath, recurse, files);
            }
        }
        else if (files)
        {
            entryList << entryPath;
        }
    }
}

//------------------------------------------------------------------------------

QStringList FileFolderPrivate::nameFilters(const QVariant& nameFilter) const
{
    if (nameFilter.canConvert<QStringList>())
    {
        return nameFilter.toStringList();
    }

    return QStringList(nameFilter.toString());
}

//------------------------------------------------------------------------------

QVariant FileFolderPrivate::url() const
{
    return QUrl(path()).toString();
}

//------------------------------------------------------------------------------

void FileFolderPrivate::setUrl(const QVariant& url)
{
    setPath(QUrl(url.toString()).toLocalFile());
}

//------------------------------------------------------------------------------
