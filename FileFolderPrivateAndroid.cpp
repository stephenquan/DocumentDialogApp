//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QAndroidJniEnvironment>
#include "FileFolderPrivateAndroid.h"
#include "ContentUris.h"
#include "ContentResolver.h"
#include "DocumentsContract.h"
#include "DocumentsContractDocument.h"
#include "JniExceptionCheck.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

FileFolderPrivateAndroid::FileFolderPrivateAndroid(QObject* parent) :
    FileFolderPrivate(parent)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList FileFolderPrivateAndroid::fileNames(const QVariant& nameFilter, bool subFolders) const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(m_Path))
    {
        return FileFolderPrivate::fileNames();
    }

    if (!DocumentsContract(env).isTreeUri(m_Path))
    {
        return QStringList();
    }

    QStringList entryList;
    names(entryList, m_Path, subFolders, true, nameFilter, subFolders, env);
    return entryList;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList FileFolderPrivateAndroid::folderNames(const QVariant& nameFilter, bool subFolders) const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(m_Path))
    {
        return FileFolderPrivate::fileNames();
    }

    if (!DocumentsContract(env).isTreeUri(m_Path))
    {
        return QStringList();
    }

    QStringList entryList;
    names(entryList, m_Path, subFolders, false, nameFilter, subFolders, env);
    return entryList;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileFolderPrivateAndroid::filePath(const QString& fileName) const
{
    if (!ContentUris::isContentUri(m_Path))
    {
        return FileFolderPrivate::filePath(fileName);
    }

    return fileName;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QVariant FileFolderPrivateAndroid::fileUrl(const QString& fileName) const
{
    if (!ContentUris::isContentUri(m_Path))
    {
        return FileFolderPrivate::filePath(fileName);
    }

    return fileName;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void FileFolderPrivateAndroid::names(QStringList& entryList, const QString& uri, const bool recurse, bool files, const QVariant& nameFilter, bool subFolders, QAndroidJniEnvironment& env) const
{
    Q_UNUSED(recurse)
    Q_UNUSED(nameFilter)
    Q_UNUSED(subFolders)

    QStringList childDocumentUris = DocumentsContract(env).childDocumentUris(uri);

    foreach (QString childDocumentUri, childDocumentUris)
    {
        bool isFile = DocumentsContract(env).isFile(childDocumentUri);
        if (isFile)
        {
            if (files)
            {
                entryList.append(childDocumentUri);
            }
        }

        bool isFolder = DocumentsContract(env).isFolder(childDocumentUri);
        if (isFolder)
        {
            if (!files)
            {
                entryList.append(childDocumentUri);
            }
        }
    }
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QVariant FileFolderPrivateAndroid::url() const
{
    return path();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void FileFolderPrivateAndroid::setUrl(const QVariant& url)
{
    setPath(url.toString());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
