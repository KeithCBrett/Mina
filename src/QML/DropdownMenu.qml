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
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import mina


Item {
	id: dropdown

	width: (parent.width / 2)
	height: parent.height

	anchors.right: parent.right
	anchors.top: parent.top

	function getForegroundColor () {
		var out_color = "#000000"
		if (appearanceMenu.defaultButtonState == "selectDefault") {
			out_color = "#ffb642"
		}
		if (appearanceMenu.godelButtonState == "selectGodel") {
			out_color = "#006c6f"
		}
		if (appearanceMenu.bloombergButtonState == "selectBloomberg") {
			out_color = "#fc8b19"
		}
		if (appearanceMenu.factsetButtonState == "selectFactset") {
			out_color = "#0b2e54"
		}
		return out_color
	}

	function getBackgroundColor () {
		var out_color = "#000000"
		if (appearanceMenu.defaultButtonState == "selectDefault") {
			out_color = "#001320"
		}
		if (appearanceMenu.godelButtonState == "selectGodel") {
			out_color = "#181818"
		}
		if (appearanceMenu.bloombergButtonState == "selectBloomberg") {
			out_color = "#000000"
		}
		if (appearanceMenu.factsetButtonState == "selectFactset") {
			out_color = "#ffffff"
		}
		return out_color
	}

	function getSettingsMenuColor () {
		var out_color = "#000000"
		if (appearanceMenu.defaultButtonState == "selectDefault") {
			out_color = "#001e21"
		}
		if (appearanceMenu.godelButtonState == "selectGodel") {
			out_color = "#171717"
		}
		if (appearanceMenu.bloombergButtonState == "selectBloomberg") {
			out_color = "#1d1d1d"
		}
		if (appearanceMenu.factsetButtonState == "selectFactset") {
			out_color = "#fafafa"
		}
		return out_color
	}

	function getMouseOverColor () {
		var out_color = "#000000"
		if (appearanceMenu.defaultButtonState == "selectDefault") {
			out_color = "#000921"
		}
		if (appearanceMenu.godelButtonState == "selectGodel") {
			out_color = "#181818"
		}
		if (appearanceMenu.bloombergButtonState == "selectBloomberg") {
			out_color = "#282828"
		}
		if (appearanceMenu.factsetButtonState == "selectFactset") {
			out_color = "#d9edf5"
		}
		return out_color
	}

	property color foregroundColor: getForegroundColor ()
	property color backgroundColor: getBackgroundColor ()
	property color settingsMenuColor: getSettingsMenuColor ()
	property color mouseOverColor: getMouseOverColor ()

	Image {
		id: cogwheel

		source: "images/setting.png"
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
				PropertyChanges {
					target: helpButton
					state: "toggleButton"
				}
				PropertyChanges {
					target: homeButton
					state: "toggleButton"
				}
				PropertyChanges {
					target: aboutButton
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
					enabled: true
					state: ""
				}

				PropertyChanges {
					target: appearanceButtonMouse
					enabled: true
				}

				PropertyChanges {
					target: helpMenu
					state: ""
				}

				PropertyChanges {
					target: helpButton
					state: ""
				}

				PropertyChanges {
					target: helpButtonMouse
					enabled: true
				}

				PropertyChanges {
					target: homeButtonMouse
					enabled: true
				}

				PropertyChanges {
					target: aboutMenu
					state: ""
				}

				PropertyChanges {
					target: aboutButtonMouse
					enabled: true
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
		color: foregroundColor

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
		
		Behavior on color {
			ColorAnimation {
				easing.type: Easing.InOutQuad;
				duration: 200
			}
		}
	}

	// Draw settings menu
	Rectangle {
		id: rootRectangle
		color: settingsMenuColor

		anchors.top: dropdown.top
		anchors.bottom: dropdown.bottom
		anchors.right: dropdown.right
		anchors.left: colorCogwheel.right
		anchors.leftMargin: 40

		border {
			color: foregroundColor
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

			HomeButton {
				id: homeButton

				inpColor1: foregroundColor
				inpColor2: settingsMenuColor

				width: rootRectangle.width
				- (rootRectangle.border.width * 2)
				height: (rootRectangle.height / 4)
				- ((rootRectangle.height / 4) * 0.25)

				MouseArea {
					id: homeButtonMouse
					anchors.fill: parent
					hoverEnabled: true

					onEntered: {
						homeButton.color
						= mouseOverColor

						homeButton.border.color
						= foregroundColor

						homeButton.border.width
						= 1

						cursorShape
						= Qt.PointingHandCursor
					}

					onExited: {
						homeButton.color
						= settingsMenuColor

						homeButton.border.width
						= 0

						cursorShape
						= Qt.ArrowCursor
					}

					onClicked: {
						stack.pop();
						cogwheel.state = "";
					}
				}
			}

			HelpButton {
				id: helpButton

				inpColor1: foregroundColor
				inpColor2: settingsMenuColor

				width: rootRectangle.width
				- (rootRectangle.border.width * 2)
				height: (rootRectangle.height / 4)
				- ((rootRectangle.height / 4) * 0.25)

				MouseArea {
					id: helpButtonMouse
					anchors.fill: parent
					hoverEnabled: true

					onClicked: {
						helpMenu.state
						= "toggleMenu"

						helpButton.state
						= ""

						helpButtonMouse.enabled
						= false

						aboutButtonMouse.enabled
						= false

						appearanceButtonMouse.enabled
						= false

						homeButtonMouse.enabled
						= false
					}

					onEntered: {
						helpButton.color
						= mouseOverColor

						helpButton.border.color
						= foregroundColor

						helpButton.border.width
						= 1

						cursorShape
						= Qt.PointingHandCursor
					}

					onExited: {
						helpButton.color
						= settingsMenuColor

						helpButton.border.width
						= 0

						cursorShape
						= Qt.ArrowCursor
					}
				}
			}


			AboutButton {
				id: aboutButton

				inpFontSize: 22
				inpLeftMargin: rootRectangle.border.width
				inpColor1: foregroundColor
				inpColor2: settingsMenuColor

				width: rootRectangle.width
				- (rootRectangle.border.width * 2)
				height: (rootRectangle.height / 4)
				- ((rootRectangle.height / 4) * 0.25)

				MouseArea {
					id: aboutButtonMouse
					anchors.fill: parent
					hoverEnabled: true

					onClicked: {
						aboutMenu.state
						= "toggleMenu"

						aboutButton.state
						= ""

						aboutButtonMouse.enabled
						= false

						homeButtonMouse.enabled
						= false

						appearanceButtonMouse.enabled
						= false

						helpButtonMouse.enabled
						= false
					}

					onEntered: {
						aboutButton.color
						= mouseOverColor

						aboutButton.border.color
						= foregroundColor

						aboutButton.border.width
						= 1

						cursorShape
						= Qt.PointingHandCursor
					}

					onExited: {
						aboutButton.color
						= settingsMenuColor

						aboutButton.border.width
						= 0

						cursorShape
						= Qt.ArrowCursor
					}
				}
			}
			
			AppearanceButton {
				id: appearanceButton

				inpFontSize: 22
				inpLeftMargin: rootRectangle.border.width
				inpColor1: foregroundColor
				inpColor2: settingsMenuColor

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

						appearanceButtonMouse.enabled
						= false

						aboutButtonMouse.enabled
						= false

						helpButtonMouse.enabled
						= false

						homeButtonMouse.enabled
						= false
					}

					onEntered: {
						appearanceButton.color
						= mouseOverColor

						appearanceButton.border.color
						= foregroundColor

						appearanceButton.border.width
						= 1

						cursorShape
						= Qt.PointingHandCursor
					}

					onExited: {
						appearanceButton.color
						= settingsMenuColor

						appearanceButton.border.width
						= 0

						cursorShape
						= Qt.ArrowCursor
					}
				}
			}
		}
		// Code for slide-out menus that appear when *Button.qml is
		// clicked
		AppearanceMenu {
			id: appearanceMenu

			inpColor1: settingsMenuColor
			inpColor2: foregroundColor
			inpMouseOverColor: mouseOverColor
			inpBorderWidth: rootRectangle.border.width
			inpButtonWidth: appearanceButton.width
			inpButtonHeight: appearanceButton.height
			inpFontSize: appearanceButton.inpFontSize
			inpTopPadding: appearanceButton.inpTopPadding

			width: rootRectangle.width
			height: rootRectangle.height

			anchors.left: rootRectangle.right
		}

		HelpMenu {
			id: helpMenu

			inpColor1: settingsMenuColor
			inpColor2: foregroundColor

			width: rootRectangle.width
			height: rootRectangle.height

			anchors.left: rootRectangle.right
		}

		AboutMenu {
			id: aboutMenu

			inpColor1: settingsMenuColor
			inpColor2: foregroundColor

			width: rootRectangle.width
			height: rootRectangle.height

			anchors.left: rootRectangle.right
		}

		Behavior on color {
			ColorAnimation {
				easing.type: Easing.InOutQuad;
				duration: 200
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
