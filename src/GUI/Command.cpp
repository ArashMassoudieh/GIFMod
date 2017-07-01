
#include "Command.h"



CCommand::CCommand()
{
}

CCommand::CCommand(QString s) //create command from script
{
	QStringList list = s.split(",");
	if (list.size() == 0) return;
	 
	command = list[0].split(" ")[0];
	if (list[0].split(" ").size() == 2) name = list[0].split(" ")[1];
	for (int i = 1; i < list.size(); i++)
	{
		parameters[list[i].split("=")[0]] = list[i].split("=")[1];
	}
}

CCommand::CCommand(const CCommand & s)
{
	name = s.name;
	parameters = s.parameters;
	command = s.command;
}

CCommand& CCommand::operator=(const CCommand & s)
{
	command = s.command;
	parameters = s.parameters;
	name = s.name;

	return *this;
}

QString CCommand::toQString()
{
	QString S; 
	S.append(command);
	S.append(" ");
	S.append(name);
	S.append(" ");
	for (int i = 0; i < parameters.size(); i++)
	{
		S.append(parameters.key(i));
		S.append("=");
		S.append(parameters.value(parameters.key(i)).toQString());
		S.append("[");
		S.append(parameters.value(parameters.key(i)).unit);
		S.append("]");
		if (i < parameters.size() - 1) S.append(",");
	}
	return S;
}

CCommand::CCommand(string s)
{
	CCommand(QString(s.c_str()));
}




CCommand::~CCommand()
{
}
