// AboutButton.qml represents the clickable about button found in
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
	- (aboutButtonImage.height / 2)
	property color inpColor1: "#000000"
	property color inpColor2: "#000000"

	color: inpColor2

	Row {
		spacing: 16
		padding: 10
		topPadding: inpTopPadding

		Image {
			id: aboutButtonImage
			source: "images/info.png"

			visible: false

			width: 30
			height: 30

			layer.enabled: true
			layer.effect: ColorOverlay {
				id: aboutButtonImageColor
				source: aboutButtonImage

				visible: false

				anchors.fill: aboutButtonImage
				smooth: true
				color: inpColor1
			}
		}
		
		Text {
			id: aboutButtonText
			text: "About"

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
				target: aboutButtonText
				visible: true
			}
			PropertyChanges {
				target: aboutButtonImage
				visible: true
			}
		},
		State {
			name: ""
			PropertyChanges {
				target: aboutButtonText
				visible: false
			}
			PropertyChanges {
				target: aboutButtonImage
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
