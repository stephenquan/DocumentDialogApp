//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "DocumentDialog.h"
#ifdef Q_OS_ANDROID
#include "DocumentDialogPrivateAndroid.h"
#endif
#ifndef Q_OS_ANDROID
#include "DocumentDialogPrivate.h"
#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentDialog::DocumentDialog(QObject* parent) :
    QObject(parent)
#ifdef Q_OS_ANDROID
    , m_DocumentDialogPrivate(new DocumentDialogPrivateAndroid)
#endif
#ifndef Q_OS_ANDROID
    , m_DocumentDialogPrivate(new DocumentDialogPrivate)
#endif
{
    connect(m_DocumentDialogPrivate, &DocumentDialogPrivate::fileUrlChanged, this, &DocumentDialog::fileUrlChanged);
    connect(m_DocumentDialogPrivate, &DocumentDialogPrivate::selectFolderChanged, this, &DocumentDialog::selectFolderChanged);
    connect(m_DocumentDialogPrivate, &DocumentDialogPrivate::accepted, this, &DocumentDialog::accepted);
    connect(m_DocumentDialogPrivate, &DocumentDialogPrivate::rejected, this, &DocumentDialog::rejected);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentDialog::~DocumentDialog()
{
    disconnect(m_DocumentDialogPrivate, &DocumentDialogPrivate::fileUrlChanged, this, &DocumentDialog::fileUrlChanged);
    disconnect(m_DocumentDialogPrivate, &DocumentDialogPrivate::selectFolderChanged, this, &DocumentDialog::selectFolderChanged);
    disconnect(m_DocumentDialogPrivate, &DocumentDialogPrivate::accepted, this, &DocumentDialog::accepted);
    disconnect(m_DocumentDialogPrivate, &DocumentDialogPrivate::rejected, this, &DocumentDialog::rejected);
    delete m_DocumentDialogPrivate;
    m_DocumentDialogPrivate = nullptr;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QVariant DocumentDialog::fileUrl() const
{
    return m_DocumentDialogPrivate->fileUrl();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentDialog::selectFolder() const
{
    return m_DocumentDialogPrivate->selectFolder();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void DocumentDialog::setSelectFolder(bool selectFolder)
{
    m_DocumentDialogPrivate->setSelectFolder(selectFolder);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void DocumentDialog::open()
{
    m_DocumentDialogPrivate->open();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
