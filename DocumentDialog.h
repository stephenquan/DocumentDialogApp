#ifndef __DocumentDialog__
#define __DocumentDialog__

#include <QObject>
#include <QVariant>

class DocumentDialogPrivate;

class DocumentDialog : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant fileUrl READ fileUrl NOTIFY fileUrlChanged)

public:
    DocumentDialog(QObject* parent = nullptr);
    ~DocumentDialog();

    Q_INVOKABLE void open();

signals:
    void fileUrlChanged();

    void accepted();
    void rejected();

protected:
    DocumentDialogPrivate* m_DocumentDialogPrivate;

    QVariant fileUrl() const;

};

#endif
