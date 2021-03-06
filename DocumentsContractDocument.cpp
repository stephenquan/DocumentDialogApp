//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "DocumentsContractDocument.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

const char* DocumentsContractDocument::JCLASS = "android/provider/DocumentsContract$Document";

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentsContractDocument::DocumentsContractDocument(QAndroidJniEnvironment& env, QAndroidJniObject obj) :
    AndroidObject(env, DocumentsContractDocument::JCLASS, obj)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
