import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.12
import StephenQuan 1.0

Window {
    id: app

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property bool verboseFileInfo: false
    property var fileNames: ""
    property var folderNames: ""

    Page {
        anchors.fill: parent

        header: Frame {
            background: Rectangle {
                color: "blue"
            }

            RowLayout {
                width: parent.width

                Item {
                    Layout.preferredWidth: 32
                    Layout.preferredHeight: 32

                    Image {
                        id: leftImage
                        anchors.fill: parent
                        source: "Images/chevron-left-32.svg"
                    }

                    ColorOverlay {
                        anchors.fill: parent
                        source: leftImage
                        color: stackView.depth > 1 ? "white" : "grey"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: stackView.pop()
                    }
                }

                Text {
                    Layout.fillWidth: true
                    text: qsTr("Document Dialog App")
                    font.pointSize: 12
                    color: "white"
                    horizontalAlignment: Qt.AlignHCenter
                }

                Item {
                    Layout.preferredWidth: 32
                    Layout.preferredHeight: 32

                    Image {
                        id: menuImage
                        anchors.fill: parent
                        source: "Images/hamburger-32.svg"
                    }

                    ColorOverlay {
                        anchors.fill: parent
                        source: menuImage
                        color: "white"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: appMenu.open()
                    }
                }

            }
        }

        StackView {
            id: stackView

            anchors.fill: parent

            initialItem: StartPage { }
        }

        Menu {
            id: appMenu
            x: parent.width - width

            MenuItem {
                text: qsTr("FileDialog")
                font.pointSize: 12
                onClicked: fileDialog.open()
            }

            MenuItem {
                text: qsTr("FileDialog (selectFolder)")
                font.pointSize: 12
                onClicked: fileDialogWithSelectFolder.open()
            }

            MenuItem {
                text: qsTr("DocumentDialog")
                font.pointSize: 12
                visible: Qt.platform.os === "android"
                onClicked: documentDialog.open()
            }

            MenuItem {
                text: qsTr("DocumentDialog (selectFolder)")
                font.pointSize: 12
                visible: Qt.platform.os === "android"
                onClicked: documentDialogWithSelectFolder.open()
            }

        }


    }

    FileDialog {
        id: fileDialog
        onAccepted: openFileInfoPage(fileUrl)
    }

    FileDialog {
        id: fileDialogWithSelectFolder
        selectFolder: true
        onAccepted: openFileFolderPage(fileUrl)
    }


    DocumentDialog {
        id: documentDialog
        onAccepted: openFileInfoPage(fileUrl)
    }

    DocumentDialog {
        id: documentDialogWithSelectFolder
        selectFolder: true
        onAccepted: openFileFolderPage(fileUrl)
    }

    Component {
        id: fileInfoPageComponent
        FileInfoPage {
        }
    }

    Component {
        id: fileFolderPageComponent
        FileFolderPage {
        }
    }

    function openFileInfoPage(url) {
        console.log("openFileInfoPage: ", url);
        stackView.push(fileInfoPageComponent, { url: url } );
    }

    function openFileFolderPage(url) {
        console.log("openFileFolderPage: ", url);
        stackView.push(fileFolderPageComponent, { url: url } );
    }

/*

    Page {
        anchors.fill: parent

        header: Frame {
            background: Rectangle {
                color: "blue"
            }

            Text {
                width: parent.width

                text: app.title
                font.pointSize: 12
                font.bold: true
                color: "white"
                horizontalAlignment: Qt.AlignHCenter
            }
        }

        Flickable {
            id: flickable

            anchors.fill: parent
            anchors.margins: 10
            contentWidth: columnLayout.width
            contentHeight: columnLayout.height
            clip: true

            ColumnLayout {
                id: columnLayout

                width: flickable.width

                spacing: 10

                Frame {
                    Layout.fillWidth: true

                    ColumnLayout {
                        width: parent.width

                        spacing: 10

                        Text {
                            text: qsTr("Menu")
                            font.pointSize: 12
                            font.bold: true
                        }

                        CheckBox {
                            id: selectFolderCheckBox

                            checked: false
                            text: qsTr("Select Folder")
                            font.pointSize: 12
                        }


                        RowLayout {
                            Layout.fillWidth: true

                            spacing: 10

                            Button {
                                text: qsTr("FileDialog")
                                font.pointSize: 12
                                onClicked: openFileDialog()
                            }

                            Button {
                                text: qsTr("DocumentDialog")
                                font.pointSize: 12
                                onClicked: openDocumentDialog()
                            }
                        }
                    }
                }

                Frame {
                    Layout.fillWidth: true

                    ColumnLayout {

                        width: parent.width

                        spacing: 10

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("FileInfo properties")
                            font.pointSize: 12
                            font.bold: true
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("url: %1").arg(JSON.stringify(fileInfo.url))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            property url urlCopy: fileInfo.url
                            property bool urlSame: (urlCopy + "") === (fileInfo.url + "")
                            Layout.fillWidth: true
                            text: qsTr("url (check): %1 (same: %2)").arg(urlCopy).arg(JSON.stringify(urlSame))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("isFile: %1").arg(JSON.stringify(fileInfo.isFile))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("isDir: %1").arg(JSON.stringify(fileInfo.isDir))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("absoluteFilePath: %1").arg(JSON.stringify(fileInfo.absoluteFilePath))
                            font.pointSize: 10
                            visible: verboseFileInfo
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("absolutePath: %1").arg(JSON.stringify(fileInfo.absolutePath))
                            font.pointSize: 10
                            visible: verboseFileInfo
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("baseName: %1").arg(JSON.stringify(fileInfo.baseName))
                            font.pointSize: 10
                            visible: verboseFileInfo
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("folder.path: %1").arg(JSON.stringify(fileInfo.folder ? fileInfo.folder.path : null))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("exists: %1").arg(JSON.stringify(fileInfo.exists))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("size: %1").arg(JSON.stringify(fileInfo.size))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("displayName: %1").arg(JSON.stringify(fileInfo.displayName))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("fileName: %1").arg(JSON.stringify(fileInfo.fileName))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("filePath: %1").arg(JSON.stringify(fileInfo.filePath))
                            font.pointSize: 10
                            visible: verboseFileInfo
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("extra: %1").arg(fileInfo.url ? JSON.stringify(fileInfo.extra, undefined, 2) : null)
                            font.pointSize: 10
                            visible: verboseFileInfo
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Button {
                            text: verboseFileInfo ? qsTr("Less") : qsTr("More")
                            font.pointSize: 12

                            onClicked: verboseFileInfo = !verboseFileInfo
                        }

                    }
                }

                Frame {
                    Layout.fillWidth: true

                    visible: fileFolder.path !== ""

                    ColumnLayout {

                        width: parent.width

                        spacing: 10

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("FileFolder properties")
                            font.pointSize: 12
                            font.bold: true
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("path: %1").arg(JSON.stringify(fileFolder.path))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("fileNames: %1").arg(JSON.stringify(fileNames))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("folderNames: %1").arg(JSON.stringify(folderNames))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                    }
                }

                Frame {
                    Layout.fillWidth: true

                    ColumnLayout {
                        width: parent.width

                        spacing: 10

                        Text {
                            text: qsTr("Image preview")
                            font.pointSize: 12
                            font.bold: true
                        }

                        Image {
                            id: image

                            Layout.fillWidth: true
                            Layout.preferredHeight: 300

                            visible: status === Image.Ready
                            source: ""
                            cache: false
                            fillMode: Image.PreserveAspectFit
                        }

                        Text {
                            text: qsTr("Status: %1").arg(["Null", "Ready", "Loading", "Error"][image.status])
                            color: ["grey", "green", "orange", "red"][image.status]
                            font.pointSize: 10
                        }

                        RowLayout {
                            Layout.fillWidth: true

                            Button {
                                text: qsTr("Hide Image")
                                font.pointSize: 10
                                onClicked: {
                                    image.source = ""
                                }
                            }

                            Button {
                                text: qsTr("Show Image")
                                font.pointSize: 10
                                onClicked: {
                                    image.source = ""
                                    image.source = fileInfo.url;
                                }
                            }

                            Button {
                                text: qsTr("Show Image using dataUri")
                                font.pointSize: 10
                                onClicked: {
                                    image.source = ""
                                    image.source = fileInfo.dataUri();
                                }
                            }
                        }

                    }
                }

                Frame {
                    Layout.fillWidth: true

                    ColumnLayout {
                        width: parent.width

                        spacing: 10

                        Text {
                            text: qsTr("Console log")
                            font.pointSize: 12
                            font.bold: true
                        }

                        TextArea {
                            id: results
                            Layout.fillWidth: true
                            width: parent.width
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            selectByMouse: true

                            function clear()
                            {
                                text = "";
                            }

                            function log(...params)
                            {
                                console.log(...params);
                                let txt = params.join(" ");
                                text += txt + "\n";
                            }
                        }
                    }
                }

            }
        }
    }

    DocumentDialog {
        id: documentDialog

        onAccepted: notifyAccepted(fileUrl);
        onRejected: notifyRejected();
        //onDebug: results.log(text)
    }

    FileDialog {
        id: fileDialog

        onAccepted: notifyAccepted(fileUrl);
        onRejected: notifyRejected();
    }

    FileInfo {
        id: fileInfo
    }

    FileFolder {
        id: fileFolder
    }

    function openFileDialog()
    {
        image.source = "";
        results.clear();
        results.log("fileDialog.open");
        fileDialog.selectFolder = selectFolderCheckBox.checked;
        fileDialog.open();
    }

    function openDocumentDialog()
    {
        image.source = "";
        results.clear();
        results.log("documentDialog.open");
        documentDialog.selectFolder = selectFolderCheckBox.checked;
        documentDialog.open();
    }

    function notifyAccepted(fileUrl)
    {
        results.log("notifyAccepted", fileUrl);
        fileInfo.url = fileUrl;
        if ((fileInfo.displayName + "").match(/.jpg$/))
        {
            image.source = fileUrl;
        }

        fileFolder.path = "";
        fileNames = "";
        folderNames = "";
        if (fileInfo.isDir)
        {
            fileFolder.url = fileUrl;
            fileNames = fileFolder.fileNames();
            folderNames = fileFolder.folderNames();
        }

        results.log("fileInfo.url: ", fileInfo.url);
    }

    function notifyRejected()
    {
        results.log("notifyRejected");
    }

*/



}
