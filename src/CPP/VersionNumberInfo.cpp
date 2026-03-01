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
