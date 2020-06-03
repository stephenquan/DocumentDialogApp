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
    property var mediaPlayerUrl

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
                visible: mediaPlayerUrl

                Layout.fillWidth: true

                ColumnLayout {
                    width: parent.width

                    Text {
                        text: qsTr("MediaPlayer")
                        font.pointSize: 12
                        font.bold: true
                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.preferredHeight: width / 2

                        MediaPlayer {
                            id: mediaPlayer

                            source: mediaPlayerUrl ? mediaPlayerUrl : ""
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            text: qsTr("%1 (Status: %2)")
                            .arg(mediaPlayerStatus.stringify(mediaPlayer.status) || "NULL")
                            .arg(mediaPlayer.status)
                            font.pointSize: 10
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        Text {
                            text: qsTr("%1/%2")
                            .arg(Math.floor(mediaPlayer.position / 1000))
                            .arg(Math.floor(mediaPlayer.duration / 1000))
                            font.pointSize: 10
                        }
                    }

                    Flow {
                        Layout.fillWidth: true

                        spacing: 10

                        Button {
                            text: qsTr("Show")
                            font.pointSize: 12

                            onClicked: mediaPlayerUrl = url
                        }

                        Button {
                            text: qsTr("Rewind")
                            font.pointSize: 12

                            onClicked: mediaPlayer.seek(0)
                        }

                        Button {
                            text: qsTr("Play")
                            font.pointSize: 12

                            onClicked: mediaPlayer.play()
                        }

                        Button {
                            text: qsTr("Pause")
                            font.pointSize: 12

                            onClicked: mediaPlayer.pause()
                        }

                        Button {
                            text: qsTr("Stop")
                            font.pointSize: 12

                            onClicked: mediaPlayer.stop()
                        }

                        Button {
                            text: qsTr("Fix")
                            font.pointSize: 12

                            onClicked: {
                                let fileInfo = AppFramework.fileInfo(url);
                                let bytes = fileInfo.readAll();
                                let base64 = AppFramework.btoa(bytes);
                                mediaPlayerUrl = "data:" + fileInfo.type + ";base64," + base64;
                                console.log(mediaPlayerUrl);
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
        imageUrl = null;
        mediaPlayerUrl = null;

        listModel.clear();
        if (!url) {
            return;
        }

        listModel.appendInfo( "url", url );
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
            mediaPlayerUrl = url;
        }

        if (fileInfo.type.match(/^audio\//)) {
            mediaPlayerUrl = url;
        }
    }

    EnumInfo {
        id: mediaPlayerStatus

        context: mediaPlayer
        name: "Status"

    }

    Component.onCompleted: {
        Qt.callLater( refresh );
        console.log(JSON.stringify(mediaPlayerStatus.availableNames));
    }

}
