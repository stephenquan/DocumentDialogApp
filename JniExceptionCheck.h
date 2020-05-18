#ifndef __JniExceptionCheck__
#define __JniExceptionCheck__

#include <QAndroidJniEnvironment>
#include <QDebug>

class JniExceptionCheck
{
public:
    JniExceptionCheck(QAndroidJniEnvironment& env) :
        m_Env(env)
    {
    }

    ~JniExceptionCheck()
    {
        qDebug() << Q_FUNC_INFO << __LINE__;
        if (m_Env->ExceptionCheck())
        {
            qDebug() << Q_FUNC_INFO << __LINE__;
            m_Env->ExceptionDescribe();
            m_Env->ExceptionClear();
        }
        qDebug() << Q_FUNC_INFO << __LINE__;
    }

protected:
    QAndroidJniEnvironment& m_Env;

};

#endif
