#include "Wizard_Script_Reader.h"
#include "qfile.h"
#include "qmessagebox.h"
#include "qtextstream.h"
#include "qdatetime.h"
#include "utility_funcs.h"

Wizard_Script_Reader::Wizard_Script_Reader()
{
	script_specific_params << "configuration" << "type" << "name";
}

Wizard_Script_Reader::Wizard_Script_Reader(const Wizard_Script_Reader & WSR)
{
	error_list = WSR.error_list;
	icon_file = WSR.icon_file;
	major_blocks = WSR.major_blocks;
	major_connections = WSR.major_connections;
	project_settings = WSR.project_settings;
	script_name = WSR.script_name;
	entities = WSR.entities;
	script_specific_params = WSR.script_specific_params;
	wiz_parameter_groups = WSR.wiz_parameter_groups;
	wiz_params = WSR.wiz_params;
}

QStringList  Wizard_Script_Reader::toQStingList()
{
	QStringList out; 
	out << "script name = " + script_name;
	out << "icon file = " + icon_file;
	for (QString key : major_blocks.keys())
	{
		out << "major_block: " + major_blocks[key].toQString(); 
	}

	for (QString key : major_connections.keys())
	{
		out << "major_connection: " + major_connections[key].toQString();
	}

	for (QString key : entities.keys())
	{
		out << "entity: " + entities[key].toQString();
	}

	for (QString key : project_settings.keys())
	{
		out << "project setting: " + project_settings[key].toQString();
	}

	for (QString key : wiz_params.keys())
	{
		out << "parameter: " + wiz_params[key].toQString();
	}

	for (QString key : wiz_parameter_groups.keys())
	{
		out << "parameter_group: " + wiz_parameter_groups[key].toQString();
	}

	return out; 
}

Wizard_Script_Reader::Wizard_Script_Reader(QString filename)
{
	script_specific_params << "configuration" << "type" << "name";
	QFile file(filename); 
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox msgBox;
		msgBox.setText("File '" + filename + "' was not found");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
	}
	else
	{
		QTextStream wizard_stream(&file);
		while (!wizard_stream.atEnd())
		{
			add_command(wizard_stream.readLine());
		}
	}
	file.close();

}


bool Wizard_Script_Reader::add_command(QString line)
{
	if (line.split(":").size() == 1) return false;
	if (line.split(":")[0].toLower().trimmed() == "name") script_name = line.split(":")[1].trimmed();
	if (line.split(":")[0].toLower().trimmed() == "icon") icon_file = line.split(":")[1].trimmed();

	if (line.split(":")[0].toLower().trimmed() == "settings" || line.split(":")[0].toLower().trimmed() == "major_block" || line.split(":")[0].toLower().trimmed() == "major_connection" || line.split(":")[0].toLower().trimmed() == "entity")
	{
		wiz_entity entty(line, this); 
		if (entty.name() == "" & entty.entity() == "settings")
		{
			entty.name() = "settings_" + QString::number(project_settings.count());
			entty.get_last_error() = "";
		}

		if (entty.get_last_error() == "")
		{
			if (entty.entity() == "settings")
			{
				project_settings[entty.name()] = entty;
			}
			else if (entty.entity() == "major_block")
			{
				major_blocks[entty.name()] = entty;

			}
			else if (entty.entity() == "major_connection")
			{
				major_connections[entty.name()] = entty;
			}
			else if (entty.entity() == "entity")
			{
				entities[entty.name()] = entty;
			}

		}
		else
			error_list.append("Error in '" + line + "':" + entty.get_last_error());
			
	}
	else if (line.split(":")[0].toLower().trimmed() == "parameter")
	{
		wiz_parameter p(line, this); 
		if (p.get_last_error() == "")
			wiz_params[p.get_name()] = p;
		else
		{
			error_list.append("Parameter '" + p.get_name() + "':" + p.get_last_error());
		}
	}
	else if (line.split(":")[0].toLower().trimmed() == "parameter_group")
	{
		wiz_parameter_group pg(line, this);
		if (pg.get_last_error() == "")
			wiz_parameter_groups[pg.get_name()] = pg;
		else
		{
			error_list.append("Parameter group '" + pg.get_name() + "' :" + pg.get_last_error());
		}
	}

}

