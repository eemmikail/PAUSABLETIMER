import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 300
    height: 100
    visible: true
    title: qsTr("Scheduler")

    Button {
        id: btn_startTimer
        width: 100
        height: 50
        anchors.top: parent.top
        anchors.left: parent.left
        text: "START"
        onClicked: {
            rec_status.state = "running";
            SchedulerTimer.start()
        }
    }

    Button {
        id: btn_stopTimer
        width: 100
        height: 50
        anchors.top: parent.top
        anchors.right: parent.right
        text: "STOP"
        onClicked: {
            rec_status.state = "stopped";
            SchedulerTimer.stop()
        }
    }

    Button {
        id: btn_pauseTimer
        width: 100
        height: 50
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: "PAUSE"
        onClicked: {
            rec_status.state = "paused";
            SchedulerTimer.pause()
        }
    }

    Button {
        id: btn_resumeTimer
        width: 100
        height: 50
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: "RESUME"
        visible: SchedulerTimer.state === 1
        onClicked: {
            rec_status.state = "running";
            SchedulerTimer.resume()
        }
    }

    ProgressBar {
        id: pb_timeBar
        anchors.top: btn_startTimer.bottom
        anchors.left: parent.left
        value: SchedulerTimer.elapsedMS
        from: 0
        to: SchedulerTimer.targetMS
        width: 300
        height: 25
    }

    Text {
        id: lbl_setTime
        width: 75
        height: 25
        text: "Time(ms)"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Rectangle {
        width: 225
        height: 25
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        color: "gray";
        TextInput {
            id: ti_setTime
            anchors.fill: parent
            color: "white"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            validator: RegExpValidator{regExp: /^[0-9/]+$/}
            text: "10000"
            onTextChanged: {
                SchedulerTimer.setTargetTime(text)
            }
        }
        Rectangle {
            id: rec_status
            width: 10
            height: 10
            radius: width/2
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            state: "stopped"
            states: [
                State {
                    name: "stopped"
                    PropertyChanges {
                        target: rec_status
                        color: "red"
                    }
                },
                State {
                    name: "running"
                    PropertyChanges {
                        target: rec_status
                        color: "green"
                    }
                },
                State {
                    name: "paused"
                    PropertyChanges {
                        target: rec_status
                        color: "purple"
                    }
                }
            ]
        }
    }
    Connections {
        target: SchedulerTimer
        function onCurrentStateChanged(state) {
            if(state === 0) {
                rec_status.state = "running";
            }else if(state === 1) {
                rec_status.state = "paused";
            }else {
                rec_status.state = "stopped";
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
