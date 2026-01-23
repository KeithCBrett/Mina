import QtQuick
import QtQuick.Shapes


Item {
	id: root
	width: 150
	height: root.width
	anchors.left: parent.left
	anchors.top: parent.top
	Shape {
		id: outercircle
		anchors.fill: parent
		anchors.centerIn: parent
		ShapePath {
			id: outerpath
			strokeWidth: 0
			fillGradient: ConicalGradient {
				centerX: outercircle.width / 2
				centerY: outercircle.height / 2
				GradientStop { position: 0; color: "#ff0000" }
				GradientStop { position: 0.165; color: "#ffff00" }
				GradientStop { position: 0.33; color: "#00ff00" }
				GradientStop { position: 0.495; color: "#00ffff" }
				GradientStop { position: 0.66; color: "#0000ff" }
				GradientStop { position: 0.825; color: "#ff00ff" }
				GradientStop { position: 1; color: "#ff0000" }
			}

			readonly property real r: root.width / 2
			PathAngleArc {
				centerX: outercircle.width / 2
				centerY: outercircle.height / 2
				radiusX: outerpath.r
				radiusY: outerpath.r
				sweepAngle: 360
			}
			readonly property real r2: r - (r * 0.10)
			PathAngleArc {
				centerX: outercircle.width / 2
				centerY: outercircle.height / 2
				radiusX: outerpath.r2
				radiusY: outerpath.r2
				sweepAngle: 360
			}
		}
	}
}