Wizard_Script_Reader::~Wizard_Script_Reader()
{
}


CCommand Wizard_Script_Reader::get_script_commands_entities(wiz_entity *wiz_ent)
{
	CCommand command; 
	command.command = "add";
	command.values.append(wiz_ent->type());

	mProp _filter;
	_filter.setstar();
	_filter.GuiObject = "Entity";
	_filter.ObjectType = wiz_ent->type();
	_filter.SubType = wiz_ent->subtype();
	mPropList m = mproplist->filter(_filter);

	for (wiz_assigned_value item : wiz_ent->get_parameters())
	{
		command.parameters["Name"] = wiz_ent->name();
		if (!script_specific_params.contains(item.entity))
		{
			if (m.VariableNames_w_abv().contains(item.entity))
				command.parameters[item.entity] = wiz_ent->get_value(item);
			if (item.entity.toLower()=="rate" || item.entity.toLower().left(4)=="stch")
				command.parameters[item.entity] = wiz_ent->get_value(item);
		}
	}
	
	return command; 

}

CCommand Wizard_Script_Reader::get_script_commands_project_settings(wiz_entity *wiz_ent)
{
	CCommand command;
	command.command = "setprop";
	command.values.append(wiz_ent->type());

	mProp _filter;
	_filter.setstar();
	_filter.GuiObject = "Entity";
	_filter.ObjectType = wiz_ent->type();
	_filter.SubType = wiz_ent->subtype();
	mPropList m = mproplist->filter(_filter);

	for (wiz_assigned_value item : wiz_ent->get_parameters())
	{
		if (!script_specific_params.contains(item.entity))
		{
			_filter.VariableName = item.entity;
			mPropList m1 = m.filter(_filter);
			if (m.VariableNames_w_abv().contains(item.entity))
			{
				if (m1[0].Delegate != "DateTime")
					command.parameters[item.entity] = wiz_ent->get_value(item);
				else
				{
					QDateTime QDT = QDateTime::fromString(wiz_ent->get_value(item),"M/d/yyyy hh:mm AP");
					qDebug() << QDT << QDT.toString() << QDT.isValid();
					command.parameters[item.entity] = QString::number(QDate2Xldate(QDT)); 
				}
			}
		}
	}

	return command;
}

QList<CCommand> Wizard_Script_Reader::get_script_commands_major_blocks(wiz_entity *wiz_ent, int &x, int &y)
{
	QList<CCommand> commands;
	
	QString configuration = wiz_ent->get_configuration().toLower();
	QString direction = wiz_ent->get_direction();
	if (configuration == "")
	{
		int n = 1;
		CCommand command;
		command.command = "add";
		command.values.append(wiz_ent->type());

		mProp _filter;
		_filter.setstar();
		_filter.GuiObject = "Block";
		_filter.ObjectType = wiz_ent->type();
		mPropList m = mproplist->filter(_filter);

		for (wiz_assigned_value item : wiz_ent->get_parameters())
		{
			command.parameters["Name"] = wiz_ent->name();
			command.parameters["x"] = x;
			command.parameters["y"] = y;
			if (!script_specific_params.contains(item.entity))
			{
				if (m.VariableNames_w_abv().contains(item.entity))
					command.parameters[item.entity] = wiz_ent->get_value(item);
			}
		}
		commands.append(command);
		x += h_big_interval;
	}
	if ((configuration == "1dv") || (configuration == "1dh"))
	{
		commands.append(do_1dvh(configuration, wiz_ent, x, y));
	}
	if (configuration == "2dv")
	{
		commands.append(do_2dv(configuration, wiz_ent, x, y));
	}

	return commands; 
}


QList<CCommand> Wizard_Script_Reader::get_script_commands()
{
	int x, y;
	x = x_base; 
	y = y_base; 

	QList<CCommand> commands;
	
	for (QString key : get_project_settings().keys())
	{
		commands.append(get_script_commands_project_settings(&get_project_settings()[key]));
	}
	for (QString key : get_major_blocks().keys())
	{
		commands.append(get_script_commands_major_blocks(&get_major_blocks()[key],x,y));
	}
	for (QString key : get_major_connections().keys())
	{
		commands.append(get_script_commands_major_connections(&get_major_connections()[key], x, y));
	}
	for (QString key : get_entities().keys())
	{
		commands.append(get_script_commands_entities(&get_entities()[key]));
	}


	return commands; 

}

