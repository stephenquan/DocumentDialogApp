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

AndroidObject::AndroidObject(QAndroidJniEnvironment& env, const char* jclass, QAndroidJniObject obj) :
    QAndroidJniObject(obj),
    m_Env(env),
    m_jclass(jclass)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

AndroidObject::AndroidObject(AndroidObject& other) :
    QAndroidJniObject(other),
    m_Env(other.m_Env),
    m_jclass(other.m_jclass)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

AndroidObject::AndroidObject(AndroidObject&& other) :
    QAndroidJniObject(other),
    m_Env(other.m_Env),
    m_jclass(other.m_jclass)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

AndroidObject::~AndroidObject()
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString AndroidObject::staticString(const QString& name) const
{
    return staticString(m_Env, jclass(), name);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString AndroidObject::staticString(QAndroidJniEnvironment& env, const QString& jclass, const QString& name)
{
    JniExceptionCheck check(env);
    return QAndroidJniObject::getStaticObjectField<jstring>( jclass.toUtf8().data(), name.toUtf8().data() ).toString();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
