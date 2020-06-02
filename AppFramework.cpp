//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "AppFramework.h"
#include "FileFolder.h"
#include "FileInfo.h"
#include <QDebug>

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

AppFramework::AppFramework(QObject* parent) :
    QObject(parent)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QObject* AppFramework::singletonProvider(QQmlEngine *, QJSEngine *)
{
    return new AppFramework();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

FileFolder* AppFramework::fileFolder(const QVariant& url)
{
    FileFolder* fileFolder = new FileFolder();
    fileFolder->setUrl(url);
    QQmlEngine::setObjectOwnership(fileFolder, QQmlEngine::JavaScriptOwnership);
    return fileFolder;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

FileInfo* AppFramework::fileInfo(const QVariant& url)
{
    FileInfo* fileInfo = new FileInfo();
    fileInfo->setUrl(url);
    QQmlEngine::setObjectOwnership(fileInfo, QQmlEngine::JavaScriptOwnership);
    return fileInfo;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString AppFramework::btoa(const QVariant& data)
{
    return data.toByteArray().toBase64();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
