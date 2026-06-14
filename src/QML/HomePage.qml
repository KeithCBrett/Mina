// HomePage.qml represents the first U.I. page you see when you launch Mina.

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

	width: parent.width
	height: parent.height

	color: ColorScheme.background

	DropdownMenu {
		id: homePageMenu
	}

	Text {
		id: logo

		text: "Mina"
		color: ColorScheme.foreground

		padding: 20
		bottomPadding: 0

		font.pointSize: 32
		font.family: ConstSingleton.defaultFont
	}

	Text {
		id: versionNumberText

		anchors.top: logo.bottom

		text: "Version:\n" + version_number.getMajor()
		+ "." + version_number.getMinor() + "."
		+ version_number.getPatch()
		color: ColorScheme.foreground

		padding: 20
		topPadding: 0


		font.pointSize: 16
		font.family: ConstSingleton.defaultFont
	}


	BrowseButton {
		id: browseButton
	}

	Behavior on color {
		ColorAnimation {
			easing.type: Easing.InOutQuad;
			duration: 200
		}
	}
}
