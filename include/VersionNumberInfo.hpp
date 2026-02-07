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
