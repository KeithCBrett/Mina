// home.qml is the graphical entry to the program (i.e. the first GUI page
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
import QtQuick.Window
import mina


Window {
	width: 1920
	height: 1080
	//color: '#001320'
	color: dropdownMenu.backgroundColor

	property VersionNumberInfo version_number: VersionNumberInfo {}

	visible: true
	title: qsTr("Mina")

	Text {
		id: logo

		text: "Mina"
		color: dropdownMenu.foregroundColor
		padding: 20
		bottomPadding: 0

		font.pointSize: 32
		font.family: "Iosevka NF"
	}

	Text {
		id: versionNumberText

		anchors.top: logo.bottom
		text: "Version:\n" + version_number.getMajor() + "."
		+ version_number.getMinor() + "." + version_number.getPatch()
		padding: 20
		color: dropdownMenu.foregroundColor
		topPadding: 0
		font.pointSize: 16
		font.family: "Iosevka NF"
	}

	DropdownMenu {
		id: dropdownMenu
	}

	Behavior on color {
		ColorAnimation {
			easing.type: Easing.InOutQuad;
			duration: 200
		}
	}
}
