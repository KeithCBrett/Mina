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
import QtCharts 2.10

Rectangle {
	id: root

	color: dropdownMenu.backgroundColor

	ChartView {
		title: ""
		legend.visible: false

		backgroundColor: dropdownMenu.backgroundColor
		plotAreaColor: dropdownMenu.backgroundColor
		titleColor: dropdownMenu.backgroundColor

		width: 500
		height: 500

		CandlestickSeries {
			increasingColor: "#00c531"
			decreasingColor: "#ff5f5f"

			axisX: DateTimeAxis {
				gridVisible: false
				format: "dd/MM"
				color: dropdownMenu.foregroundColor
				labelsColor: dropdownMenu.foregroundColor
				labelsFont.pixelSize: 16
				labelsFont.family: "Iosevka NF"
			}

			axisY: ValueAxis {
				color: dropdownMenu.foregroundColor
				gridLineColor: dropdownMenu.foregroundColor
				labelsColor: dropdownMenu.foregroundColor
				labelsFont.pixelSize: 16
				labelsFont.family: "Iosevka NF"
			}

			CandlestickSet {
				timestamp: 0
				open: 690
				high: 700
				low: 575
				close: 630
			}

			CandlestickSet {
				timestamp: 100000
				open: 630
				high: 750
				low: 575
				close: 710
			}

			CandlestickSet {
				timestamp: 200000
				open: 710
				high: 1200
				low: 575
				close: 1000
			}

			CandlestickSet {
				timestamp: 300000
				open: 1000
				high: 1200
				low: 575
				close: 750
			}
		}
	}
}
