QT += quick
QT += svg
QT += multimedia

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AppFramework.cpp \
    DocumentDialog.cpp \
    DocumentDialogPrivate.cpp \
    EnumInfo.cpp \
    FileFolder.cpp \
    FileFolderPrivate.cpp \
    FileInfo.cpp \
    FileInfoPrivate.cpp \
    main.cpp

HEADERS += \
    AppFramework.h \
    DocumentDialog.h \
    DocumentDialogPrivate.h \
    EnumInfo.h \
    FileFolder.h \
    FileFolderPrivate.h \
    FileInfo.h \
    FileInfoPrivate.h

android: {
    QT += androidextras

    SOURCES += \
        AndroidObject.cpp \
        ContentResolver.cpp \
        ContentUris.cpp \
        DocumentDialogPrivateAndroid.cpp \
        DocumentFile.cpp \
        DocumentsContract.cpp \
        DocumentsContractDocument.cpp \
        FileFolderPrivateAndroid.cpp \
        FileInfoPrivateAndroid.cpp \
        InputStream.cpp

    HEADERS += \
        AndroidObject.h \
        ContentResolver.h \
        ContentUris.h \
        DocumentDialogPrivateAndroid.h \
        DocumentFile.h \
        DocumentsContract.h \
        DocumentsContractDocument.h \
        FileFolderPrivateAndroid.h \
        FileInfoPrivateAndroid.h \
        InputStream.h \
        JniExceptionCheck.h

}

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android

    OTHER_FILES += $$files("*.java", "true")
}
