#include <QAndroidJniEnvironment>

#include "FileFolderPrivateAndroid.h"
#include "ContentUris.h"
#include "ContentResolver.h"
#include "DocumentsContract.h"
#include "JniExceptionCheck.h"

FileFolderPrivateAndroid::FileFolderPrivateAndroid(QObject* parent) :
    FileFolderPrivate(parent)
{
}

QStringList FileFolderPrivateAndroid::fileNames(const QVariant& nameFilter, bool subFolders) const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(m_Path)) return FileFolderPrivate::fileNames();

    DocumentsContract documentsContract(env);

    if (!documentsContract.isTreeUri(m_Path)) return QStringList();

    QStringList entryList;

    names(entryList, m_Path, subFolders, true, nameFilter, subFolders, env);

    return entryList;
}

QStringList FileFolderPrivateAndroid::folderNames(const QVariant& nameFilter, bool subFolders) const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(m_Path)) return FileFolderPrivate::fileNames();

    DocumentsContract documentsContract(env);

    if (!documentsContract.isTreeUri(m_Path)) return QStringList();

    QStringList entryList;

    names(entryList, m_Path, subFolders, false, nameFilter, subFolders, env);

    return entryList;
}

void FileFolderPrivateAndroid::names(QStringList& entryList, const QString& uri, const bool recurse, bool files, const QVariant& nameFilter, bool subFolders, QAndroidJniEnvironment& env) const
{
    Q_UNUSED(nameFilter)
    Q_UNUSED(subFolders)

    ContentResolver contentResolver(env);
    DocumentsContract documentsContract(env);

    foreach (QString content, contentList(uri, env))
    {
        QStringList displayName =  contentResolver.query(content, "android/provider/MediaStore$MediaColumns", "DISPLAY_NAME");
        bool isFile = displayName.length() > 0;
        if (isFile)
        {
            if (files)
            {
                entryList.append(content);
            }
        }

        bool isFolder = !isFile;
        if (isFolder)
        {
            if (!files)
            {
                entryList.append(content);
            }
        }
    }
}

QStringList FileFolderPrivateAndroid::contentList(const QString& uri, QAndroidJniEnvironment& env) const
{
    DocumentsContract documentsContract(env);
    QString treeDocumentId = documentsContract.getTreeDocumentId(m_Path);
    if (treeDocumentId.isEmpty() || treeDocumentId.isNull())
    {
        return QStringList();
    }

    QString childDocumentsUri = documentsContract.buildChildDocumentsUriUsingTree(uri, treeDocumentId);

    if (childDocumentsUri.isEmpty() || childDocumentsUri.isNull())
    {
        return QStringList();
    }

    QStringList childDocumentUris;
    ContentResolver contentResolver(env);
    QStringList childDocumentIds = contentResolver.query(childDocumentsUri,  "android/provider/DocumentsContract$Document", "COLUMN_DOCUMENT_ID");

    foreach (QString childDocumentId, childDocumentIds)
    {
        QString childDocumentUri = documentsContract.buildDocumentUriUsingTree(m_Path, childDocumentId);
        childDocumentUris.append(childDocumentUri);
    }
    return childDocumentUris;
}

QVariant FileFolderPrivateAndroid::url() const
{
    return path();
}

void FileFolderPrivateAndroid::setUrl(const QVariant& url)
{
    setPath(url.toString());
}
