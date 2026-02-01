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
					target: cogwheel
					anchors.rightMargin: parent.width / 2
				}
				PropertyChanges {
					target: appearanceButton
					state: "toggleButton"
				}
			},

			State {
				name: ""
				PropertyChanges {
					target: appearanceMenu
					state: ""
				}
				PropertyChanges {
					target: appearanceButton
					state: ""
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
			width: 1
		}

		Column {
			id: dropdownButtonColumn

			property real num_elements: 4
			property real total_element_height: num_elements
			* appearanceButton.height
			property real height_delta: rootRectangle.height
			- total_element_height

			spacing: height_delta / (num_elements - 1)
			- rootRectangle.border.width
			anchors.fill: parent

			leftPadding: rootRectangle.border.width
			topPadding: rootRectangle.border.width
			bottomPadding: rootRectangle.border.width

			AppearanceButton {
				id: appearanceButton

				inpFontSize: 22
				inpLeftMargin: rootRectangle.border.width
				width: rootRectangle.width
				- (rootRectangle.border.width * 2)
				height: (rootRectangle.height / 4)
				- ((rootRectangle.height / 4) * 0.25)

				MouseArea {
					id: appearanceButtonMouse
					anchors.fill: parent
					hoverEnabled: true

					onClicked: {
						appearanceMenu.state
						= "toggleMenu"
						appearanceButton.state
						= ""
					}

					onEntered: {
						appearanceButton.color
						= "#000921"
						appearanceButton.border.color
						= "#ffb642"
						appearanceButton.border.width
						= 1
						cursorShape
						= Qt.PointingHandCursor
					}

					onExited: {
						appearanceButton.color
						= "#001e21"
						appearanceButton.border.width
						= 0
						cursorShape
						= Qt.ArrowCursor
					}
				}
			}

			AppearanceButton {
				width: rootRectangle.width
				- (rootRectangle.border.width * 2)
				height: (rootRectangle.height / 4)
				- ((rootRectangle.height / 4) * 0.25)
			}

			AppearanceButton {
				width: rootRectangle.width
				- (rootRectangle.border.width * 2)
				height: (rootRectangle.height / 4)
				- ((rootRectangle.height / 4) * 0.25)
			}

			AppearanceButton {
				width: rootRectangle.width
				- (rootRectangle.border.width * 2)
				height: (rootRectangle.height / 4)
				- ((rootRectangle.height / 4) * 0.25)
			}
		}
		// Code for slide-out menus that appear when *Button.qml is
		// clicked
		AppearanceMenu {
			id: appearanceMenu

			inpColor1: "#001e21"
			inpColor2: "#ffb642"
			inpBorderWidth: rootRectangle.border.width
			inpButtonWidth: appearanceButton.width
			inpButtonHeight: appearanceButton.height
			inpFontSize: appearanceButton.inpFontSize
			inpTopPadding: appearanceButton.inpTopPadding

			width: rootRectangle.width
			height: rootRectangle.height

			anchors.left: rootRectangle.right
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
