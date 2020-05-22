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

QStringList FileFolderPrivate::fileNames() const
{
    return dir().entryList();
}

QDir FileFolderPrivate::dir() const
{
    return QDir(m_Path);
}
