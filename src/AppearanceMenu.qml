// AppearanceMenu.qml represents the slide-out window that activates when
// AppearanceButton.qml is clicked

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

Rectangle {
	id: root

	// Caller of AppearanceMenu sets these
	property color inpColor1: "#000000"
	property color inpColor2: "#000000"
	property color inpMouseOverColor: "#000000"
	property real inpBorderWidth: 0
	property real inpButtonWidth: 0
	property real inpButtonHeight: 0
	property real inpFontSize: 1
	property real inpTopPadding: 0

	// The following states denote which theme/button is selected
	property string defaultButtonState: defaultButton.state
	property string godelButtonState: godelButton.state
	property string bloombergButtonState: bloombergButton.state
	property string factsetButtonState: factsetButton.state

	color: inpColor1
	border.color: inpColor2
	border.width: inpBorderWidth

	Column {
		id: appearanceMenuColumn
		anchors.fill: parent
		Component.onCompleted: defaultButton.state = "selectDefault"

		property real num_elements: 4
		property real total_element_height: num_elements
		* defaultButton.height
		property real height_delta: root.height - total_element_height

		spacing: height_delta / (num_elements - 1)
		- root.border.width
		padding: 1

		Rectangle {
			id: defaultButton
			color: root.color

			width: root.inpButtonWidth
			height: root.inpButtonHeight

			Text {
				id: defaultButtonText
				color: root.inpColor2

				text: "Default"
				font.pointSize: root.inpFontSize
				font.family: "Iosevka NF"
				padding: 10
				topPadding: root.inpTopPadding
			}

			MouseArea {
				id: defaultButtonMouse
				anchors.fill: parent
				hoverEnabled: true

				cursorShape: containsMouse
				? Qt.PointingHandCursor
				: Qt.ArrowCursor

				onEntered: {
					defaultButton.border.width = 1
					defaultButton.border.color
					= inpColor2
					defaultButton.color = inpMouseOverColor
				}

				onExited: {
					defaultButton.color = root.inpColor1

					defaultButton.border.width
					= (defaultButton.state
					== "selectDefault")
					? 1 : 0
				}

				onClicked: {
					defaultButton.state = "selectDefault"
					godelButton.state = ""
					bloombergButton.state = ""
					factsetButton.state = ""
				}
			}

			states: [
				State {
					name: "selectDefault"
					PropertyChanges {
						target: defaultButton
						border.width: 1
						border.color: root.inpColor2
						color: inpColor1
					}
					PropertyChanges {
						target: godelButton
						color: inpColor1
					}
					PropertyChanges {
						target: bloombergButton
						color: inpColor1
					}
					PropertyChanges {
						target: factsetButton
						color: inpColor1
					}
				},
				State {
					name: ""
					PropertyChanges {
						target: defaultButton
						border.width: 0
						color: inpColor1
					}
					PropertyChanges {
						target: godelButton
						color: inpColor1
					}
					PropertyChanges {
						target: bloombergButton
						color: inpColor1
					}
					PropertyChanges {
						target: factsetButton
						color: inpColor1
					}
				}
			]

			Behavior on color {
				ColorAnimation {
					easing.type: Easing.InOutQuad;
					duration: 200
				}
			}
		}

		Rectangle {
			id: godelButton
			color: root.color

			width: root.inpButtonWidth
			height: root.inpButtonHeight

			Text {
				id: godelButtonText
				color: root.inpColor2

				text: "Godel"
				font.pointSize: root.inpFontSize
				font.family: "Iosevka NF"
				padding: 10
				topPadding: root.inpTopPadding
			}

			MouseArea {
				id: godelButtonMouse
				anchors.fill: parent
				hoverEnabled: true

				cursorShape: containsMouse
				? Qt.PointingHandCursor
				: Qt.ArrowCursor

				onEntered: {
					godelButton.border.width = 1
					godelButton.border.color
					= inpColor2
					godelButton.color = inpMouseOverColor
				}

				onExited: {
					godelButton.color = root.inpColor1

					godelButton.border.width
					= (godelButton.state
					== "selectGodel")
					? 1 : 0
				}

				onClicked: {
					godelButton.state = "selectGodel"
					defaultButton.state = ""
					bloombergButton.state = ""
					factsetButton.state = ""
				}
			}

			states: [
				State {
					name: "selectGodel"
					PropertyChanges {
						target: godelButton
						border.width: 1
						border.color: root.inpColor2
						color: inpColor1
					}
					PropertyChanges {
						target: defaultButton
						color: inpColor1
					}
					PropertyChanges {
						target: bloombergButton
						color: inpColor1
					}
					PropertyChanges {
						target: factsetButton
						color: inpColor1
					}
				},
				State {
					name: ""
					PropertyChanges {
						target: godelButton
						border.width: 0
						color: inpColor1
					}
					PropertyChanges {
						target: defaultButton
						color: inpColor1
					}
					PropertyChanges {
						target: bloombergButton
						color: inpColor1
					}
					PropertyChanges {
						target: factsetButton
						color: inpColor1
					}
				}
			]

			Behavior on color {
				ColorAnimation {
					easing.type: Easing.InOutQuad;
					duration: 200
				}
			}
		}

		Rectangle {
			id: bloombergButton
			color: root.color

			width: root.inpButtonWidth
			height: root.inpButtonHeight

			Text {
				id: bloombergButtonText
				color: root.inpColor2

				text: "Bloomberg"
				font.pointSize: root.inpFontSize
				font.family: "Iosevka NF"
				padding: 10
				topPadding: root.inpTopPadding
			}

			MouseArea {
				id: bloombergButtonMouse
				anchors.fill: parent
				hoverEnabled: true

				cursorShape: containsMouse
				? Qt.PointingHandCursor
				: Qt.ArrowCursor

				onEntered: {
					bloombergButton.border.width = 1
					bloombergButton.border.color
					= inpColor2
					bloombergButton.color = inpMouseOverColor
				}

				onExited: {
					bloombergButton.color = root.inpColor1

					bloombergButton.border.width
					= (bloombergButton.state
					== "selectBloomberg")
					? 1 : 0
				}

				onClicked: {
					bloombergButton.state = "selectBloomberg"
					defaultButton.state = ""
					godelButton.state = ""
					factsetButton.state = ""
				}
			}

			states: [
				State {
					name: "selectBloomberg"
					PropertyChanges {
						target: bloombergButton
						border.width: 1
						border.color: root.inpColor2
						color: inpColor1
					}
					PropertyChanges {
						target: defaultButton
						color: inpColor1
					}
					PropertyChanges {
						target: godelButton
						color: inpColor1
					}
					PropertyChanges {
						target: factsetButton
						color: inpColor1
					}
				},
				State {
					name: ""
					PropertyChanges {
						target: bloombergButton
						border.width: 0
						color: inpColor1
					}
					PropertyChanges {
						target: godelButton
						color: inpColor1
					}
					PropertyChanges {
						target: defaultButton
						color: inpColor1
					}
					PropertyChanges {
						target: factsetButton
						color: inpColor1
					}
				}
			]

			Behavior on color {
				ColorAnimation {
					easing.type: Easing.InOutQuad;
					duration: 200
				}
			}
		}

		Rectangle {
			id: factsetButton
			color: root.color

			width: root.inpButtonWidth
			height: root.inpButtonHeight

			Text {
				id: factsetButtonText
				color: root.inpColor2

				text: "FactSet"
				font.pointSize: root.inpFontSize
				font.family: "Iosevka NF"
				padding: 10
				topPadding: root.inpTopPadding
			}

			MouseArea {
				id: factsetButtonMouse
				anchors.fill: parent
				hoverEnabled: true

				cursorShape: containsMouse
				? Qt.PointingHandCursor
				: Qt.ArrowCursor

				onEntered: {
					factsetButton.border.width = 1
					factsetButton.border.color
					= inpColor2
					factsetButton.color = inpMouseOverColor
				}

				onExited: {
					factsetButton.color = root.inpColor1
					factsetButton.border.width = 0

					factsetButton.border.width
					= (factsetButton.state
					== "selectFactset")
					? 1 : 0
				}

				onClicked: {
					factsetButton.state = "selectFactset"
					defaultButton.state = ""
					godelButton.state = ""
					bloombergButton.state = ""
				}
			}

			states: [
				State {
					name: "selectFactset"
					PropertyChanges {
						target: factsetButton
						border.width: 1
						border.color: root.inpColor2
						color: inpColor1
					}
					PropertyChanges {
						target: defaultButton
						color: inpColor1
					}
					PropertyChanges {
						target: godelButton
						color: inpColor1
					}
					PropertyChanges {
						target: bloombergButton
						color: inpColor1
					}
				},
				State {
					name: ""
					PropertyChanges {
						target: factsetButton
						border.width: 0
						color: inpColor1
					}
					PropertyChanges {
						target: godelButton
						color: inpColor1
					}
					PropertyChanges {
						target: bloombergButton
						color: inpColor1
					}
					PropertyChanges {
						target: defaultButton
						color: inpColor1
					}
				}
			]

			Behavior on color {
				ColorAnimation {
					easing.type: Easing.InOutQuad;
					duration: 200
				}
			}
		}
	}

	states: [
		State {
			name: "toggleMenu"
			AnchorChanges {
				target: root
				anchors.left: parent.left
			}
		},

		State {
			name: ""
			AnchorChanges {
				target: root
				anchors.left: parent.right
			}
		}
	]

	Behavior on color {
		ColorAnimation {
			easing.type: Easing.InOutQuad;
			duration: 200
		}
	}

	transitions: Transition {
		AnchorAnimation {
			easing.type: Easing.InOutQuad;
			duration: 200
		}
	}
}
