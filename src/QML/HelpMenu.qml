// HelpMenu.qml represents the menu that slides out when 'help' is clicked
// in the settings menu

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

	color: ColorScheme.settingsMenu

	width: parent.width - ConstSingleton.dropdownMenuWidthOffset
	height: parent.height

	border.color: ColorScheme.foreground
	border.width: ConstSingleton.borderWidth

	Text {
		id: helpMenuText

		anchors.fill: parent

		color: ColorScheme.foreground

		wrapMode: Text.WordWrap
		padding: 10

		font.pointSize: (ConstSingleton.buttonFontSize - 2)
		font.family: ConstSingleton.defaultFont

		text: "*The contents of this menu change depending on which"
		+ " page you are on*\n\nThis is the 'Home' page. Consolidates"
		+ " access to other pages.\n\nPress 'Browse' to browse equities"
		+ " on various indices. Provides a convinient way to find"
		+ " equities you want to perform analysis on."
	}

	Behavior on color {
		ColorAnimation {
			easing.type: Easing.InOutQuad;
			duration: ConstSingleton.baseAnimationSpeed
		}
	}

	states: [
		State {
			name: "toggle"

			AnchorChanges {
				target: root
				anchors.left: buttonColumn.left
			}
		}
	]

	transitions: Transition {
		AnchorAnimation {
			easing.type: Easing.InOutQuad
			duration: ConstSingleton.baseAnimationSpeed
		}
	}
}
