#ifndef __DocumentsContract__
#define __DocumentsContract__

#include <QObject>
#include <QVariant>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>

class DocumentsContract : public QObject
{
    Q_OBJECT

public:
    DocumentsContract(QAndroidJniEnvironment& env, QObject* parent = nullptr);
    ~DocumentsContract();

    QString getDocumentId(const QString& uri);
    QString getTreeDocumentId(const QString& uri);
    QString buildChildDocumentsUriUsingTree(const QString& uri, const QString& documentId);
    QString buildDocumentUriUsingTree(const QString& uri, const QString& documentId);

protected:
    QAndroidJniEnvironment& m_Env;

    QAndroidJniObject documentsContract();

};

#endif
