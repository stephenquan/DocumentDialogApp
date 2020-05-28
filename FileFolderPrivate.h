//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __FileFolderPrivate__
#define __FileFolderPrivate__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QObject>
#include <QVariant>
#include <QDir>
#include <QUrl>

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class FileFolderPrivate : public QObject
{
    Q_OBJECT

public:
    FileFolderPrivate(QObject* parent = nullptr);

    virtual QString path() const;
    virtual void setPath(const QString& path);
    virtual QVariant url() const;
    virtual void setUrl(const QVariant& url);
    virtual QStringList fileNames(const QVariant& nameFilter = QStringLiteral("*"), bool subFolders = false) const;
    virtual QStringList folderNames(const QVariant& nameFilter = QStringLiteral("*"), bool subFolders = false) const;
    virtual QString filePath(const QString& fileName) const;
    virtual QVariant fileUrl(const QString& fileName) const;

    QDir dir() const;
    void names(QStringList& entryList, const QDir& dir, const QStringList& nameFilters, const QString &basePath, bool recurse, bool files) const;
    QStringList nameFilters(const QVariant& nameFilter) const;

signals:
    void fileFolderChanged();

protected:
    QString m_Path;

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
