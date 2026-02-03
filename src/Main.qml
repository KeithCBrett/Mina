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


Window {
	width: 1920
	height: 1080
	//color: '#001320'
	color: dropdownMenu.backgroundColor

	visible: true
	title: qsTr("KCBfin")
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
