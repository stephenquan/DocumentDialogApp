import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.12
import StephenQuan 1.0

Page {
    id: fileInfoPage

    property var url
    property var imageUrl
    property var videoUrl
    property var audioUrl

    onUrlChanged: refresh()

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

            Repeater {
                model: listModel

                Frame {
                    Layout.fillWidth: true

                    ColumnLayout {
                        width: parent.width

                        Text {
                            Layout.fillWidth: true

                            text: infoLabel
                            font.pointSize: 12
                            font.bold: true
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        }

                        RowLayout {
                            Layout.fillWidth: true

                            Text {
                                Layout.fillWidth: true

                                text: infoValue
                                font.pointSize: 12
                                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            }

                            Item {
                                Layout.preferredWidth: 32
                                Layout.preferredHeight: 32

                                visible: folderPath !== ""

                                Image {
                                    id: folderImage
                                    anchors.fill: parent
                                    source: "Images/folder-32.svg"
                                }

                                ColorOverlay {
                                    anchors.fill: folderImage
                                    source: folderImage
                                    color: "black"
                                }

                                MouseArea {
                                    anchors.fill: parent

                                    onClicked: openFileFolderPage(folderPath)
                                }
                            }

                        }
                    }
                }
            }

            Frame {
                visible: imageUrl

                Layout.fillWidth: true

                ColumnLayout {
                    width: parent.width

                    Text {
                        text: qsTr("Image")
                        font.pointSize: 12
                        font.bold: true
                    }

                    Image {
                        id: image

                        Layout.fillWidth: true
                        Layout.preferredHeight: width / 2

                        source: imageUrl ? imageUrl : ""
                        fillMode: Image.PreserveAspectFit
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Button {
                            text: qsTr("Show")
                            font.pointSize: 12

                            onClicked: imageUrl = url
                        }

                        Button {
                            text: qsTr("Fix")
                            font.pointSize: 12

                            onClicked: {
                                let fileInfo = AppFramework.fileInfo(url);
                                let bytes = fileInfo.readAll();
                                let base64 = AppFramework.btoa(bytes);
                                imageUrl = "data:" + fileInfo.type + ";base64," + base64;
                            }
                        }
                    }
                }
            }

            Frame {
                visible: videoUrl

                Layout.fillWidth: true

                ColumnLayout {
                    width: parent.width

                    Text {
                        text: qsTr("video")
                        font.pointSize: 12
                        font.bold: true
                    }

                    Video {
                        id: video

                        Layout.fillWidth: true
                        Layout.preferredHeight: width / 2

                        source: videoUrl ? videoUrl : ""
                    }

                    Flow {
                        Layout.fillWidth: true

                        spacing: 10

                        Button {
                            text: qsTr("Show")
                            font.pointSize: 12

                            onClicked: videoUrl = url
                        }

                        Button {
                            text: qsTr("Rewind")
                            font.pointSize: 12

                            onClicked: video.seek(0)
                        }

                        Button {
                            text: qsTr("Play")
                            font.pointSize: 12

                            onClicked: video.play()
                        }

                        Button {
                            text: qsTr("Pause")
                            font.pointSize: 12

                            onClicked: video.pause()
                        }

                        Button {
                            text: qsTr("Stop")
                            font.pointSize: 12

                            onClicked: video.stop()
                        }

                        Button {
                            text: qsTr("Fix")
                            font.pointSize: 12

                            onClicked: {
                                let fileInfo = AppFramework.fileInfo(url);
                                let bytes = fileInfo.readAll();
                                let base64 = AppFramework.btoa(bytes);
                                videoUrl = "data:" + fileInfo.type + ";base64," + base64;
                            }
                        }
                    }
                }
            }

            Frame {
                visible: audioUrl

                Layout.fillWidth: true

                ColumnLayout {
                    width: parent.width

                    Text {
                        text: qsTr("audio")
                        font.pointSize: 12
                        font.bold: true
                    }

                    Audio {
                        id: audio

                        Layout.fillWidth: true
                        Layout.preferredHeight: width / 2

                        source: audioUrl ? audioUrl : ""
                    }

                    Flow {
                        Layout.fillWidth: true

                        spacing: 10

                        Button {
                            text: qsTr("Show")
                            font.pointSize: 12

                            onClicked: audioUrl = url
                        }

                        Button {
                            text: qsTr("Rewind")
                            font.pointSize: 12

                            onClicked: audio.seek(0)
                        }

                        Button {
                            text: qsTr("Play")
                            font.pointSize: 12

                            onClicked: audio.play()
                        }

                        Button {
                            text: qsTr("Pause")
                            font.pointSize: 12

                            onClicked: audio.pause()
                        }

                        Button {
                            text: qsTr("Stop")
                            font.pointSize: 12

                            onClicked: audio.stop()
                        }

                        Button {
                            text: qsTr("Fix")
                            font.pointSize: 12

                            onClicked: {
                                let fileInfo = AppFramework.fileInfo(url);
                                let bytes = fileInfo.readAll();
                                let base64 = AppFramework.btoa(bytes);
                                audioUrl = "data:" + fileInfo.type + ";base64," + base64;
                            }
                        }
                    }
                }
            }

        }

    }

    FileInfo {
        id: fileInfo

        url: fileInfoPage.url
    }

    ListModel {
        id: listModel

        function appendInfo( infoLabel, infoValue, folderPath ) {
            append( {
                       infoLabel : infoLabel,
                       infoValue: JSON.stringify( infoValue, undefined, 2 ),
                       folderPath: folderPath || ""
                   } );
        }
    }

    function refresh() {
        imageUrl = "";
        videoUrl = "";
        audioUrl = "";

        listModel.clear();
        listModel.appendInfo( "url", fileInfoPage.url );
        if (fileInfo.folder) {
            listModel.appendInfo( "folder.path", fileInfo.folder.path, fileInfo.folder.path );
        }
        listModel.appendInfo( "exists", fileInfo.exists );
        listModel.appendInfo( "isFile", fileInfo.isFile );
        listModel.appendInfo( "isDir", fileInfo.isDir );
        listModel.appendInfo( "displayName", fileInfo.displayName );
        listModel.appendInfo( "fileName", fileInfo.fileName );
        listModel.appendInfo( "filePath", fileInfo.filePath );
        listModel.appendInfo( "size", fileInfo.size );
        listModel.appendInfo( "type", fileInfo.type );
        listModel.appendInfo( "extra", fileInfo.extra );

        if (fileInfo.type.match(/^image\//)) {
            imageUrl = url;
        }

        if (fileInfo.type.match(/^video\//)) {
            videoUrl = url;
        }

        if (fileInfo.type.match(/^audio\//)) {
            audioUrl = url;
        }
    }

    Component.onCompleted: {
        Qt.callLater( refresh );
    }

}
