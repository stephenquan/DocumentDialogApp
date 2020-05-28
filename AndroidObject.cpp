//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "AndroidObject.h"
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QtAndroid>
#include "JniExceptionCheck.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

AndroidObject::AndroidObject(QAndroidJniEnvironment& env, QObject* parent) :
    QObject(parent),
    m_Env(env)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString AndroidObject::staticString(const QString& name) const
{
    return staticString(jclass(), name, m_Env);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString AndroidObject::staticString(const QString& jclass, const QString& name, QAndroidJniEnvironment& env)
{
    JniExceptionCheck check(env);
    return QAndroidJniObject::getStaticObjectField<jstring>( jclass.toUtf8().data(), name.toUtf8().data() ).toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