QList<CCommand> Wizard_Script_Reader::get_script_commands_major_connections(wiz_entity *wiz_ent, int &x, int &y)
{
	QList<CCommand> commands;

	QString configuration = wiz_ent->get_configuration();
	wiz_entity *source = &major_blocks[wiz_ent->get_parameter("source").value];
	wiz_entity *target = &major_blocks[wiz_ent->get_parameter("target").value];
	if (configuration == "e2s" || configuration == "s2e" || configuration == "s2s" || configuration == "e2e")
	{
		CCommand command;
		command.command = "connect";
		
		if (configuration.left(1)=="e")
		{ 
			if (source->get_value(source->get_parameter("n")).toInt() > 1)
				command.values.append(source->name() + " (" + QString::number(source->get_value(source->get_parameter("n")).toInt()) + ")");
			else
				command.values.append(source->name()); 
		}
		else if (configuration.left(1) == "s")
		{
			if (source->get_value(source->get_parameter("n")).toInt() > 1)
				command.values.append(source->name() + " (1)");
			else
				command.values.append(source->name());
		}
		if (configuration.right(1) == "e")
		{
			if (target->get_value(target->get_parameter("n")).toInt() > 1)
				command.values.append(target->name() + " (" + QString::number(target->get_value(target->get_parameter("n")).toInt()) + ")");
			else
				command.values.append(target->name());
		}
		else
		{
			if (target->get_value(target->get_parameter("n")).toInt() > 1)
				command.values.append(target->name() + " (1)");
			else
				command.values.append(target->name());

		}
		
		mProp _filter;
		_filter.setstar();
		_filter.GuiObject = "Connector";
		mPropList m = mproplist->filter(_filter);

		for (wiz_assigned_value item : wiz_ent->get_parameters())
		{
			if (!script_specific_params.contains(item.entity))
			{
				if (m.VariableNames_w_abv().contains(item.entity))
					command.parameters[item.entity] = wiz_ent->get_value(item);
				if (item.entity.toLower() == "area")
					command.parameters["Interface/cross sectional area"] = wiz_ent->get_value(item);
			}
		}
		commands.append(command);
	}
	if (configuration == "a2a")
	{
		int n_source = source->get_value(QString("n")).toInt();
		int n_target = target->get_value(QString("n")).toInt();
		if (n_source != n_target)
			error_list.append("Number of cells in source and target are different");
		else
		{
			for (int i = 0; i < n_source; i++)
			{
				CCommand command;
				command.command = "connect";
				command.values.append(source->name() + " ("+ QString::number(i+1) + ")");
				command.values.append(target->name() + " ("+ QString::number(i+1) + ")") ;
				
				mProp _filter;
				_filter.setstar();
				_filter.GuiObject = "Connector";
				mPropList m = mproplist->filter(_filter);

				for (wiz_assigned_value item : wiz_ent->get_parameters())
				{
					if (!script_specific_params.contains(item.entity))
					{
						if (m.VariableNames_w_abv().contains(item.entity))
							command.parameters[item.entity] = wiz_ent->get_value(item);
						if (item.entity.toLower() == "area")
							command.parameters["Interface/cross sectional area"] = wiz_ent->get_value(item);
					}
				}
				commands.append(command);

			}
		}

	}
	return commands; 
}

XString Wizard_Script_Reader::get_parameter_value(QString &parameter_name)
{
	return get_parameters()[parameter_name].get_value();
}

