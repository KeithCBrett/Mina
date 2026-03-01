// VersionNumberInfo wraps cmake/git version number logic from
// GetVersionNum () into a QObject so that it may be used in QML GUI.

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
#ifndef VERSION_NUMBER_INFO_H
#define VERSION_NUMBER_INFO_H

#include <QObject>
#include "GetVersionNum.hpp"
#include "qqml.h"

class VersionNumberInfo : public QObject
{
	Q_OBJECT
	QML_ELEMENT
	Q_PROPERTY (QString patch READ patch NOTIFY patchChanged)
	Q_PROPERTY (QString minor READ minor NOTIFY minorChanged)
	Q_PROPERTY (QString major READ major NOTIFY majorChanged)

public:
	explicit VersionNumberInfo (QObject *parent = nullptr);
	QString patch () const;
	QString minor () const;
	QString major () const;

public slots:
	QString getPatch ();
	QString getMajor ();
	QString getMinor ();

signals:
	void patchChanged ();
	void minorChanged ();
	void majorChanged ();

private:
	QString c_patch = "00";
	QString c_minor = "00";
	QString c_major = "00";
};
#endif
