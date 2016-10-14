#pragma once
#include "qstring.h"
#include <vector>
#include "qcolor.h"
#include "qrgb.h"
#include "btc.h"

using namespace std;
struct colorlegend
{
	vector<QColor> colors;
	vector<QString> legends;
};
class colorScheme
{
public:
	colorScheme() {
	}
	~colorScheme(){}
	int numberofColors() {
		return colors.size();
	}
	std::vector<QColor> colors;
	void setColorTheme(QString theme) {
		colorTheme = theme;
		//do something on vector
	}
	QString currentColorTheme() {
		return colorTheme;
	}
	void setLogType(bool logType) {
		this->logType = logType;
	}
	QString currentLogType() {
		return (logType) ? "Logged" : "Normal";
	}
	static vector<QColor> color(vector<CBTC> data, float t, QString theme = "Green", bool logType = false, int numberofGroups = 8, vector<double> factors = vector<double>(), vector<double> shifts = vector<double>()) {
		vector<QColor> colors(numberofGroups);
		bool factor = factors.size();
		bool shift = shifts.size();

		if (theme == "Green")
			for (int i = 0; i < numberofGroups; i++)
				colors[i] = QColor::fromRgb(0, i * 255 / numberofGroups, 0, 128);
		float min=-1e100, max=1e100;
		vector<QColor> r(data.size());
		vector <double> values(data.size());

		for (int i = 0; i < data.size(); i++)
		{
			values[i] = data[i].interpol(t);
			if (factor)
				values[i] *= factors[i];
			if (shift)
				values[i] += shifts[i];
		}
		//updating min, max
		for (int i = 0; i < data.size(); i++)
		{
			if (values[i] < min) min = values[i];
			if (values[i] > max) max = values[i];
		}
		for (int i = 0; i < data.size(); i++)
		{
			int g;
			if (values[i] == max)
				g = numberofGroups - 1;
			else 
				g = (min - values[i]) / (max - min) * (numberofGroups);
			r[i] = colors[g];
		}
		return r;
	}
	
	static colorlegend colorandLegend(vector<CBTC> data, float t, QString theme = "Green", bool logType = false, int numberofGroups = 8, vector<float> factors = vector<float>(), vector<float> shifts = vector<float>()) {
		colorlegend r;
		vector<QColor> colors(numberofGroups);
		bool factor = factors.size();
		bool shift = shifts.size();

		if (theme == "Green")
			for (int i = 0; i < numberofGroups; i++)
			{
				QColor c = QColor(0, i * 255 / numberofGroups, 0, 128);
				r.colors[i] = c.toRgb();
			}
		float min = -1e100, max = 1e100;

		r.colors.resize(data.size());
		r.legends.resize(data.size());
		vector <double> values(data.size());

		for (int i = 0; i < data.size(); i++)
		{
			values[i] = data[i].interpol(t);
			if (factor)
				values[i] *= factors[i];
			if (shift)
				values[i] += shifts[i];
		}
		//updating min, max
		for (int i = 0; i < data.size(); i++)
		{
			if (values[i] < min) min = values[i];
			if (values[i] > max) max = values[i];
		}

		//updatring legend
		for (int i = 0; i < numberofGroups; i++)
		{
			float groupRange = (max - min) / numberofGroups;
			r.legends[i] = QString ("%1-%2").arg(min + groupRange *i).arg(min + groupRange *(i+1));
		}
		for (int i = 0; i < data.size(); i++)
		{
			int g;
			if (values[i] == max)
				g = numberofGroups - 1;
			else
				g = (min - values[i]) / (max - min) * (numberofGroups);
			r.colors[i] = colors[g];
		}
		return r;
	}
private:
	QString colorTheme;
	bool logType;
};