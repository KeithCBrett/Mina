import QtQuick
import Qt5Compat.GraphicalEffects


Item {
	id: dropdown
	width: (parent.width / 2)
	height: parent.height
	anchors.right: parent.right
	anchors.top: parent.top

	Image {
		id: cogwheel
		source: "setting.png"
		width: 30
		height: 30
		smooth: true
		visible: false
		anchors.right: parent.right
		anchors.rightMargin: 40
		anchors.top: parent.top
		anchors.topMargin: 40
		states: [
			State {
				name: "togglecogwheel"
				PropertyChanges {
					target: cogwheel;
					anchors.rightMargin: parent.width / 2
				}
				// Show buttons
				PropertyChanges {
					target: appearancebutton
					visible: true
				}
			},
			State {
				name: ""
				PropertyChanges {
					appearancebutton.state: ""
				}
				PropertyChanges {
					colorwheel.visible: true
				}
				PropertyChanges {
					appearancebutton.visible: false
				}
			}
		]
		Behavior on anchors.rightMargin {
			PropertyAnimation {
				easing.type: Easing.InOutQuad;
				duration: 200
			}
		}
	}

	// Colors setting button orange
	ColorOverlay {
		id: colorcogwheel
		anchors.fill: cogwheel
		source: cogwheel
		color: "#ffb642"
		// Whenever the cogwheel is rotated, animate it
		Behavior on rotation {
			NumberAnimation {
				from: 0
				to: 720
				duration: 300
			}
		}
		// Whenever cogwheel x changes, animate it moving
		Behavior on x {
			NumberAnimation {
				duration: 500
			}
		}
	}


	// Draw settings menu
	Rectangle {
		id: rootrectangle
		color: "#001e21"
		anchors.top: dropdown.top
		anchors.bottom: dropdown.bottom
		anchors.right: dropdown.right
		anchors.left: colorcogwheel.right
		anchors.leftMargin: 40
		border {
			color: "#ffb642"
		}
		Rectangle {
			id: appearancemenu
			width: rootrectangle.width
			height: rootrectangle.height
			anchors.left: parent.right
			color: "#001e21"
			border.color: "#ffb642"
			Text {
				text: "Foreground"
				font.family: "Iosevka NF"
				font.pointSize: 24
				anchors.top: parent.top
				anchors.left: parent.left
				anchors.topMargin: parent.width * 0.1
				anchors.leftMargin: parent.width * 0.1
				color: "#ffb642"
			}
			ColorWheel {
				id: colorwheel
				anchors.top: parent.top
				anchors.left: parent.left
				anchors.leftMargin: (rootrectangle.width
				- colorwheel.width) / 2
				anchors.topMargin: ((rootrectangle.width
				- colorwheel.width) / 2)
				+ (colorwheel.width * 0.40)
				visible: true
				width: parent.width - (parent.width * 0.2)
			}
			Text {
				id: textbackground
				text: "Background"
				font.family: "Iosevka NF"
				font.pointSize: 24
				anchors.top: colorwheel.bottom
				anchors.left: parent.left
				anchors.topMargin: parent.width * 0.1
				anchors.leftMargin: parent.width * 0.1
				color: "#ffb642"
			}
			ColorWheel {
				id: colorwheel2
				anchors.top: textbackground.bottom
				anchors.left: parent.left
				anchors.leftMargin: (rootrectangle.width
				- colorwheel.width) / 2
				anchors.topMargin: ((rootrectangle.width
				- colorwheel.width) / 2)
				+ (colorwheel.width * 0.15)
				visible: true
				width: parent.width - (parent.width * 0.2)
			}
		}
		Rectangle {
			id: appearancebutton
			color: "#001e21"
			width: parent.width - (parent.border.width * 2)
			height: (parent.height / 4) - (parent.height / 10)
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottom: parent.bottom
			Behavior on color {
				ColorAnimation {
					duration: 125
				}
			}
			Text {
				id: appearancetext
				text: "Appearance"
				color: "#ffb642"
				anchors.fill: parent
				width: parent.width
				height: parent.height
				verticalAlignment: Text.AlignVCenter
				leftPadding: (appearanceicon.width
				+ appearanceicon.anchors.leftMargin) + 20
				font.pointSize: 20
				font.family: "Iosevka NF"
			}
			Image {
				id: appearanceicon
				source: "pallete.png"
				anchors.left: parent.left
				anchors.leftMargin: 20
				anchors.verticalCenter: parent.verticalCenter
				visible: false
				width: 30
				height: 30
			}
			ColorOverlay {
				id: colorappearanceicon
				anchors.fill: appearanceicon
				source: appearanceicon
				color: "#ffb642"
			}
			// Controls mouse area for appearance button
			MouseArea {
				anchors.fill: parent
				hoverEnabled: true

				// Change cursor to pointer on mouse over
				cursorShape: containsMouse ? Qt.PointingHandCursor
				: Qt.ArrowCursor;

				onEntered: {
					appearancebutton.color = "#002119";
				}
				onExited: {
					appearancebutton.color = "#001e21";
				}
				onClicked: {
					appearancebutton.state
					= "toggleappearance";
				}
			}
			states: [
				State {
					// Toggles appearance menu on
					name: "toggleappearance"
					AnchorChanges {
						target: appearancemenu
						anchors.left: rootrectangle.left
					}
					PropertyChanges {
						target: appearancebutton
						visible: false
					}
					PropertyChanges {
						target: colorwheel
						visible: true
					}
				},
				State {
					name: ""
					AnchorChanges {
						target: appearancemenu
						anchors.left: rootrectangle.right
					}
					PropertyChanges {
						target: appearancebutton
						visible: true
					}
					PropertyChanges {
						target: colorwheel
						visible: false
					}
				}
			]
			transitions: Transition {
				AnchorAnimation {
					targets: {
						appearancemenu
					}
					duration: 200
					easing.type: Easing.InOutQuad;
				}
				NumberAnimation {
					properties: appearancemenu.x
					duration: 200
					easing.type: Easing.InOutQuad;
				}
			}
		}
	}

	// Controls mouse interaction for cogwheel
	MouseArea {
		anchors.fill: colorcogwheel
		hoverEnabled: true

		// Change cursor to pointer on mouse over
		cursorShape: containsMouse ? Qt.PointingHandCursor
		: Qt.ArrowCursor;

		// When we hover over cogwheel it rotatates
		onEntered: { 
			colorcogwheel.rotation += 360
		}

		// Whenever cogwheel is clicked, toggle
		onClicked: {
			cogwheel.state == 'togglecogwheel'
			? cogwheel.state = ''
			: cogwheel.state = 'togglecogwheel'
		}
	}
}
