#include <QAndroidJniEnvironment>
#include <QDebug>

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

QString FileFolderPrivateAndroid::filePath(const QString& fileName) const
{
    if (!ContentUris::isContentUri(m_Path)) return FileFolderPrivate::filePath(fileName);

    return fileName;
}

QVariant FileFolderPrivateAndroid::fileUrl(const QString& fileName) const
{
    if (!ContentUris::isContentUri(m_Path)) return FileFolderPrivate::filePath(fileName);

    return fileName;
}

void FileFolderPrivateAndroid::names(QStringList& entryList, const QString& uri, const bool recurse, bool files, const QVariant& nameFilter, bool subFolders, QAndroidJniEnvironment& env) const
{
    Q_UNUSED(nameFilter)
    Q_UNUSED(subFolders)

    ContentResolver contentResolver(env);
    DocumentsContract documentsContract(env);

    foreach (QString content, contentList(uri, env))
    {
        //QStringList displayName =  contentResolver.query(content, "android/provider/MediaStore$MediaColumns", "DISPLAY_NAME");
        //bool isFile = displayName.length() > 0;
        //bool isFolder = !isFile;
        //bool isFolder = documentsContract.isTreeUri(content);
        //bool isFile = !isFolder;
        QStringList mimeTypes = contentResolver.query(content, "android/provider/MediaStore$MediaColumns", "MIME_TYPE");
        QString mimeType = mimeTypes.length() > 0 ? mimeTypes[0] : "";
        bool isFolder = (mimeType == "vnd.android.document/directory" || mimeType == "");
        bool isFile = !isFolder;
        if (isFile)
        {
            if (files)
            {
                //entryList.append("FILE " + mimeType + " " + content);
                entryList.append(content);
            }
        }

        if (isFolder)
        {
            if (!files)
            {
                //entryList.append("FOLDER " + mimeType + " " + content);
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

    QString scheme;
    QString authority;
    QString treeOrDocument;
    QString type;
    QStringList path;
    //ContentUris::parseContentUri(uri, scheme, authority, treeOrDocument, type, path);
    authority = QUrl(uri).host();

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
        QString childTreeDocumentUri = documentsContract.buildDocumentUriUsingTree(m_Path, childDocumentId);
        QString childDocumentUri = documentsContract.buildDocumentUri(authority, childDocumentId);
        QStringList mimeTypes = contentResolver.query(childTreeDocumentUri, "android/provider/MediaStore$MediaColumns", "MIME_TYPE");
        QString mimeType = mimeTypes.length() > 0 ? mimeTypes[0] : "";
        if (mimeType == "vnd.android.document/directory" || mimeType == "")
        {
            //childDocumentUris.append("TREE " + mimeType + " " + childTreeDocumentUri);
            //childDocumentUris.append(childTreeDocumentUri);
        }
        else
        {
            //childDocumentUris.append("DOCUMENT " + mimeType + " " + childDocumentUri);
            //childDocumentUris.append(childDocumentUri);
        }
        childDocumentUris.append(childTreeDocumentUri);
        //childDocumentUris.append(childDocumentUri);
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
