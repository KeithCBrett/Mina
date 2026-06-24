// DropdownButtonColumn.qml represents the slide out column of buttons that
// appears in the U.I. when the cogwheel icon is clicked.

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


Item {
    id: root

    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.leftMargin: 40

    // Draw outline
    Rectangle {
        anchors.fill: parent

        color: ColorScheme.settingsMenu

        border.color: ColorScheme.foreground
        border.width: ConstSingleton.borderWidth
    }

    Column {
        id: column

        anchors.fill: parent

        spacing: (parent.height / 5) / 3 - 0.25

        HomeButton {
            id: homeButton
        }
        HelpButton { }
        AboutButton { }
        ManualButton { }
    }
}
