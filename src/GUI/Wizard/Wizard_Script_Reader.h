#pragma once

#include <qstring.h>
#include <qmap.h>
#include "Wizard/wiz_entity.h"
#include "Wizard/wiz_parameter.h"
#include "Wizard/wiz_parameter_group.h"
#include "Command.h"
#include "mProplist.h"

#define x_base 500
#define y_base 500
#define v_interval 120
#define h_interval 220
#define v_big_interval 180
#define h_big_interval 280

class Wizard_Script_Reader
{
public:
	mPropList *mproplist;
	QStringList script_specific_params;
	Wizard_Script_Reader();
	Wizard_Script_Reader(const Wizard_Script_Reader &WSR);
	QStringList toQStingList();
	Wizard_Script_Reader(QString filename);
	bool add_command(QString line);
	~Wizard_Script_Reader();
	CCommand get_script_commands_entities(wiz_entity * wiz_ent);
	CCommand get_script_commands_project_settings(wiz_entity * wiz_ent);
	QList<CCommand> get_script_commands_major_blocks(wiz_entity * wiz_ent, int & x, int & y);
		
	QMap<QString, wiz_entity> &get_major_blocks()
	{
		return major_blocks;
	}

	QMap<QString, wiz_entity> &get_entities()
	{
		return entities;
	}

	QMap<QString, wiz_entity> &get_major_connections()
	{
		return major_connections;
	}
	QMap<QString, wiz_entity> &get_project_settings()
	{
		return project_settings;
	}
	QMap<QString, wiz_parameter> &get_parameters()
	{
		return wiz_params;
	}
	QMap<QString, wiz_parameter_group> &get_parameter_groups()
	{
		return wiz_parameter_groups;
	}

	QString& get_script_name() { return script_name; };
	QString& get_script_icon() { return icon_file; };
	QList<CCommand> get_script_commands();
	QList<CCommand> get_script_commands_major_connections(wiz_entity * wiz_ent, int & x, int & y);
	XString get_parameter_value(QString & parameter_name);
	QList<CCommand> do_1dvh(QString configuration, wiz_entity * wiz_ent, int & x, int & y); //creates commands for a 1d grid object
	QList<CCommand> do_2dv(QString configuration, wiz_entity * wiz_ent, int & x, int & y); //creates commands for a 2d-vertical grid object
	QList<CCommand> do_2dh(QString configuration, wiz_entity * wiz_ent, int & x, int & y); //creates commands for a 2d-horizontal grid object
	private:
	QMap<QString, wiz_entity> major_blocks;
	QMap<QString, wiz_entity> major_connections;
	QMap<QString, wiz_entity> entities;
	QMap<QString, wiz_entity> project_settings;
	QMap<QString, wiz_parameter> wiz_params;
	QMap<QString, wiz_parameter_group> wiz_parameter_groups;
	QStringList error_list;
	QString script_name; 
	QString icon_file; 
	

};

