//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __ContentUris__
#define __ContentUris__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QObject>
#include <QVariant>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QUrl>
#include "InputStream.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class ContentUris : public QObject
{
    Q_OBJECT

public:
    ContentUris(QAndroidJniEnvironment& env, QObject* parent = nullptr);

    static bool isContentUri(const QString& uri);
    static bool parseContentUri(const QString& contentUri, QString& scheme, QString& authority, QString& treeOrDocument, QString& type, QStringList& path);
    static QString buildContentUri(const QString& scheme, const QString& authority, const QString& treeOrDocument, const QString& type, const QStringList& path);

protected:
    QAndroidJniEnvironment& m_Env;

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
