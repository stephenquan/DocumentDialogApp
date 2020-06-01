//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "DocumentFile.h"
#include "JniExceptionCheck.h"
#include "DocumentsContract.h"
#include  <QtAndroid>

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

const char* DocumentFile::JCLASS = "com/arcgis/appframework/DocumentFile";

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentFile::DocumentFile(QAndroidJniEnvironment& env, QAndroidJniObject obj) :
    AndroidObject(env, JCLASS, obj)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentFile::DocumentFile(DocumentFile&& other) :
    AndroidObject(other.m_Env, JCLASS, other)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentFile::DocumentFile(DocumentFile& other) :
    AndroidObject(other.m_Env, JCLASS, other)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentFile::~DocumentFile()
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentFile DocumentFile::fromSingleUri(QAndroidJniEnvironment& env, const QString& uri)
{
    JniExceptionCheck check(env);

    QAndroidJniObject context = QtAndroid::androidContext();
    if (!context.isValid())
    {
        return DocumentFile(env);
    }

    QAndroidJniObject _uri = QAndroidJniObject::fromString(uri);
    if (!_uri.isValid())
    {
        return DocumentFile(env);
    }

    QAndroidJniObject __uri = QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri",
                "parse",
                "(Ljava/lang/String;)Landroid/net/Uri;",
                _uri.object<jstring>() );
    if (!__uri.isValid())
    {
        return DocumentFile(env);
    }

    QAndroidJniObject documentFile = QAndroidJniObject::callStaticObjectMethod(
                DocumentFile::JCLASS,
                "fromSingleUri",
                "(Landroid/content/Context;Landroid/net/Uri;)Lcom/arcgis/appframework/DocumentFile;",
                context.object(),
                __uri.object() );
    return DocumentFile(env, documentFile);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentFile DocumentFile::fromTreeUri(QAndroidJniEnvironment& env, const QString& treeUri)
{
    JniExceptionCheck check(env);

    QAndroidJniObject context = QtAndroid::androidContext();
    if (!context.isValid())
    {
        return DocumentFile(env);
    }

    QAndroidJniObject _treeUri = QAndroidJniObject::fromString(treeUri);
    if (!_treeUri.isValid())
    {
        return DocumentFile(env);
    }

    QAndroidJniObject __treeUri = QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri",
                "parse",
                "(Ljava/lang/String;)Landroid/net/Uri;",
                _treeUri.object<jstring>() );
    if (!__treeUri.isValid())
    {
        return DocumentFile(env);
    }

    QAndroidJniObject documentFile = QAndroidJniObject::callStaticObjectMethod(
                DocumentFile::JCLASS,
                "fromTreeUri",
                "(Landroid/content/Context;Landroid/net/Uri;)Lcom/arcgis/appframework/DocumentFile;",
                context.object(),
                __treeUri.object() );
    return DocumentFile(env, documentFile);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentFile DocumentFile::fromUri(QAndroidJniEnvironment& env, const QString& uri)
{
    if (DocumentsContract::isTreeUri(env, uri))
    {
        return fromTreeUri(env, uri);
    }

    return fromSingleUri(env, uri);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentFile::isDocumentUri(QAndroidJniEnvironment& env, const QString& uri)
{
    JniExceptionCheck check(env);

    QAndroidJniObject context = QtAndroid::androidContext();
    if (!context.isValid())
    {
        return false;
    }

    QAndroidJniObject _uri = QAndroidJniObject::fromString(uri);
    if (!_uri.isValid())
    {
        return false;
    }

    QAndroidJniObject __uri = QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri",
                "parse",
                "(Ljava/lang/String;)Landroid/net/Uri;",
                _uri.object<jstring>() );
    if (!__uri.isValid())
    {
        return false;
    }

    jboolean result = QAndroidJniObject::callStaticMethod<jboolean>(
                DocumentFile::JCLASS,
                "isDocumentUri",
                "(Landroid/content/Context;Landroid/net/Uri;)Lcom/arcgis/appframework/DocumentFile;",
                context.object(),
                __uri.object<jstring>());
    return result != JNI_FALSE;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentFile DocumentFile::createFile(const QString& mimeType, const QString& displayName) const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return DocumentFile(m_Env);
    }

    QAndroidJniObject _mimeType = QAndroidJniObject::fromString(mimeType);
    if (!_mimeType.isValid())
    {
        return DocumentFile(m_Env);
    }

    QAndroidJniObject _displayName = QAndroidJniObject::fromString(displayName);
    if (!_displayName.isValid())
    {
        return DocumentFile(m_Env);
    }

    QAndroidJniObject documentFile = callObjectMethod(
                "createFile",
                "(Ljava/lang/String;Ljava/lang/String;)Lcom/arcgis/appframework/DocumentFile;",
                _mimeType.object(),
                _displayName.object()
                );
    return DocumentFile(m_Env, documentFile);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentFile DocumentFile::createDirectory(const QString& displayName) const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return DocumentFile(m_Env);
    }

    QAndroidJniObject _displayName = QAndroidJniObject::fromString(displayName);
    if (!_displayName.isValid())
    {
        return DocumentFile(m_Env);
    }

    QAndroidJniObject documentFile = callObjectMethod(
                "createDirectory",
                "(Ljava/lang/String;)Lcom/arcgis/appframework/DocumentFile;",
                _displayName.object()
                );
    return DocumentFile(m_Env, documentFile);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentFile::getUri() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return QString();
    }

    QAndroidJniObject uri = callObjectMethod(
                "getUri",
                "()Landroid/net/Uri;"
                );
    if (!uri.isValid())
    {
        return QString();
    }
    return uri.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentFile::getName() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return QString();
    }

    QAndroidJniObject name = callObjectMethod(
                "getName",
                "()Ljava/lang/String;"
                );
    if (!name.isValid())
    {
        return QString();
    }
    return name.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString DocumentFile::getType() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return QString();
    }

    QAndroidJniObject type = callObjectMethod(
                "getType",
                "()Ljava/lang/String;"
                );
    if (!type.isValid())
    {
        return QString();
    }
    return type.toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentFile DocumentFile::getParentFile() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return DocumentFile(m_Env);
    }

    QAndroidJniObject documentFile = callObjectMethod(
                "getParentFile",
                "()Lcom/arcgis/appframework/DocumentFile;"
                );
    return DocumentFile(m_Env, documentFile);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentFile::isDirectory() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return false;
    }

    jboolean result = callMethod<jboolean>(
                "isDirectory",
                "()Z"
                );
    return result != JNI_FALSE;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentFile::isFile() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return false;
    }

    jboolean result = callMethod<jboolean>(
                "isFile",
                "()Z"
                );
    return result != JNI_FALSE;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentFile::isVirtual() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return false;
    }

    jboolean result = callMethod<jboolean>(
                "isVirtual",
                "()Z"
                );
    return result != JNI_FALSE;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

