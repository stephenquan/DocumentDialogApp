#ifndef __FileFolderPrivate__
#define __FileFolderPrivate__

#include <QObject>
#include <QVariant>
#include <QDir>
#include <QUrl>

class FileFolderPrivate : public QObject
{
    Q_OBJECT

public:
    FileFolderPrivate(QObject* parent = nullptr);

    virtual QString path() const;
    virtual void setPath(const QString& path);
    virtual QStringList fileNames() const;

    QDir dir() const;

signals:
    void fileFolderChanged();

protected:
    QString m_Path;

};

#endif
