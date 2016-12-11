#pragma once
#include <string>
#include <vector>
using namespace std;

struct range //properties of unknown parameters
{
	string name;
	double low;
	double high;
	double value;
	vector<double> conversion_factor;
	double tempcorr;
	bool fixed;
	int param_no;
	bool log;
	bool applytoall;
	vector<int> location;
	vector<string> quan;
	vector<string> experiment_id;
	vector<int> location_type; //0: block, 1: connector; 2: both
};
QString float2date(const float d, QString format = "MMM dd yyyy");
qint64 xldate2julian(const qint64 xldate);

qint64 julian2xldate(const qint64 juliandate);
