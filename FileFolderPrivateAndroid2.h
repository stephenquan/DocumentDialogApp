//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __FileFolderPrivateAndroid2__
#define __FileFolderPrivateAndroid2__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QObject>
#include <QVariant>
#include <QAndroidJniEnvironment>
#include "FileFolderPrivate.h"
#include "DocumentFile.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class FileFolderPrivateAndroid2 : public FileFolderPrivate
{
    Q_OBJECT

public:
    FileFolderPrivateAndroid2(QObject* parent = nullptr);

    virtual QStringList fileNames(const QVariant& nameFilter = QStringLiteral("*"), bool subFolders = false) const Q_DECL_OVERRIDE;
    virtual QStringList folderNames(const QVariant& nameFilter = QStringLiteral("*"), bool subFolders = false) const Q_DECL_OVERRIDE;
    virtual QString filePath(const QString& fileName) const Q_DECL_OVERRIDE;
    virtual QVariant fileUrl(const QString& fileName) const Q_DECL_OVERRIDE;

    void names(QAndroidJniEnvironment& env, QStringList& entryList, const QString& uri, const QVariant&nameFilter, const bool recurse, bool files) const;

    virtual QVariant url() const Q_DECL_OVERRIDE;
    virtual void setUrl(const QVariant& url) Q_DECL_OVERRIDE;

protected:
    DocumentFile* m_DocumentFile;

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
