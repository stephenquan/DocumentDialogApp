import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import StephenQuan 1.0

Window {
    id: app

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property bool verboseFileInfo: false

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
                            text: qsTr("url: %1").arg(JSON.stringify(fileInfo.url))
                            font.pointSize: 10
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("extra: %1").arg(fileInfo.url ? JSON.stringify(fileInfo.extra, undefined, 2) : null)
                            font.pointSize: 10
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

    function openFileDialog()
    {
        image.source = "";
        results.clear();
        results.log("fileDialog.open");
        fileDialog.open();
    }

    function openDocumentDialog()
    {
        image.source = "";
        results.clear();
        results.log("documentDialog.open");
        documentDialog.open();
    }

    function notifyAccepted(fileUrl)
    {
        results.log("notifyAccepted", fileUrl);
        fileInfo.url = fileUrl;
        image.source = fileUrl;
        /*
        results.log("fileInfo.absoluteFilePath: ", fileInfo.absoluteFilePath);
        results.log("fileInfo.absolutePath: ", fileInfo.absolutePath);
        results.log("fileInfo.exists: ", fileInfo.exists);
        results.log("fileInfo.size: ", fileInfo.size);
        results.log("fileInfo.fileName: ", fileInfo.fileName);
        results.log("fileInfo.filePath: ", fileInfo.filePath);
        */
        results.log("fileInfo.url: ", fileInfo.url);
    }

    function notifyRejected()
    {
        results.log("notifyRejected");
    }

}
