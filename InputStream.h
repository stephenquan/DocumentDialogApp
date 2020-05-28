//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __InputStream__
#define __InputStream__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include <QObject>
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class InputStream : public QObject
{
    Q_OBJECT

public:
    InputStream(QAndroidJniEnvironment& env, QObject* parent = nullptr, QAndroidJniObject inputStream = QAndroidJniObject());
    InputStream(InputStream&& other);
    ~InputStream();

    int available();
    void close();
    QByteArray read(int n);
    void reset();
    qint64 skip(qint64 n);
    bool isValid() { return m_InputStream.isValid(); }

protected:
    QAndroidJniEnvironment& m_Env;
    QAndroidJniObject m_InputStream;

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