QList<CCommand> Wizard_Script_Reader::do_1dvh(QString configuration, wiz_entity *wiz_ent, int &x, int &y)
{
	
	QList<CCommand> commands;
	QString direction = wiz_ent->get_direction();
	
	int n = wiz_ent->get_value(wiz_ent->get_parameter("n")).toInt();
	
	double z0 = 0;
	double Depth;
	double length = wiz_ent->get_value(wiz_ent->get_parameter("Length")).toDouble();
	double width = wiz_ent->get_value(wiz_ent->get_parameter("Width")).toDouble();
	double slope = wiz_ent->get_value(wiz_ent->get_parameter("Slope")).toDouble();
	bool has_z0 = false;
	bool has_depth = false;
	if (wiz_ent->has_parameter("Bottom elevation"))
	{
		z0 = wiz_ent->get_value(wiz_ent->get_parameter("Bottom elevation")).toDouble();
		has_z0 = true;
	}
	if (wiz_ent->has_parameter("Depth"))
	{
		Depth = wiz_ent->get_value(wiz_ent->get_parameter("Depth")).toDouble();
		has_depth = true;
	}

	mProp _filter;
	_filter.setstar();
	_filter.GuiObject = "Block";
	_filter.ObjectType = wiz_ent->type();
	mPropList m = mproplist->filter(_filter);

	for (int i = 0; i < n; i++)
	{
		CCommand command;
		command.command = "add";
		command.values.append(wiz_ent->type());
		if (n > 1)
			command.parameters["Name"] = XString(wiz_ent->name() + " (" + QString::number(i + 1) + ")");
		else
			command.parameters["Name"] = XString(wiz_ent->name());

		command.parameters["x"] = x;
		command.parameters["y"] = y;
		if (configuration == "1dv")
		{
			if (direction == "up")
				y -= v_interval;
			else
				y += v_interval;
		}
		else if (configuration == "1dh")
		{
			if (direction == "right")
				x += h_interval;
			else
				x -= h_interval;
		}
		for (wiz_assigned_value item : wiz_ent->get_parameters())
		{
			if (!script_specific_params.contains(item.entity))
			{
				if (m.VariableNames_w_abv().contains(XString::reform(item.entity)))
					command.parameters[item.entity] = wiz_ent->get_value(item);
			}
		}
		if (has_depth)
		{
			if (configuration == "1dv")
			{
				if (direction == "down")
					command.parameters["Bottom elevation"] = z0 + (n - i - 1)*Depth;
				else
					command.parameters["Bottom elevation"] = z0 + i*Depth;
			}
		}
		if (configuration == "1dh")
			command.parameters["Bottom elevation"] = z0 - i*length*slope;

		commands.append(command);

	}

	for (int i = 0; i < n - 1; i++)
	{
		CCommand command;
		command.command = "connect";
		command.values.append(wiz_ent->name() + " (" + QString::number(i + 1) + ")");
		command.values.append(wiz_ent->name() + " (" + QString::number(i + 2) + ")");
		mProp _filter;
		_filter.setstar();
		_filter.GuiObject = "Connector";
		mPropList m = mproplist->filter(_filter);

		command.parameters["Name"] = XString(wiz_ent->name() + " (" + QString::number(i + 1) + ") - " + wiz_ent->name() + " (" + QString::number(i + 2) + ")");
		if (has_depth && configuration == "1dv") command.parameters["Length"] = Depth;
		if (has_depth && configuration == "1dh") command.parameters["Length"] = length;
		for (wiz_assigned_value item : wiz_ent->get_parameters())
		{
			if (!script_specific_params.contains(item.entity))
			{
				if (m.VariableNames_w_abv().contains(item.entity))
					command.parameters[item.entity] = wiz_ent->get_value(item);
				if (item.entity.toLower() == "bottom area" && configuration == "1dv")
					command.parameters["Interface/cross sectional area"] = wiz_ent->get_value(item);

			}
		}

		if (configuration == "1dh")
			command.parameters["Interface/cross sectional area"] = width*Depth;

		commands.append(command);

	}

	if (configuration == "1dv")
	{
		y = y_base;
		x += h_big_interval;
	}
	else if (configuration == "1dh")
	{
		x = x_base;
		y += v_big_interval;
	}

	return commands; 
}

