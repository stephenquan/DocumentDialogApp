import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import StephenQuan 1.0

Page {
    id: fileInfoPage

    property var url

    onUrlChanged: refresh()

    ListView {
        id: listView

        anchors.fill: parent
        anchors.margins: 10

        model: listModel
        clip: true

        delegate: Frame {
            width: listView.width

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

    FileInfo {
        id: fileInfo

        url: fileInfoPage.url
    }

    ListModel {
        id: listModel

        function appendInfo( infoLabel, infoValue, folderPath ) {
            append( { infoLabel : infoLabel, infoValue: JSON.stringify( infoValue, undefined, 2 ), folderPath: folderPath || "" } );
        }
    }

    function refresh() {
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
    }

    Component.onCompleted: {
        Qt.callLater( refresh );
    }

}
