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

protected:
    QAndroidJniEnvironment& m_Env;

    QAndroidJniObject documentsContract();

};

#endif