QList<CCommand> Wizard_Script_Reader::do_2dv(QString configuration, wiz_entity *wiz_ent, int &x, int &y)
{
	QList<CCommand> commands;
	QString direction = wiz_ent->get_direction();

	int nh = wiz_ent->get_value(wiz_ent->get_parameter("nh")).toInt();
	int nv = wiz_ent->get_value(wiz_ent->get_parameter("nv")).toInt();

	double z0 = 0;
	double Depth;
	double length = wiz_ent->get_value(wiz_ent->get_parameter("Length")).toDouble();
	double Width = wiz_ent->get_value(wiz_ent->get_parameter("Width")).toDouble();
	double slope = wiz_ent->get_value(wiz_ent->get_parameter("Slope")).toDouble();
	bool has_z0 = false;
	bool has_depth = false;
	if (wiz_ent->has_parameter("Bottom elevation"))
	{
		z0 = wiz_ent->get_value(wiz_ent->get_parameter("Bottom elevation")).toDouble();
		has_z0 = true;
	}
	if (wiz_ent->has_parameter("Depth"))
	{
		Depth = wiz_ent->get_value(wiz_ent->get_parameter("Depth")).toDouble();
		has_depth = true;
	}

	mProp _filter;
	_filter.setstar();
	_filter.GuiObject = "Block";
	_filter.ObjectType = wiz_ent->type();
	mPropList m = mproplist->filter(_filter);
	
	for (int i = 0; i < nh; i++)
	{
		for (int j = 0; j < nv; j++)
		{
			CCommand command;
			command.command = "add";
			command.values.append(wiz_ent->type());

			command.parameters["Name"] = XString(wiz_ent->name() + " (" + QString::number(i + 1) + "," + QString::number(j + 1) + ")");


			command.parameters["x"] = x;
			command.parameters["y"] = y;

			if (direction == "up")
				y -= v_interval;
			else
				y += v_interval;


			for (wiz_assigned_value item : wiz_ent->get_parameters())
			{
				if (!script_specific_params.contains(item.entity))
				{
					if (m.VariableNames_w_abv().contains(XString::reform(item.entity)))
						command.parameters[item.entity] = wiz_ent->get_value(item);
				}
			}
			if (has_depth)
			{
				{
					if (direction == "down")
						command.parameters["Bottom elevation"] = z0 + (nv - j - 1)*Depth;
					else
						command.parameters["Bottom elevation"] = z0 + j*Depth;
				}
			}


			commands.append(command);

		}
		x += h_interval;
		y = y_base;
		z0 -= slope*length;
	}
	
	for (int i = 0; i < nh-1; i++)
	{
		for (int j = 0; j < nv; j++)
		{
			CCommand command;
			command.command = "connect";
			command.values.append(wiz_ent->name() + " (" + QString::number(i + 1) + "," + QString::number(j + 1) + ")");
			command.values.append(wiz_ent->name() + " (" + QString::number(i + 2) + "," + QString::number(j + 1) + ")");
			mProp _filter;
			_filter.setstar();
			_filter.GuiObject = "Connector";
			mPropList m = mproplist->filter(_filter);

			command.parameters["Name"] = XString(wiz_ent->name() + " (" + QString::number(i + 1) + "," + QString::number(j + 1) + ") - " + wiz_ent->name() + " (" + QString::number(i + 2) + "," + QString::number(j + 1) + ")");
			
			
			for (wiz_assigned_value item : wiz_ent->get_parameters())
			{
				if (!script_specific_params.contains(item.entity))
				{
					if (m.VariableNames_w_abv().contains(item.entity))
						command.parameters[item.entity] = wiz_ent->get_value(item);
				}
			}

			command.parameters["Length"] = length;
			command.parameters["Interface/cross sectional area"] = Width*Depth;

			commands.append(command);

		}
	}

	for (int i = 0; i < nh; i++)
	{
		for (int j = 0; j < nv-1; j++)
		{
			CCommand command;
			command.command = "connect";
			command.values.append(wiz_ent->name() + " (" + QString::number(i + 1) + "," + QString::number(j + 1) + ")");
			command.values.append(wiz_ent->name() + " (" + QString::number(i + 1) + "," + QString::number(j + 2) + ")");
			mProp _filter;
			_filter.setstar();
			_filter.GuiObject = "Connector";
			mPropList m = mproplist->filter(_filter);

			command.parameters["Name"] = XString(wiz_ent->name() + " (" + QString::number(i + 1) + "," + QString::number(j + 1) + ") - " + wiz_ent->name() + " (" + QString::number(i + 1) + "," + QString::number(j + 2) + ")");
			
			for (wiz_assigned_value item : wiz_ent->get_parameters())
			{
				if (!script_specific_params.contains(item.entity))
				{
					if (m.VariableNames_w_abv().contains(item.entity))
						command.parameters[item.entity] = wiz_ent->get_value(item);
				}
			}
			command.parameters["Length"] = Depth;
			commands.append(command);

		}
	}

	y = y_base;
	x += h_big_interval;

	return commands;
	
}