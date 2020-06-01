import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import StephenQuan 1.0

Page {
    id: fileFolderPage

    property var url

    header: Frame {
        RowLayout {
            width: parent.width

            Item {
                Layout.preferredWidth: 32
                Layout.preferredHeight: 32

                Image {
                    anchors.fill: parent

                    source: "Images/folder-32.svg"
                }
            }

            Text {
                Layout.fillWidth: true

                text: url
                font.pointSize: 12
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
        }
    }

    ListView {
        id: listView

        anchors.fill: parent
        anchors.margins: 10

        model: listModel
        clip: true

        delegate: Item {
            width: listView.width
            height: rowLayout.height

            RowLayout {
                id: rowLayout

                width: parent.width

                Image {
                    Layout.preferredWidth: 32
                    Layout.preferredHeight: 32

                    source: iconSource
                }

                Text {
                    Layout.fillWidth: true
                    text: displayName
                    font.pointSize: 12
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    if (linkFolderUrl !== "") {
                        openFileFolderPage(linkFolderUrl);
                        return;
                    }

                    if (linkFileUrl !== "") {
                        openFileInfoPage(linkFileUrl);
                        return;
                    }
                }
            }
        }
    }

    ListModel {
        id: listModel
    }

    FileFolder {
        id: fileFolder
        url: fileFolderPage.url
    }

    Component.onCompleted: {

        for (let folderName of fileFolder.folderNames()) {
            let fileUrl = fileFolder.fileUrl(folderName);
            let fileInfo = AppFramework.fileInfo(fileUrl);
            let displayName = fileInfo.displayName;
            listModel.append( {
                                 type: "FOLDER",
                                 iconSource: "Images/folder-32.svg",
                                 folderName: folderName,
                                 fileName: "",
                                 displayName: displayName,
                                 fileUrl: fileUrl,
                                 linkFolderUrl: fileUrl,
                                 linkFileUrl: ""
                             } );
        }

        for (let fileName of fileFolder.fileNames()) {
            let fileUrl = fileFolder.fileUrl(fileName);
            let fileInfo = AppFramework.fileInfo(fileUrl);
            let displayName = fileInfo.displayName;
            listModel.append( {
                                 type: "FILE",
                                 iconSource: "Images/file-32.svg",
                                 folderName: "",
                                 fileName: fileName,
                                 displayName: displayName,
                                 fileUrl: fileUrl,
                                 linkFolderUrl: "",
                                 linkFileUrl: fileUrl
                             } );
        }

    }
}
