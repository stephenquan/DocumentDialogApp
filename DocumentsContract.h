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
#include "AndroidObject.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class DocumentsContract : public AndroidObject
{
public:
    DocumentsContract(QAndroidJniEnvironment& env, QAndroidJniObject obj = QAndroidJniObject());

    static const char* JCLASS;

    // DocumentContracts methods
    static QString getDocumentId(QAndroidJniEnvironment& env, const QString& uri);
    static QString getTreeDocumentId(QAndroidJniEnvironment& env, const QString& uri);
    static QString buildChildDocumentsUri(QAndroidJniEnvironment& env, const QString& authority, const QString& parentDocumentId);
    static QString buildChildDocumentsUriUsingTree(QAndroidJniEnvironment& env, const QString& uri, const QString& documentId);
    static QString buildDocumentUri(QAndroidJniEnvironment& env, const QString& authority, const QString& documentId);
    static QString buildDocumentUriUsingTree(QAndroidJniEnvironment& env, const QString& uri, const QString& documentId);
    static QString buildTreeDocumentUri(QAndroidJniEnvironment& env, const QString& authority, const QString& documentId);
    static bool isTreeUri(QAndroidJniEnvironment& env, const QString& uri);

    // Helper methods
    static QString mimeType(QAndroidJniEnvironment& env, const QString& uri);
    static QString displayName(QAndroidJniEnvironment& env, const QString& uri);
    static qint64 size(QAndroidJniEnvironment& env, const QString& uri);
    static QStringList documentIds(QAndroidJniEnvironment& env, const QString& uri);
    static bool exists(QAndroidJniEnvironment& env, const QString& uri);
    static QStringList childDocumentIds(QAndroidJniEnvironment& env, const QString& uri);
    static QStringList childDocumentUris(QAndroidJniEnvironment& env, const QString& uri);
    static bool isDirectory(QAndroidJniEnvironment& env, const QString& uri);
    static bool isFile(QAndroidJniEnvironment& env, const QString& uri);

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
