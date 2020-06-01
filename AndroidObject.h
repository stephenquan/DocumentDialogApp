//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __AndroidObject__
#define __AndroidObject__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QObject>
#include <QVariant>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class AndroidObject : public QAndroidJniObject
{
public:
    AndroidObject(QObject* parent = nullptr);
    AndroidObject(QAndroidJniEnvironment& env, const char* jclass, QAndroidJniObject obj = QAndroidJniObject());
    AndroidObject(AndroidObject& other);
    AndroidObject(AndroidObject&& other);
    virtual ~AndroidObject();

    virtual const char* jclass() const { return m_jclass; }

    inline QAndroidJniEnvironment& env() { return m_Env; }

    QString staticString(const QString& name) const;

    static QString staticString(QAndroidJniEnvironment& env, const QString& jclass, const QString& name);

protected:
    QAndroidJniEnvironment& m_Env;
    const char* m_jclass;

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
