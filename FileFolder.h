#ifndef __FileFolder__
#define __FileFolder__

#include <QObject>
#include <QVariant>

class FileFolderPrivate;

class FileFolder : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY fileFolderChanged)

public:
    FileFolder(QObject* parent = nullptr);
    ~FileFolder();

    Q_INVOKABLE QStringList fileNames() const;

public:
    QString path() const;
    void setPath(const QString& path);

signals:
    void fileFolderChanged();

protected:
    FileFolderPrivate* m_FileFolderPrivate;

};

#endif