qint64 DocumentFile::lastModified() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return false;
    }

    jlong result = callMethod<jboolean>(
                "lastModified",
                "()J"
                );
    return result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

qint64 DocumentFile::length() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return false;
    }

    jlong result = callMethod<jlong>(
                "length",
                "()J"
                );
    return result;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentFile::canRead() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return false;
    }

    jboolean result = callMethod<jboolean>(
                "canRead",
                "()Z"
                );
    return result != JNI_FALSE;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentFile::canWrite() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return false;
    }

    jboolean result = callMethod<jboolean>(
                "canWrite",
                "()Z"
                );
    return result != JNI_FALSE;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentFile::deleteFile() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return false;
    }

    jboolean result = callMethod<jboolean>(
                "delete",
                "()Z"
                );
    return result != JNI_FALSE;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentFile::exists() const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return false;
    }

    jboolean result = callMethod<jboolean>(
                "exists",
                "()Z"
                );
    return result != JNI_FALSE;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QStringList DocumentFile::listFiles() const
{
    JniExceptionCheck check(m_Env);

    QStringList files;

    if (!isValid())
    {
        return files;
    }

    QAndroidJniObject _files = callObjectMethod(
                "listFiles",
                "()[Lcom/arcgis/appframework/DocumentFile;"
                );
    if (!_files.isValid())
    {
        return files;
    }

    jobjectArray fileArray = _files.object<jobjectArray>();
    jsize fileArraySize  = m_Env->GetArrayLength(fileArray);
    for (jint i = 0; i < fileArraySize; i++)
    {
        jobject fileObject = m_Env->GetObjectArrayElement(fileArray, i);

        QAndroidJniObject _fileObject = QAndroidJniObject::fromLocalRef(fileObject);
        if (!_fileObject.isValid())
        {
            m_Env->DeleteLocalRef(fileObject);
            continue;
        }

        QAndroidJniObject uri = _fileObject.callObjectMethod(
                    "getUri",
                    "()Landroid/net/Uri;"
                    );
        if (!uri.isValid())
        {
            m_Env->DeleteLocalRef(fileObject);
            continue;
        }

        files.append(uri.toString());
    }

    return files;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentFile DocumentFile::findFile(const QString& displayName) const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return DocumentFile(m_Env);
    }

    QAndroidJniObject _displayName = QAndroidJniObject::fromString(displayName);
    if (!_displayName.isValid())
    {
        return DocumentFile(m_Env);
    }

    QAndroidJniObject documentFile = callObjectMethod(
                "findFile",
                "(Ljava/lang/String;)Lcom/arcgis/appframework/DocumentFile;",
                _displayName.object()
                );
    return DocumentFile(m_Env, documentFile);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool DocumentFile::renameTo(const QString& displayName) const
{
    JniExceptionCheck check(m_Env);

    if (!isValid())
    {
        return false;
    }

    QAndroidJniObject _displayName = QAndroidJniObject::fromString(displayName);
    if (!_displayName.isValid())
    {
        return false;
    }

    jboolean result = callMethod<jboolean>(
                "renameTo",
                "(Ljava/lang/String;)Z",
                _displayName.object()
                );
    return result != JNI_FALSE;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
