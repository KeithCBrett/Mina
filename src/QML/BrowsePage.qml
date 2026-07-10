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
	}

	YAxis {
		id: yAxis

		anchors.left: candlestickChart.right

		height: root.height
		width: 100

		max: 498.83
		min: 138.80

		color: ColorScheme.foreground
	}
}
