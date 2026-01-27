// DropdownMenu is graphically represented by the cogwheel in the top right
// corner of each GUI page. Written in Qt's QML framework

// Copyright (C) 2026  Keith C Brett (KeithCBrett@gmail.com)

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
				name: "toggleCogwheel"
				PropertyChanges {
					target: cogwheel;
					anchors.rightMargin: parent.width / 2
				}
				// Show buttons
				PropertyChanges {
					target: appearanceButton
					visible: true
				}
			},
			State {
				name: ""
				PropertyChanges {
					appearanceButton.state: ""
				}
				PropertyChanges {
					appearanceButton.visible: false
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
		id: colorCogwheel
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
		id: rootRectangle
		color: "#001e21"
		anchors.top: dropdown.top
		anchors.bottom: dropdown.bottom
		anchors.right: dropdown.right
		anchors.left: colorCogwheel.right
		anchors.leftMargin: 40
		border {
			color: "#ffb642"
		}
		Rectangle {
			id: appearanceMenu
			width: rootRectangle.width
			height: rootRectangle.height
			anchors.left: parent.right
			color: "#001e21"
			border.color: "#ffb642"
		}
		Rectangle {
			id: appearanceButton
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
				id: appearanceText
				text: "Appearance"
				color: "#ffb642"
				anchors.fill: parent
				width: parent.width
				height: parent.height
				verticalAlignment: Text.AlignVCenter
				leftPadding: (appearanceIcon.width
				+ appearanceIcon.anchors.leftMargin) + 20
				font.pointSize: 20
				font.family: "Iosevka NF"
			}
			Image {
				id: appearanceIcon
				source: "pallete.png"
				anchors.left: parent.left
				anchors.leftMargin: 20
				anchors.verticalCenter: parent.verticalCenter
				visible: false
				width: 30
				height: 30
			}
			ColorOverlay {
				id: colorAppearanceIcon
				anchors.fill: appearanceIcon
				source: appearanceIcon
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
					appearanceButton.color = "#002119";
				}
				onExited: {
					appearanceButton.color = "#001e21";
				}
				onClicked: {
					appearanceButton.state
					= "toggleAppearance";
				}
			}
			states: [
				State {
					// Toggles appearance menu on
					name: "toggleAppearance"
					AnchorChanges {
						target: appearanceMenu
						anchors.left: rootRectangle.left
					}
					PropertyChanges {
						target: appearanceButton
						visible: false
					}
				},
				State {
					name: ""
					AnchorChanges {
						target: appearanceMenu
						anchors.left: rootRectangle.right
					}
					PropertyChanges {
						target: appearanceButton
						visible: true
					}
				}
			]
			transitions: Transition {
				AnchorAnimation {
					targets: {
						appearanceMenu
					}
					duration: 200
					easing.type: Easing.InOutQuad;
				}
				NumberAnimation {
					properties: appearanceMenu.x
					duration: 200
					easing.type: Easing.InOutQuad;
				}
			}
		}
	}

	// Controls mouse interaction for cogwheel
	MouseArea {
		anchors.fill: colorCogwheel
		hoverEnabled: true

		// Change cursor to pointer on mouse over
		cursorShape: containsMouse ? Qt.PointingHandCursor
		: Qt.ArrowCursor;

		// When we hover over cogwheel it rotatates
		onEntered: { 
			colorCogwheel.rotation += 360
		}

		// Whenever cogwheel is clicked, toggle
		onClicked: {
			cogwheel.state == 'toggleCogwheel'
			? cogwheel.state = ''
			: cogwheel.state = 'toggleCogwheel'
		}
	}
}
