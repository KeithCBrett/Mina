// DropdownMenu is graphically represented by the cogwheel in the top right
// corner of each GUI page. Written in Qt's QML framework.

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
import mina_module


Item {
	id: root

	height: parent.height
	width: parent.width

	anchors.right: parent.right
	anchors.left: parent.left

	anchors.leftMargin: parent.width - ConstSingleton.cogwheelWidth
	- ConstSingleton.cogwheelMargin

	Cogwheel {
		id: cogwheel
	}

	DropdownButtonColumn {
		id: buttonColumn

		anchors.left: cogwheel.right
	}

	HelpMenu {
		id: helpMenu

		anchors.left: buttonColumn.right
	}

	AboutMenu {
		id: aboutMenu

		anchors.left: buttonColumn.right
	}

	Behavior on anchors.leftMargin {
		PropertyAnimation {
			easing.type: Easing.InOutQuad
			duration: ConstSingleton.baseAnimationSpeed
		}
	}
}
