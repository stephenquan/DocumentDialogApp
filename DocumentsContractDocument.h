//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#ifndef __DocumentsContractDocument__
#define __DocumentsContractDocument__

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "AndroidObject.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class DocumentsContractDocument : public AndroidObject
{
public:
    DocumentsContractDocument(QAndroidJniEnvironment& env, QAndroidJniObject obj = QAndroidJniObject());

    static const char* JCLASS;

    QString COLUMN_DISPLAY_NAME() const { return COLUMN_DISPLAY_NAME(m_Env); }
    QString COLUMN_DOCUMENT_ID() const { return COLUMN_DOCUMENT_ID(m_Env); }
    QString COLUMN_FLAGS() const { return COLUMN_FLAGS(m_Env); }
    QString COLUMN_MIME_TYPE() const { return COLUMN_MIME_TYPE(m_Env); }
    QString COLUMN_LAST_MODIFIED() const { return COLUMN_LAST_MODIFIED(m_Env); }
    QString COLUMN_SIZE() const { return COLUMN_SIZE(m_Env); }
    QString MIME_TYPE_DIR() const { return MIME_TYPE_DIR(m_Env); }

    static QString COLUMN_DISPLAY_NAME(QAndroidJniEnvironment& env) { return staticString(env, JCLASS, "COLUMN_DISPLAY_NAME"); }
    static QString COLUMN_DOCUMENT_ID(QAndroidJniEnvironment& env) { return staticString(env, JCLASS, "COLUMN_DOCUMENT_ID"); }
    static QString COLUMN_FLAGS(QAndroidJniEnvironment& env) { return staticString(env, JCLASS, "COLUMN_FLAGS"); }
    static QString COLUMN_MIME_TYPE(QAndroidJniEnvironment& env) { return staticString(env, JCLASS, "COLUMN_MIME_TYPE"); }
    static QString COLUMN_LAST_MODIFIED(QAndroidJniEnvironment& env) { return staticString(env, JCLASS, "COLUMN_LAST_MODIFIED"); }
    static QString COLUMN_SIZE(QAndroidJniEnvironment& env) { return staticString(env, JCLASS, "COLUMN_SIZE"); }
    static QString MIME_TYPE_DIR(QAndroidJniEnvironment& env) { return staticString(env, JCLASS, "MIME_TYPE_DIR"); }

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
