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

	property real inpLeftMargin: 1
	property real inpFontSize: 22
	property real inpTopPadding: root.height / 2
	- (appearanceButtonImage.height / 2)
	property color inpColor1: "#000000"
	property color inpColor2: "#000000"

	color: inpColor2

	Row {
		spacing: 16
		padding: 10
		topPadding: inpTopPadding

		Image {
			id: appearanceButtonImage
			source: "images/pallete.png"

			visible: false

			width: 30
			height: 30

			layer.enabled: true
			layer.effect: ColorOverlay {
				id: appearanceButtonImageColor
				source: appearanceButtonImage

				visible: false

				anchors.fill: appearanceButtonImage
				smooth: true
				color: inpColor1
			}
		}
		
		Text {
			id: appearanceButtonText
			text: "Appearance"

			visible: false

			font.pointSize: inpFontSize
			font.family: "Iosevka NF"
			color: inpColor1

			topPadding: root.height * 0.001
		}
	}

	states: [
		State {
			name: "toggleButton"

			PropertyChanges {
				target: appearanceButtonText
				visible: true
			}
			PropertyChanges {
				target: appearanceButtonImage
				visible: true
			}
		},
		State {
			name: ""
			PropertyChanges {
				target: appearanceButtonText
				visible: false
			}
			PropertyChanges {
				target: appearanceButtonImage
				visible: false
			}
		}
	]

	Behavior on color {
		ColorAnimation {
			easing.type: Easing.InOutQuad;
			duration: 200
		}
	}
}
