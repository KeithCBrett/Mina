// AboutMenu.qml represents the menu that slides out when 'About' is clicked
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
import mina_module


Rectangle {
	id: root

	color: ColorScheme.settingsMenu

	width: parent.width - ConstSingleton.dropdownMenuWidthOffset
	height: parent.height

	border.color: ColorScheme.foreground
	border.width: ConstSingleton.borderWidth

	Text {
		id: aboutMenuText

		anchors.fill: parent

		color: ColorScheme.foreground

		wrapMode: Text.WordWrap
		padding: 10

		font.pointSize: (ConstSingleton.buttonFontSize - 2)
		font.family: ConstSingleton.defaultFont

		text: "Mina:\nis a equity analyzer that performs various"
		+ " functions related to the appraisal of common stock"
		+ " (Such as DCF, NOPLAT, ROIC, etc)\n\nContact:"
		+ " KeithCBrett@gmail.com\n\nLicense:\nGPLv3\n\nVersion:\n"
		+ version_number.getMajor() + "." + version_number.getMinor()
		+ "." + version_number.getPatch()
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
