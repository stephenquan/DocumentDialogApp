#include <QAndroidJniEnvironment>
#include "InputStream.h"
#include "JniExceptionCheck.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

InputStream::InputStream(QAndroidJniEnvironment& env, QObject* parent, QAndroidJniObject inputStream) :
    QObject(parent),
    m_Env(env),
    m_InputStream(inputStream)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

InputStream::InputStream(InputStream &&other) :
    QObject(nullptr),
    m_Env(other.m_Env),
    m_InputStream(other.m_InputStream)
{
    other.m_InputStream = QAndroidJniObject();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

InputStream::~InputStream()
{
    if (!m_InputStream.isValid())
    {
        return;
    }

    close();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

int InputStream::available()
{
    JniExceptionCheck check(m_Env);

    if (!m_InputStream.isValid())
    {
        return 0;
    }

    jint result = m_InputStream.callMethod<jint>("available", "()I");
    return static_cast<int>(result);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void InputStream::close()
{
    JniExceptionCheck check(m_Env);

    if (!m_InputStream.isValid())
    {
        return;
    }

    m_InputStream.callMethod<void>("close", "()V");
    m_InputStream = QAndroidJniObject();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QByteArray InputStream::read(int n)
{
    JniExceptionCheck check(m_Env);

    if (!m_InputStream.isValid())
    {
        return QByteArray();
    }

    QByteArray byteArray;
    jbyteArray _byteArray = m_Env->NewByteArray(n);
    jint size = m_InputStream.callMethod<jint>("read", "([BII)I", _byteArray, 0, n);
    if (size > 0)
    {
        jboolean isCopy = false;
        jbyte* _bytes = m_Env->GetByteArrayElements(_byteArray, &isCopy);
        byteArray.append(reinterpret_cast<const char *>(_bytes), static_cast<int>(size));
    }

    return byteArray;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void InputStream::reset()
{
    JniExceptionCheck check(m_Env);

    if (m_InputStream.isValid())
    {
        return;
    }

    m_InputStream.callMethod<void>("reset", "()V");
    m_InputStream = QAndroidJniObject();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

qint64 InputStream::skip(qint64 n)
{
    JniExceptionCheck check(m_Env);

    if (!m_InputStream.isValid())
    {
        return 0;
    }

    jint result = m_InputStream.callMethod<jint>("skip", "(J)J", static_cast<jint>(n));
    return static_cast<int>(result);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
