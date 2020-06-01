//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __DocumentFile__
#define __DocumentFile__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "AndroidObject.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class DocumentFile : public AndroidObject
{
public:
    DocumentFile(QAndroidJniEnvironment& env, QAndroidJniObject obj = QAndroidJniObject());
    DocumentFile(DocumentFile&& other);
    DocumentFile(DocumentFile& other);
    virtual ~DocumentFile();

    static const char* JCLASS;

    static DocumentFile fromSingleUri(QAndroidJniEnvironment& env, const QString& uri);
    static DocumentFile fromTreeUri(QAndroidJniEnvironment& env, const QString& treeUri);
    static DocumentFile fromUri(QAndroidJniEnvironment& env, const QString& uri);

    static bool isDocumentUri(QAndroidJniEnvironment& env, const QString& uri);
    DocumentFile createFile(const QString& mimeType, const QString& displayName) const;
    DocumentFile createDirectory(const QString& displayName) const;
    QString getUri() const;
    QString getName() const;
    QString getType() const;
    DocumentFile getParentFile() const;
    bool isDirectory() const;
    bool isFile() const;
    bool isVirtual() const;
    qint64 lastModified() const;
    qint64 length() const;
    bool canRead() const;
    bool canWrite() const;
    bool deleteFile() const;
    bool exists() const;
    QStringList listFiles() const;
    DocumentFile findFile(const QString& displayName) const;
    bool renameTo(const QString& displayName) const;

};

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
