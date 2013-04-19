import QtQuick 1.1
import com.nokia.meego 1.0



Page {
    tools: commonTools


    TextField {
        id: textfield1
        x: 127
        y: 234
    }

    TextField {
        id: textfield2
        x: 127
        y: 336
    }

    Label {
        id: label1
        x: 41
        y: 240
        text: "IP :"
    }

    Label {
        id: label2
        x: 41
        y: 342
        text: "Port :"
    }

    Label {
        id: label3
        x: 49
        y: 119
        text: "Developer Enabler for IRANIAN Users\n"
              + "      By Hamid Zamani (aka HAMIDx9)\n"

    }
    QueryDialog {

        id: successDialog
        titleText: "Success"
        message: "Process was done successfully!\n"
                 + "Try this command 'pkgmgr refresh-cache' if you have terminal\n"
                 + "Or try to install developer-mode package from gui\n"
                 + "Good LuCk...\n"
        acceptButtonText: "OK!"
        onAccepted: Qt.quit()
    }
    Label {
        id: label4
        x: 41
        y: 441
        text: "Proxy:"

    }
    QueryDialog {

        id: disSuccessDialog
        titleText: "Success"
        message: "Proxy was disabled successfully!\n"
        acceptButtonText: "OK!"

    }

    QueryDialog {

        id: failedisSuccessDialog
        titleText: "Error"
        message: "There is a problem in the process!\n"
        acceptButtonText: "OK!"
    }

    Label {
        id: label5
        x: 182
        y: 444
        width: 300
        height: 48
        text: pirdev.get()


    }

    Column {
        x: 80
        y: 551

        Button{
            anchors {
                horizontalCenter: parent.horizontalCenter

            }
            text: qsTr("Start")
            anchors.horizontalCenterOffset: 0
            onClicked: if (textfield1.text != "" && textfield2.text != "") {pirdev.start(textfield1.text,textfield2.text) ; successDialog.open()} }

        Button{
            y: 50
            text: qsTr("Remove")
            onClicked: { pirdev.del(); disSuccessDialog.open() }


        }
    }

    Label {
        id: label6
        x: 139
        y: 40
        text: "IN THE NAME OF GOD"
        font.strikeout: false
        font.underline: true
        font.italic: true
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
    }


}
