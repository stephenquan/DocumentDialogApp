#ifndef __DocumentDialogPrivate__
#define __DocumentDialogPrivate__

#include <QObject>
#include <QUrl>
#include <QVariant>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(documentDialog)

class DocumentDialogPrivate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant fileUrl READ fileUrl NOTIFY fileUrlChanged)

public:
    DocumentDialogPrivate(QObject* parent = nullptr);

    virtual void open();

    QVariant fileUrl() const { return m_FileUrl; }
    void setFileUrl(const QVariant& fileUrl);

signals:
    void fileUrlChanged();

    void rejected();
    void accepted();

protected:
    QVariant m_FileUrl;


};

#endif
