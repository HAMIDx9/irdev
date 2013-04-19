import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    initialPage: mainPage

    MainPage {
        id: mainPage
    }

    ToolBarLayout {
        id: commonTools
        visible: true
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: (myMenu.status === DialogStatus.Closed) ? myMenu.open() : myMenu.close()
        }
    }

    Menu {
        id: myMenu
        visualParent: pageStack
        MenuLayout {
            MenuItem { text: qsTr("About") ; onClicked: aboutDialog.open() }
            MenuItem { text: qsTr("Exit") ; onClicked:  Qt.quit()}
        }
    }
    QueryDialog {
        id: aboutDialog
        titleText: "About"
        message: "This Program in under GPLv2 license or later.\n\n"
                 + "Wrriten By Hamid Zamani (aka HAMIDx9)\n"
                 + "http://www.hamidx9.ir\nhamidx9@linuxmail.org"
        acceptButtonText: "Ok"

    }
}
