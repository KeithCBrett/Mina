// AppearanceButton.qml represents the clickable appearance button found in
// the settings menu

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
import Qt5Compat.GraphicalEffects

Rectangle {
	id: root

	color: "#001e21"

	Row {
		spacing: 16
		padding: 10
		topPadding: root.height / 2
		- (appearanceButtonImage.height / 2)

		Image {
			id: appearanceButtonImage
			source: "pallete.png"

			width: 30
			height: 30

			layer.enabled: true
			layer.effect: ColorOverlay {
				id: appearanceButtonImageColor
				source: appearanceButtonImage
				anchors.fill: appearanceButtonImage
				color: "#ffb642"
			}
		}
		
		Text {
			id: appearanceButtonText
			text: "Appearance"

			font.pointSize: 22
			font.family: "Iosevka NF"
			color: "#ffb642"

			topPadding: root.height * 0.001
		}
	}

	MouseArea {
		id: appearanceButtonMouse
		anchors.fill: root
		hoverEnabled: true

		cursorShape: containsMouse ? Qt.PointingHandCursor
		: Qt.ArrowCursor;

		onEntered: {
			root.color = "#000921"
			root.border.color = "#ffb642"
			root.border.width = 1
		}
		
		onExited: {
			root.color = "#001e21"
			root.border.width = 0
		}
	}

	Behavior on color {
		ColorAnimation {
			easing.type: Easing.InOutQuad;
			duration: 200
		}
	}
}
