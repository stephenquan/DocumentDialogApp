#ifndef __FileFolderPrivateAndroid__
#define __FileFolderPrivateAndroid__

#include <QObject>
#include <QVariant>
#include "FileFolderPrivate.h"

class FileFolderPrivateAndroid : public FileFolderPrivate
{
    Q_OBJECT

public:
    FileFolderPrivateAndroid(QObject* parent = nullptr);

    virtual QStringList fileNames() const Q_DECL_OVERRIDE;

};

#endif
