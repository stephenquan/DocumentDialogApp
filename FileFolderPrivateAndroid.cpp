//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QAndroidJniEnvironment>
#include "FileFolderPrivateAndroid.h"
#include "ContentUris.h"
#include "ContentResolver.h"
#include "DocumentFile.h"
#include "DocumentsContract.h"
#include "DocumentsContractDocument.h"
#include "JniExceptionCheck.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

FileFolderPrivateAndroid::FileFolderPrivateAndroid(QObject* parent) :
    FileFolderPrivate(parent),
    m_DocumentFile(nullptr)
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

    QStringList entryList;
    names(env, entryList, url().toString(), nameFilter, subFolders, true);
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

    QStringList entryList;
    names(env, entryList, url().toString(), nameFilter, subFolders, false);
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

void FileFolderPrivateAndroid::names(QAndroidJniEnvironment& env, QStringList& entryList, const QString& uri, const QVariant& nameFilter, const bool recurse, bool files) const
{
    Q_UNUSED(recurse)
    Q_UNUSED(nameFilter)

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

QVariant FileFolderPrivateAndroid::url() const
{
    return path();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void FileFolderPrivateAndroid::setUrl(const QVariant& url)
{
    QAndroidJniEnvironment env;

    JniExceptionCheck check(env);

    setPath(url.toString());
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
