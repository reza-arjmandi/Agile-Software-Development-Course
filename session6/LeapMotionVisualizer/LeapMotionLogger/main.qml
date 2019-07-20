import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtDataVisualization 1.3

import Viewer3D.DataModel 1.0
import LeapMotion.DataAcquisitor 1.0

Window {
    visible: true
    visibility: "Maximized"

    title: qsTr("Leap Motion Logger")

    ColumnLayout{
        spacing: 20
        anchors.fill: parent

        RowLayout{
            spacing: 20
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter

            Button{
                id: start
                text: "start"

                onClicked:  LeapMotionDataAcquisitor.Run();
            }

            Button{
                id: stop
                text: "stop"

                onClicked:  LeapMotionDataAcquisitor.Stop();
            }
        }

        Scatter3D {
            Layout.fillWidth: true
            Layout.fillHeight: true
            axisX: ValueAxis3D{
                min: -350
                max: 350
            }

            axisY: ValueAxis3D{
                min: 0
                max: 700
            }

            axisZ: ValueAxis3D{
                min: -200
                max: 350
            }
            Scatter3DSeries {
                itemLabelFormat: "Pop density at (@xLabel N, @zLabel E): @yLabel"
                ItemModelScatterDataProxy  {
                    itemModel: Viewer3DDataModel
                    // Mapping model roles to surface series rows, columns, and values.
                    xPosRole: "X"
                    yPosRole: "Y"
                    zPosRole: "Z"
                }
            }
        }
    }
}
