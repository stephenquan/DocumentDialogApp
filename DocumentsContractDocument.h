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
    Q_OBJECT

public:
    DocumentsContractDocument(QAndroidJniEnvironment& env, QObject* parent = nullptr) :
        AndroidObject(env, parent)
    {
    }

    const char* jclass() const Q_DECL_OVERRIDE { return "android/provider/DocumentsContract$Document"; }

    QString COLUMN_DISPLAY_NAME() const { return staticString("COLUMN_DISPLAY_NAME"); }
    QString COLUMN_DOCUMENT_ID() const { return staticString("COLUMN_DOCUMENT_ID"); }
    QString COLUMN_FLAGS() const { return staticString("COLUMN_FLAGS"); }
    QString COLUMN_MIME_TYPE() const { return staticString("COLUMN_MIME_TYPE"); }
    QString COLUMN_LAST_MODIFIED() const { return staticString("COLUMN_LAST_MODIFIED"); }
    QString COLUMN_SIZE() const { return staticString("COLUMN_SIZE"); }
    QString MIME_TYPE_DIR() const { return staticString("MIME_TYPE_DIR"); }

};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#endif

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
