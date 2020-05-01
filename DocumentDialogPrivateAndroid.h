#ifndef __DocumentDialogPrivateAndroid__
#define __DocumentDialogPrivateAndroid__

#include <QObject>
#include <QAndroidActivityResultReceiver>
#include <QLoggingCategory>
#include "DocumentDialogPrivate.h"


class DocumentDialogPrivateAndroid : public DocumentDialogPrivate, public QAndroidActivityResultReceiver
{
    Q_OBJECT

public:
    DocumentDialogPrivateAndroid(QObject* parent = nullptr);

    void open() Q_DECL_OVERRIDE;

    virtual void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data) Q_DECL_OVERRIDE;

};

#endif
