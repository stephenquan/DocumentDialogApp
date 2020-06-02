//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "DocumentDialogPrivateAndroid.h"
#include <QtAndroid>
#include <QAndroidJniEnvironment>
#include "JniExceptionCheck.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#define DOCUMENT_DIALOG_REQUEST_CODE 12

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

DocumentDialogPrivateAndroid::DocumentDialogPrivateAndroid(QObject* parent) :
    DocumentDialogPrivate(parent)
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void DocumentDialogPrivateAndroid::open()
{
    QAndroidJniEnvironment env;
    JniExceptionCheck check(env);

    QAndroidJniObject ACTION_OPEN_DOCUMENT = QAndroidJniObject::getStaticObjectField("android/content/Intent", "ACTION_OPEN_DOCUMENT", "Ljava/lang/String;");

    QAndroidJniObject ACTION_OPEN_DOCUMENT_TREE = QAndroidJniObject::getStaticObjectField("android/content/Intent", "ACTION_OPEN_DOCUMENT_TREE", "Ljava/lang/String;");

    QAndroidJniObject CATEGORY_OPENABLE = QAndroidJniObject::getStaticObjectField("android/content/Intent", "CATEGORY_OPENABLE", "Ljava/lang/String;");

    QAndroidJniObject intent = QAndroidJniObject("android/content/Intent");
    if (selectFolder())
    {
        intent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", ACTION_OPEN_DOCUMENT_TREE.object<jstring>());
    }
    else
    {
        QAndroidJniObject mimeType = QAndroidJniObject::fromString(QStringLiteral( "*/*"));
        intent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", ACTION_OPEN_DOCUMENT.object<jstring>());
        intent.callObjectMethod("addCategory", "(Ljava/lang/String;)Landroid/content/Intent;", CATEGORY_OPENABLE.object<jstring>());
        intent.callObjectMethod("setType", "(Ljava/lang/String;)Landroid/content/Intent;", mimeType.object<jstring>());
    }
    QtAndroid::startActivity(intent.object<jobject>(), DOCUMENT_DIALOG_REQUEST_CODE, this);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void DocumentDialogPrivateAndroid::handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data)
{ QAndroidJniEnvironment env;
    JniExceptionCheck check(env);

    qCInfo(documentDialog, "receiverRequestCode: %d resultCode: %d", receiverRequestCode, resultCode);

    jint RESULT_OK = QAndroidJniObject::getStaticField<jint>("android/app/Activity", "RESULT_OK");
    //jint RESULT_CANCELED = QAndroidJniObject::getStaticField<jint>("android/app/Activity", "RESULT_CANCELED");

    jint FLAG_GRANT_READ_URI_PERMISSION = QAndroidJniObject::getStaticField<jint>("android.content.Intent", "FLAG_GRANT_READ_URI_PERMISSION");
    jint FLAG_GRANT_WRITE_URI_PERMISSION = QAndroidJniObject::getStaticField<jint>("android.content.Intent", "FLAG_GRANT_WRITE_URI_PERMISSION");
    jint FLAG_GRANT_PERSISTABLE_URI_PERMISSION = QAndroidJniObject::getStaticField<jint>("android.content.Intent", "FLAG_GRANT_PERSISTABLE_URI_PERMISSION");

    if (receiverRequestCode != DOCUMENT_DIALOG_REQUEST_CODE)
    {
        emit rejected();
        return;
    }

    if (resultCode != RESULT_OK)
    {
        emit rejected();
        return;
    }

    QAndroidJniObject uri = data.callObjectMethod("getData", "()Landroid/net/Uri;" );
    qCInfo(documentDialog, "uri = %s", uri.toString().toUtf8().constData());

    //setFileUrl(fileUrl);
    setFileUrl(uri.toString());

    emit accepted();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
