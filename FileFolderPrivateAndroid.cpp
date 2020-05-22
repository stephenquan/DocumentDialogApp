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

QStringList FileFolderPrivateAndroid::fileNames() const
{
    QAndroidJniEnvironment env;

    if (!ContentUris::isContentUri(m_Path)) return FileFolderPrivate::fileNames();

    DocumentsContract documentsContract(env);
    QString treeDocumentId = documentsContract.getTreeDocumentId(m_Path);
    if (treeDocumentId.isEmpty() || treeDocumentId.isNull())
    {
        return QStringList();
    }

    QString childDocumentsUri = documentsContract.buildChildDocumentsUriUsingTree(m_Path, treeDocumentId);
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
