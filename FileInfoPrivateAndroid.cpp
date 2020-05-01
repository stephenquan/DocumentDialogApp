#include "FileInfoPrivateAndroid.h"
#include <QtAndroid>
#include "ContentResolver.h"
#include "JniEnvironment.h"

FileInfoPrivateAndroid::FileInfoPrivateAndroid(QObject* parent) :
    FileInfoPrivate(parent)
{
}

QString FileInfoPrivateAndroid::absoluteFilePath() const
{
    if (!isContentUri()) return FileInfoPrivate::absoluteFilePath();
    return m_Url.toString();
}

QString FileInfoPrivateAndroid::absolutePath() const
{
    if (!isContentUri()) return FileInfoPrivate::absolutePath();
    return m_Url.toString();
}

QString FileInfoPrivateAndroid::baseName() const
{
    if (!isContentUri()) return FileInfoPrivate::baseName();
    return QFileInfo(fileName()).baseName();
}

bool FileInfoPrivateAndroid::exists() const
{
    if (!isContentUri()) return FileInfoPrivate::exists();
    QVariant size = ContentResolver::queryContentUri(url().toString(), "SIZE");
    return size.isValid() && !size.isNull();
}

QString FileInfoPrivateAndroid::fileName() const
{
    if (!isContentUri()) return FileInfoPrivate::fileName();
    QVariant displayName = ContentResolver::queryContentUri(url().toString(), "DISPLAY_NAME");
    return displayName.toString();
}

QString FileInfoPrivateAndroid::filePath() const
{
    if (!isContentUri()) return FileInfoPrivate::filePath();
    return m_Url.toString();
}

qint64 FileInfoPrivateAndroid::size() const
{
    if (!isContentUri()) return FileInfoPrivate::size();
    QVariant size = ContentResolver::queryContentUri(url().toString(), "SIZE");
    if (!size.isValid() || size.isNull()) return -1;
    return size.toLongLong();
}

QByteArray FileInfoPrivateAndroid::readAll() const
{
    if (!isContentUri()) return FileInfoPrivate::readAll();

    JniEnvironment env;

    QAndroidJniObject strUri = QAndroidJniObject::fromString(m_Url.toString());
    QAndroidJniObject uri = QAndroidJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;", strUri.object< jstring >() );
    if (!uri.isValid()) return QByteArray();

    QAndroidJniObject contentResolver = QtAndroid::androidActivity().callObjectMethod("getContentResolver","()Landroid/content/ContentResolver;");
    if (!contentResolver.isValid()) return QByteArray();

    QAndroidJniObject inputStream = contentResolver.callObjectMethod("openInputStream", "(Landroid/net/Uri;)Ljava/io/InputStream;", uri.object());
    if (!inputStream.isValid()) return QByteArray();

    QByteArray fileBytes;
    jbyteArray block = env->NewByteArray(1024);
    jint size = inputStream.callMethod<jint>("read", "([BII)I", block, 0, 1024);
    while (size > 0)
    {
        jboolean isCopy = false;
        jbyte* blockBytes = env->GetByteArrayElements(block, &isCopy);
        fileBytes.append(reinterpret_cast<const char *>(blockBytes), static_cast<int>(size));
        env->ReleaseByteArrayElements(block, blockBytes, JNI_ABORT);
        size = inputStream.callMethod<jint>("read", "([BII)I", block, 0, 1024);
    }

    return fileBytes;
}

bool FileInfoPrivateAndroid::isContentUri() const
{
    return ContentResolver::isContentUri(url().toString());
}
