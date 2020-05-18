#include "DocumentDialogPrivateAndroid.h"
#include <QtAndroid>
#include <QAndroidJniEnvironment>
#include <QDebug>
#include "JniExceptionCheck.h"

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
    qCInfo(documentDialog, "ACTION_OPEN_DOCUMENT = %s", ACTION_OPEN_DOCUMENT.toString().toUtf8().constData());

    QAndroidJniObject ACTION_OPEN_DOCUMENT_TREE = QAndroidJniObject::getStaticObjectField("android/content/Intent", "ACTION_OPEN_DOCUMENT_TREE", "Ljava/lang/String;");
    qCInfo(documentDialog, "ACTION_OPEN_DOCUMENT_TREE = %s", ACTION_OPEN_DOCUMENT_TREE.toString().toUtf8().constData());

    QAndroidJniObject CATEGORY_OPENABLE = QAndroidJniObject::getStaticObjectField("android/content/Intent", "CATEGORY_OPENABLE", "Ljava/lang/String;");
    qCInfo(documentDialog, "CATEGORY_OPENABLE = %s", CATEGORY_OPENABLE.toString().toUtf8().constData());

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
{
    QAndroidJniEnvironment env;
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

    QUrl fileUrl = uri.toString();
    qCInfo(documentDialog, "fileUrl = %s", fileUrl.toString().toUtf8().constData());

    jint flags = data.callMethod<jint>("getFlags", "()I");
    qCInfo(documentDialog, "flags (before) = %d", flags);

    flags &= (FLAG_GRANT_READ_URI_PERMISSION | FLAG_GRANT_WRITE_URI_PERMISSION);
    //qDebug() << Q_FUNC_INFO << "flags: " << flags;
    qCInfo(documentDialog, "flags (after) = %d", flags);

    QAndroidJniObject contentResolver = QtAndroid::androidActivity().callObjectMethod("getContentResolver","()Landroid/content/ContentResolver;");
    contentResolver.callMethod<void>("takePersistableUriPermission","(Landroid/net/Uri;I)V", uri.object<jobject>(), flags);
    qCInfo(documentDialog, "contentResolver.isValid = %d", contentResolver.isValid());

    //setFileUrl(fileUrl);
    setFileUrl(uri.toString());

    emit accepted();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
