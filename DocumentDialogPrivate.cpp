//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "DocumentDialogPrivate.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

Q_LOGGING_CATEGORY(documentDialog, "stephenquan.DocumentDialog")

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentDialogPrivate::DocumentDialogPrivate(QObject* parent) :
    QObject(parent),
    m_SelectFolder(false)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void DocumentDialogPrivate::open()
{
    qCDebug(documentDialog, "open");

    emit rejected();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void DocumentDialogPrivate::setFileUrl(const QVariant& fileUrl)
{
    if (fileUrl == m_FileUrl)
    {
        return;
    }

    qCDebug(documentDialog, "fileUrl %s", fileUrl.toString().toUtf8().constData());

    m_FileUrl = fileUrl;

    emit fileUrlChanged();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void DocumentDialogPrivate::setSelectFolder(bool selectFolder)
{
    if (selectFolder == m_SelectFolder)
    {
        return;
    }

    m_SelectFolder = selectFolder;

    emit selectFolderChanged();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
