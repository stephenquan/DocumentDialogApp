//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QAndroidJniEnvironment>
#include "FileFolderPrivateAndroid2.h"
#include "ContentUris.h"
#include "ContentResolver.h"
#include "DocumentFile.h"
#include "DocumentsContract.h"
#include "DocumentsContractDocument.h"
#include "JniExceptionCheck.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

FileFolderPrivateAndroid2::FileFolderPrivateAndroid2(QObject* parent) :
    FileFolderPrivate(parent),
    m_DocumentFile(nullptr)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList FileFolderPrivateAndroid2::fileNames(const QVariant& nameFilter, bool subFolders) const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(m_Path))
    {
        return FileFolderPrivate::fileNames();
    }

    QStringList entryList;
    names(entryList, url().toString(), subFolders, true, nameFilter, subFolders, env);
    return entryList;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList FileFolderPrivateAndroid2::folderNames(const QVariant& nameFilter, bool subFolders) const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(m_Path))
    {
        return FileFolderPrivate::fileNames();
    }

    QStringList entryList;
    names(entryList, url().toString(), subFolders, false, nameFilter, subFolders, env);
    return entryList;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString FileFolderPrivateAndroid2::filePath(const QString& fileName) const
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

QVariant FileFolderPrivateAndroid2::fileUrl(const QString& fileName) const
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

void FileFolderPrivateAndroid2::names(QStringList& entryList, const QString& uri, const bool recurse, bool files, const QVariant& nameFilter, bool subFolders, QAndroidJniEnvironment& env) const
{
    Q_UNUSED(recurse)
    Q_UNUSED(nameFilter)
    Q_UNUSED(subFolders)

    DocumentFile documentFile = DocumentFile::fromUri(env, uri);
    if (!documentFile.isValid())
    {
        return;
    }

    QStringList fileUris = documentFile.listFiles();

    foreach (QString fileUri, fileUris)
    {
        bool isFile = DocumentsContract::isFile(env, fileUri);
        if (isFile)
        {
            if (files)
            {
                entryList.append(fileUri);
            }
        }

        bool isFolder = DocumentsContract::isDirectory(env, fileUri);
        if (isFolder)
        {
            if (!files)
            {
                entryList.append(fileUri);
            }
        }
    }
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QVariant FileFolderPrivateAndroid2::url() const
{
    return path();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void FileFolderPrivateAndroid2::setUrl(const QVariant& url)
{
    QAndroidJniEnvironment env;

    JniExceptionCheck check(env);

    setPath(url.toString());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
