#pragma once
#include "qstring.h"
#include "qmap.h"
#include "XString.h"
#include "StringOP.h"

class CCommand //this class stores commands 
{
public:
	CCommand(); //default constructor 
	CCommand(QString s);
	CCommand(const CCommand &s);
	CCommand& CCommand::operator=(const CCommand &s);
	QString toQString();
	CCommand(string s);
	~CCommand();
	QString command;
	QString name; 
	QMap<QString,XString> parameters; 

	
};

