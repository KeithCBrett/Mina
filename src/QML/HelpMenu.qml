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

	property color inpColor1: "#000000"
	property color inpColor2: "#000000"

	color: inpColor1
	border.color: inpColor2
	border.width: 1

	Text {
		id: helpMenuText

		anchors.fill: parent
		color: inpColor2
		wrapMode: Text.WordWrap
		padding: 10
		font.pointSize: 22
		font.family: "Iosevka NF"

		text: "*The contents of this menu change depending on which"
		+ " page you are on*\n\nThis is the 'Home' page. Consolidates"
		+ " access to other pages.\n\nPress 'Browse' to browse equities"
		+ " on various indices. Provides a convinient way to find"
		+ " equities you want to perform analysis on."
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
