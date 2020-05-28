//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __FileFolder__
#define __FileFolder__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QObject>
#include <QVariant>

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class FileFolderPrivate;

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class FileFolder : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY fileFolderChanged)
    Q_PROPERTY(QVariant url READ url WRITE setUrl NOTIFY fileFolderChanged)

public:
    FileFolder(QObject* parent = nullptr);
    ~FileFolder();

    Q_INVOKABLE QStringList fileNames(const QVariant& nameFilter = QStringLiteral("*"), bool subFolders = false) const;
    Q_INVOKABLE QStringList folderNames(const QVariant& nameFilter = QStringLiteral("*"), bool subFolders = false) const;
    Q_INVOKABLE QString filePath(const QString& fileName) const;
    Q_INVOKABLE QVariant fileUrl(const QString& fileName) const;

public:
    QString path() const;
    void setPath(const QString& path);
    QVariant url() const;
    void setUrl(const QVariant& url);

signals:
    void fileFolderChanged();

protected:
    FileFolderPrivate* m_FileFolderPrivate;

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
