// ConstSingleton.qml stores miscellanious global constants like the system
// font and whatever doesn't quite fit in other singletons.

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


pragma Singleton
import QtQuick


QtObject {
    // For DropdownMenu.qml buttons.
    property string defaultFont: "BigBlueTerm437 Nerd Font"
    property real buttonFontSize: 22

    // For DropdownMenu.qml cogwheel.
    property real cogwheelWidth: 30
    property real cogwheelMargin: 40

    // Length of most animations (in ms).
    property real baseAnimationSpeed: 200

    // Whether or not Dropdown menu buttons should be visible or not.
    property bool buttonsVisible: true

    // All of the menus inherit their widths from their parents. This is
    // naturally too big and cuts off the right border for the menus.
    // We can subtract by this number to get the correct width at all supported
    // screen sizes.
    property real dropdownMenuWidthOffset: 70

    // Width of most borders (in px).
    property real borderWidth: 2
}
