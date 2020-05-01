#ifndef __JniEnvironment__
#define __JniEnvironment__

#include <QAndroidJniEnvironment>

class JniEnvironment : public QAndroidJniEnvironment
{
public:
    ~JniEnvironment()
    {
        _JNIEnv* env = operator _JNIEnv *();
        if (env->ExceptionCheck())
        {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
    }
};

#endif
