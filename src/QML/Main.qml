// Main.qml is the graphical entry to the program (i.e. the first GUI page
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
import QtQuick.Controls
import QtQuick.Window
import mina_module


Window {
	id: root

	width: 1920
	height: 1080

	color: ColorScheme.background

	property VersionNumberInfo version_number: VersionNumberInfo {}

	visible: true
	title: qsTr("Mina")

	StackView {
		id: stack

		anchors.fill: parent
		initialItem: homePage

		pushEnter: Transition {
			NumberAnimation {
				property: "y"
				from: -stack.height
				to: 0
				duration: ConstSingleton.baseAnimationSpeed
				easing.type: Easing.InOutQuad
			}
		}

		pushExit: Transition {
			NumberAnimation {
				property: "y"
				from: 0
				to: stack.height
				duration: ConstSingleton.baseAnimationSpeed
				easing.type: Easing.InOutQuad
			}
		}

		popEnter: Transition {
			NumberAnimation {
				property: "y"
				from: stack.height
				to: 0
				duration: ConstSingleton.baseAnimationSpeed
				easing.type: Easing.InOutQuad
			}
		}

		popExit: Transition {
			NumberAnimation {
				property: "y"
				from: 0
				to: -stack.height
				duration: ConstSingleton.baseAnimationSpeed
				easing.type: Easing.InOutQuad
			}
		}
	}

	Component {
		id: browsePage
		BrowsePage {}
	}


	Component {
		id: homePage
		HomePage {}
	}

	Component {
		id: manualPage
		ManualPage {}
	}
}
