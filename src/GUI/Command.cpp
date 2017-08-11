
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
	if (list.size() > 1)
	{
		QStringList param_list = list[1].split(",");
		for (int i = 0; i < param_list.size(); i++)
		{
			if (param_list[i].split("=").size() != 2)
				Validate_text = "Syntax error";
			else
			{
				parameters[param_list[i].split("=")[0].trimmed().toLower()] = param_list[i].split("=")[1].trimmed().split("[")[0];
				parameters[param_list[i].split("=")[0].trimmed().toLower()].unit = extract_in_between(param_list[i].split("=")[1].trimmed().toLower(), "[", "]");
			}
		}
	}
}

CCommand::CCommand(const CCommand & s)
{
	values = s.values;
	parameters = s.parameters;
	command = s.command;
	Validate_text = s.Validate_text;
}

CCommand& CCommand::operator=(const CCommand & s)
{
	command = s.command;
	parameters = s.parameters;
	values = s.values;
	Validate_text = s.Validate_text;

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
	S.append(":");
	int i = 0;
	for (QString key : parameters.keys())
	{
		S.append(key);
		S.append("=");
		S.append(parameters[key].toQString());
		if (parameters[key].unit != "")
		{
			S.append("[");
			S.append(parameters[key].unit);
			S.append("]");
		}
		if (i < parameters.size() - 1) S.append(",");
		i++;
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
