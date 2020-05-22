#include "FileFolder.h"
#ifndef Q_OS_ANDROID
#include "FileFolderPrivate.h"
#endif
#ifdef Q_OS_ANDROID
#include "FileFolderPrivateAndroid.h"
#endif

FileFolder::FileFolder(QObject* parent) :
    QObject(parent)
#ifndef Q_OS_ANDROID
    , m_FileFolderPrivate(new FileFolderPrivate(this))
#endif
#ifdef Q_OS_ANDROID
    , m_FileFolderPrivate(new FileFolderPrivateAndroid(this))
#endif
{
    connect(m_FileFolderPrivate, &FileFolderPrivate::fileFolderChanged, this, &FileFolder::fileFolderChanged);
}

FileFolder::~FileFolder()
{
    disconnect(m_FileFolderPrivate, &FileFolderPrivate::fileFolderChanged, this, &FileFolder::fileFolderChanged);
    delete m_FileFolderPrivate;
    m_FileFolderPrivate = nullptr;
}

QString FileFolder::path() const
{
    return m_FileFolderPrivate->path();
}

void FileFolder::setPath(const QString& path)
{
    m_FileFolderPrivate->setPath(path);
}

QStringList FileFolder::fileNames() const
{
    return m_FileFolderPrivate->fileNames();
}
