
#include "Command.h"
#include "utility_funcs.h"



CCommand::CCommand()
{
}

CCommand::CCommand(QString s) //create command from script
{
	QStringList list = s.split(":");
	if (list.size() == 0) return;
	 
	command = extract_by_space_quote(list[0].trimmed().toLower())[0];
	if (extract_by_space_quote(list[0].trimmed().toLower()).size() > 1) values = extract_by_space_quote(list[0].trimmed());
	values.removeAt(0);
	for (int i = 0; i < values.count(); i++) values[i] = values[i].trimmed();
	for (int i = 1; i < list.size(); i++)
	{
		parameters[list[i].split("=")[0].trimmed().toLower()] = list[i].split("=")[1].trimmed().toLower();
	}
}

CCommand::CCommand(const CCommand & s)
{
	values = s.values;
	parameters = s.parameters;
	command = s.command;
}

CCommand& CCommand::operator=(const CCommand & s)
{
	command = s.command;
	parameters = s.parameters;
	values = s.values;

	return *this;
}

QString CCommand::toQString()
{
	QString S; 
	S.append(command);
	S.append(" ");
	for (int i = 0; i < values.count(); i++)
	{
		S.append("'" + values[i] +"'");
		S.append(" ");
	}
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
