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
    QAndroidJniEnvironment env;
    JniExceptionCheck check(env);

    if (!ContentUris::isContentUri(m_Path))
    {
        return FileFolderPrivate::filePath(fileName);
    }

    DocumentFile parentDocumentFile = DocumentFile::fromUri(env, url().toString());
    if (!parentDocumentFile.isValid())
    {
        return QString();
    }

    DocumentFile documentFile = parentDocumentFile.findFile(fileName);
    if (!documentFile.isValid())
    {
        return QString();
    }

    return documentFile.getUri();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QVariant FileFolderPrivateAndroid::fileUrl(const QString& fileName) const
{
    QAndroidJniEnvironment env;
    JniExceptionCheck check(env);

    if (!ContentUris::isContentUri(m_Path))
    {
        return FileFolderPrivate::filePath(fileName);
    }

    DocumentFile parentDocumentFile = DocumentFile::fromUri(env, url().toString());
    if (!parentDocumentFile.isValid())
    {
        return QVariant();
    }

    DocumentFile documentFile = parentDocumentFile.findFile(fileName);
    if (!documentFile.isValid())
    {
        return QVariant();
    }

    return documentFile.getUri();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void FileFolderPrivateAndroid::names(QAndroidJniEnvironment& env, QStringList& entryList, const QString& uri, const QVariant& nameFilter, const bool recurse, bool files) const
{
    Q_UNUSED(recurse)
    Q_UNUSED(nameFilter)

    DocumentFile parentDocumentFile = DocumentFile::fromUri(env, uri);
    if (!parentDocumentFile.isValid())
    {
        return;
    }

    QStringList fileUris = parentDocumentFile.listFiles();

    foreach (QString fileUri, fileUris)
    {
        DocumentFile documentFile = DocumentFile::fromUri(env, fileUri);
        bool isFile = documentFile.isFile();
        if (isFile)
        {
            if (files)
            {
                entryList.append(documentFile.getName());
            }
        }

        bool isFolder = documentFile.isDirectory();
        if (isFolder)
        {
            if (!files)
            {
                entryList.append(documentFile.getName());
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
