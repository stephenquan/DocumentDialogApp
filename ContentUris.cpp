#include "ContentUris.h"
#include "JniExceptionCheck.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

ContentUris::ContentUris(QAndroidJniEnvironment& env, QObject* parent) :
    QObject(parent),
    m_Env(env)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool ContentUris::isContentUri(const QString& uri)
{
    return QUrl(uri).scheme() == "content";
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool ContentUris::parseContentUri(const QString& contentUri, QString& scheme, QString& authority, QString& treeOrDocument, QString& type, QStringList& path)
{
    QRegExp rx("^(content):[/][/]([^/]*)[/](tree|document)[/](.*)%3A(.*)$");
    if (rx.indexIn(contentUri) != 0)
    {
        return false;
    }
    scheme = rx.cap(1);
    authority = rx.cap(2);
    treeOrDocument = rx.cap(3);
    type = rx.cap(4);
    path = rx.cap(5).split("%2F");
    return true;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString ContentUris::buildContentUri(const QString& scheme, const QString& authority, const QString& treeOrDocument, const QString& type, const QStringList& path)
{
    return scheme + "://" + authority + "/" + treeOrDocument + "/" + type + "%3A" + (path.join("%2F"));
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
