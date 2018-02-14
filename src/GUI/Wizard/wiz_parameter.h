#pragma once

#include <qstring.h>
#include "wiz_assigned_value.h"
#include <qmap.h>
#include "XString.h"
#include <vector>
#include <fstream>
#include "StringOP.h"

using namespace std; 
class Wizard_Script_Reader;

class wiz_parameter
{
public:
	wiz_parameter();
	wiz_parameter(const wiz_parameter &wiz_param);
	QString toQString();
	~wiz_parameter();
	wiz_parameter(QString &s, Wizard_Script_Reader *_parent);
	Wizard_Script_Reader *parent;
	bool getfromfile() { return fromfile; };
	
    QString get_name()
	{
		name = parameters["name"].value.trimmed();
		return name;
	}
    QString get_last_error()
	{
		return _last_error;
	}

    QString get_role()
	{
		return parameters["delegate"].value.trimmed(); 
	}

	bool get_bold()
	{
		if (parameters["bold"].value.trimmed() == "true") return true;
		if (parameters["Bold"].value.trimmed() == "true") return true;
		return false; 
	}

	wiz_assigned_value &get_parameter(const QString name)
	{
		return parameters[name];
	}

	QMap<QString, wiz_assigned_value> &get_parameters()
	{
		return parameters;
	}

    QString param_name()
	{
		name = parameters["name"].value.trimmed();
		return parameters["name"].value.trimmed();
	}

    QString get_question()
	{
		if (parameters["question"].value.trimmed() == "")
			parameters["question"].value = parameters["name"].value;

		return parameters["question"].value.replace("#",",");
	}

    XString get_value(int i=0, int j=0)
	{
		if (fromfile)
		{
			XString x;
			x = vals[i][j];
			return x; 
		}
		else
			return value;
	}

	void set_value(XString &val)
	{
		value = val;
	}

	bool get_vals_from_file(string filename)
	{
		ifstream file(filename);
		vector<string> s;
		
		if (file.good() == false)
		{
			_last_error = QString::fromStdString("file " + filename + " was not found");
			return false;
		}
		
		while (file.eof() == false)
		{
			s = getline(file);
			if (s.size())
				vals.push_back(ATOF(s));
		}
		fromfile = true; 
	}

private:
	QString name;
	XString value;
	QMap<QString, wiz_assigned_value> parameters;
	QString _last_error;
	bool fromfile = false;
	vector<vector<double>> vals;

};

