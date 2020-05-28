//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __FileFolderPrivateAndroid__
#define __FileFolderPrivateAndroid__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QObject>
#include <QVariant>
#include <QAndroidJniEnvironment>
#include "FileFolderPrivate.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class FileFolderPrivateAndroid : public FileFolderPrivate
{
    Q_OBJECT

public:
    FileFolderPrivateAndroid(QObject* parent = nullptr);

    virtual QStringList fileNames(const QVariant& nameFilter = QStringLiteral("*"), bool subFolders = false) const Q_DECL_OVERRIDE;
    virtual QStringList folderNames(const QVariant& nameFilter = QStringLiteral("*"), bool subFolders = false) const Q_DECL_OVERRIDE;
    virtual QString filePath(const QString& fileName) const Q_DECL_OVERRIDE;
    virtual QVariant fileUrl(const QString& fileName) const Q_DECL_OVERRIDE;

    void names(QStringList& entryList, const QString& uri, const bool recurse, bool files, const QVariant&nameFilter, bool subFolders, QAndroidJniEnvironment& env) const;

    virtual QVariant url() const Q_DECL_OVERRIDE;
    virtual void setUrl(const QVariant& url) Q_DECL_OVERRIDE;

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
