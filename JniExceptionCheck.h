#ifndef __JniExceptionCheck__
#define __JniExceptionCheck__

#include <QAndroidJniEnvironment>

class JniExceptionCheck
{
public:
    JniExceptionCheck(QAndroidJniEnvironment& env) :
        m_Env(env)
    {
    }

    ~JniExceptionCheck()
    {
        if (m_Env->ExceptionCheck())
        {
            m_Env->ExceptionDescribe();
            m_Env->ExceptionClear();
        }
    }

protected:
    QAndroidJniEnvironment& m_Env;

};

#endif
