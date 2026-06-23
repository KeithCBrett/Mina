// VersionNumberInfo.cpp provides utilities for calculating which version
// number we are on based on the number of version control commits.

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


#include "VersionNumberInfo.hpp"

VersionNumberInfo::VersionNumberInfo (QObject *parent)
	: QObject{parent}
{

}


QString VersionNumberInfo::patch () const
{
	return c_patch;
}


QString VersionNumberInfo::minor () const
{
	return c_minor;
}


QString VersionNumberInfo::major () const
{
	return c_major;
}


QString VersionNumberInfo::getPatch ()
{
	unsigned num_commits = GetNumCommits ();
	QString out_string = "00";

	if ((num_commits % 100) == 0)
	{
		out_string[0] = '0';
		out_string[1] = '0';
	}
	else if ((num_commits % 100) < 10)
	{
		QChar c (((short) (num_commits % 100)) + 48);
		out_string[0] = '0';
		out_string[1] = c;
	}
	else
	{
		QChar c (((short) ((num_commits % 100) / 10)) + 48);
		out_string[0] = c;
		QChar b (((short) ((num_commits % 100) % 10)) + 48);
		out_string[1] = b;
	}

	return out_string;
}


QString VersionNumberInfo::getMinor ()
{
	short num_commits = (short) GetNumCommits ();
	QString out_string = "00";

	if ((num_commits / 100) == 0)
	{
		out_string[0] = '0';
		out_string[1] = '0';
	}
	else if ((num_commits / 100) < 10)
	{
		QChar c (((short) (num_commits / 100)) + 48);
		out_string[0] = '0';
		out_string[1] = c;
	}
	else
	{
		QChar c (((short) (num_commits / 100) / 10) + 48);
		out_string[0] = c;
		QChar b (((short) (num_commits / 100) % 10) + 48);
		out_string[1] = b;
	}

	return out_string;
}


QString VersionNumberInfo::getMajor ()
{
	return "00";
}
