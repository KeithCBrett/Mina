// BrowseButtom.qml represents the 'Browse' button found on the home page.
// Mainly serves to bring the user to BrowsePage.qml

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


Rectangle {
	id: root
	anchors.centerIn: parent

	width: parent.width / 6
	height: parent.height / 8

	color: ColorScheme.settingsMenu

	border.color: ColorScheme.foreground
	border.width: ConstSingleton.borderWidth

	Text {
		id: browseButtonText
		anchors.centerIn: parent

		text: "Browse"
		color: ColorScheme.foreground

		font.family: ConstSingleton.defaultFont
		font.pointSize: 24
	}

	MouseArea {
		id: browseButtonMouse
		anchors.fill: parent

		hoverEnabled: true

		onEntered: {
			cursorShape
			= Qt.PointingHandCursor
			browseButton.color
			= ColorScheme.mouseOver
		}

		onExited: {
			cursorShape = Qt.ArrowCursor
			browseButton.color
			= ColorScheme
			.settingsMenu
		}

		onClicked: {
			stack.push(browsePage)
		}
	}

	Behavior on color {
		ColorAnimation {
			easing.type: Easing.InOutQuad;
			duration: ConstSingleton.baseAnimationSpeed
		}
	}
}
