#ifndef __FileInfoPrivateAndroid__
#define __FileInfoPrivateAndroid__

#include <QObject>
#include <QVariant>
#include <QAndroidJniEnvironment>
#include "FileInfoPrivate.h"

class FileInfoPrivateAndroid : public FileInfoPrivate
{
    Q_OBJECT

public:
    FileInfoPrivateAndroid(QObject* parent = nullptr);

    virtual QString absoluteFilePath() const Q_DECL_OVERRIDE;
    virtual QString absolutePath() const Q_DECL_OVERRIDE;
    virtual QString baseName() const Q_DECL_OVERRIDE;
    virtual QString displayName() const Q_DECL_OVERRIDE;
    virtual bool exists() const Q_DECL_OVERRIDE;
    virtual QString fileName() const Q_DECL_OVERRIDE;
    virtual QString filePath() const Q_DECL_OVERRIDE;
    virtual FileFolder* folder() const Q_DECL_OVERRIDE;
    virtual bool isFile() const Q_DECL_OVERRIDE;
    virtual bool isDir() const Q_DECL_OVERRIDE;
    virtual qint64 size() const Q_DECL_OVERRIDE;
    virtual QByteArray readAll() const Q_DECL_OVERRIDE;
    virtual QVariant extra() const Q_DECL_OVERRIDE;

    bool isContentUri() const;
    virtual void setUrl(const QVariant& url) Q_DECL_OVERRIDE;

};

#endif
