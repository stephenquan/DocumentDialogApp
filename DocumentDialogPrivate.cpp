#include "DocumentDialogPrivate.h"

Q_LOGGING_CATEGORY(documentDialog, "stephenquan.DocumentDialog")

DocumentDialogPrivate::DocumentDialogPrivate(QObject* parent) :
    QObject(parent)
{
}

void DocumentDialogPrivate::open()
{
    qCDebug(documentDialog, "open");

    emit rejected();
}

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
