// Main.qml is the graphical entry to the program (i.e. the first GUI page
// the user interacts with on application launch)

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
import QtQuick.Window
import mina


Window {
	id: root

	width: 1920
	height: 1080
	//color: '#001320'
	color: dropdownMenu.backgroundColor

	property VersionNumberInfo version_number: VersionNumberInfo {}
	property color foregroundColor: dropdownMenu.foregroundColor
	property color backgroundColor: dropdownMenu.backgroundColor
	property color settingsMenuColor: dropdownMenu.settingsMenuColor
	property color mouseOverColor: dropdownMenu.mouseOverColor

	visible: true
	title: qsTr("Mina")

	StackView {
		id: stack
		initialItem: homePage
		BrowsePage {
			id: browsePage
		}
		anchors.fill: parent
	}

	Component {
		id: homePage

		Rectangle {
			id: homePageRect

			width: root.width
			height: root.height

			color: root.color

			Text {
				id: logo

				text: "Mina"
				color: root.foregroundColor
				padding: 20
				bottomPadding: 0

				font.pointSize: 32
				font.family: "Iosevka NF"
			}

			Text {
				id: versionNumberText

				anchors.top: logo.bottom
				text: "Version:\n" + version_number.getMajor()
				+ "." + version_number.getMinor() + "."
				+ version_number.getPatch()
				padding: 20
				color: root.foregroundColor
				topPadding: 0
				font.pointSize: 16
				font.family: "Iosevka NF"
			}


			BrowseButton {
				id: browseButton
				MouseArea {
					id: browseButtonMouse
					anchors.fill: parent

					hoverEnabled: true

					onEntered: {
						cursorShape
						= Qt.PointingHandCursor
						browseButton.color
						= dropdownMenu.mouseOverColor
					}

					onExited: {
						cursorShape = Qt.ArrowCursor
						browseButton.color
						= dropdownMenu
						.settingsMenuColor
					}

					onClicked: {
						stack.push(browsePage)
					}
				}
			}

			Behavior on color {
				ColorAnimation {
					easing.type: Easing.InOutQuad;
					duration: 200
				}
			}
		}
	}

	DropdownMenu {
		id: dropdownMenu
	}
}
