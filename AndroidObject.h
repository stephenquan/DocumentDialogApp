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

class AndroidObject : public QObject
{
    Q_OBJECT

public:
    AndroidObject(QAndroidJniEnvironment& env, QObject* parent = nullptr);

    virtual const char* jclass() const = 0;
    QString staticString(const QString& name) const;
    static QString staticString(const QString& jclass, const QString& name, QAndroidJniEnvironment& env);

protected:
    QAndroidJniEnvironment& m_Env;

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
