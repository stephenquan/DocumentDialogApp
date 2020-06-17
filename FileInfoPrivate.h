//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __FileInfoPrivate__
#define __FileInfoPrivate__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QObject>
#include <QVariant>
#include <QFileInfo>
#include <QDateTime>
#include <QUrl>

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class FileFolder;

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class FileInfoPrivate : public QObject
{
    Q_OBJECT

public:
    FileInfoPrivate(QObject* parent = nullptr);

    virtual QString absolutePath() const;
    virtual QString absoluteFilePath() const;
    virtual QString baseName() const;
    virtual bool exists() const;
    virtual FileFolder* folder() const;
    virtual QString displayName() const;
    virtual QString fileName() const;
    virtual QString filePath() const;
    virtual QString path() const;
    virtual bool isFile() const;
    virtual bool isDir() const;
    virtual QByteArray readAll() const;
    virtual qint64 size() const;
    virtual QString type() const;
    virtual QDateTime lastModified() const;
    virtual QVariant extra() const;

    virtual QVariant url() const { return m_Url; }
    virtual void setUrl(const QVariant& url);

    QFileInfo fileInfo() const;
    static QFileInfo fileInfo(const QVariant& fileSource);
    static QFileInfo fileInfo(const QUrl& fileUrl);
    static QFileInfo fileInfo(const QString& filePath);

signals:
    void fileInfoChanged();

protected:
    QVariant m_Url;
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
