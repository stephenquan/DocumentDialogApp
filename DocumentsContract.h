//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __DocumentsContract__
#define __DocumentsContract__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QObject>
#include <QVariant>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include "AndroidObject.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class DocumentsContract : public AndroidObject
{
    Q_OBJECT

public:
    DocumentsContract(QAndroidJniEnvironment& env, QObject* parent = nullptr);

    virtual const char* jclass() const { return "android/provider/DocumentsContract"; }

    QString getDocumentId(const QString& uri) const;
    QString getTreeDocumentId(const QString& uri) const;
    QString buildChildDocumentsUri(const QString& authority, const QString& parentDocumentId) const;
    QString buildChildDocumentsUriUsingTree(const QString& uri, const QString& documentId) const;
    QString buildDocumentUri(const QString& authority, const QString& documentId) const;
    QString buildDocumentUriUsingTree(const QString& uri, const QString& documentId) const;
    QString buildTreeDocumentUri(const QString& authority, const QString& documentId) const;
    bool isTreeUri(const QString& uri) const;

    QString mimeType(const QString& uri) const;
    QString displayName(const QString& uri) const;
    qint64 size(const QString& uri) const;
    QStringList documentIds(const QString& uri) const;
    bool exists(const QString& uri) const;
    QStringList childDocumentIds(const QString& uri) const;
    QStringList childDocumentUris(const QString& uri) const;
    bool isFolder(const QString& uri) const;
    bool isFile(const QString& uri) const;

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
