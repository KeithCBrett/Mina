// BrowsePage.qml represents the page that is entered when 'Browse' on the
// home page is clicked

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

	color: ColorScheme.background

	DropdownMenu {
		id: browsePageMenu
	}

	StockList {
		id: stockList
	}

	CandlestickChart{
		id: candlestickChart

		anchors.left: stockList.right
		anchors.right: browsePageMenu.left
		anchors.rightMargin: ConstSingleton.cogwheelMargin

		borderColor: ColorScheme.foreground
		height: root.height
		width: root.width

		Crosshair {
			id: crosshair

			//width: parent.width
			//height: parent.height / 2
			anchors.centerIn: parent
			anchors.fill: parent

			color: ColorScheme.foreground
			visible: true

			width: parent.width
			height: parent.height

			posX: width / 2
			posY: height / 2

			min: ConstSingleton.min
			max: ConstSingleton.max

			price: "0"

			rightSwapped: false
			leftSwapped: false
			topSwapped: false

			//Behavior on posX {
			//	NumberAnimation {
			//		duration: 30
			//	}
			//}

			//Behavior on posY {
			//	NumberAnimation {
			//		duration: 30
			//	}
			//}
		}

		MouseArea {
			id: chartMouse

			anchors.fill: parent

			hoverEnabled: true

			onEntered: {
				crosshair.visible = true;
				crosshair.posX = chartMouse.mouseX;
				crosshair.posY = chartMouse.mouseY;
				crosshair.price = crosshair.getPrice();
			}

			onExited: {
				crosshair.visible = false;
				crosshair.price = crosshair.getPrice();
			}

			onPositionChanged: {
				crosshair.posX = chartMouse.mouseX;
				if (crosshair.posX > (chartMouse.width - chartMouse.width / 8))
				{
					crosshair.rightSwapped = true;
				}
				else
				{
					crosshair.rightSwapped = false;
				}

				if (crosshair.posX < chartMouse.width / 8)
				{
					crosshair.leftSwapped = true;
				}
				else
				{
					crosshair.leftSwapped = false;
				}

				crosshair.posY = chartMouse.mouseY;
				if (crosshair.posY < chartMouse.height / 15)
				{
					crosshair.topSwapped = true;
				}
				else
				{
					crosshair.topSwapped = false;
				}
				crosshair.price = crosshair.getPrice();
			}
		}
	}

	YAxis {
		id: yAxis

		anchors.left: candlestickChart.right

		height: root.height
		width: 100

		max: ConstSingleton.max
		min: ConstSingleton.min

		color: ColorScheme.foreground
	}
}
