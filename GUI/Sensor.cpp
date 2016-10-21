#include "Sensor.h"


CSensor::CSensor()
{
}

CSensor::CSensor(int numberofExperiments)
{
	setNumberofExperiments(numberofExperiments);
}

CSensor::~CSensor()
{
}


CSensor::CSensor(const CSensor &M)
{
	name = M.name;
	loc_type = M.loc_type; //0: block, 1: connector
	quan = M.quan;
	id = M.id;
	error_structure = M.error_structure; //0: normal-additive, 1:lognormal-multiplicative
	error_std = M.error_std;
	interval = M.interval;
	output = M.output;
}

CSensor& CSensor::operator=(const CSensor &M)
{
	name = M.name;
	loc_type = M.loc_type; //0: block, 1: connector
	quan = M.quan;
	id = M.id;
	error_structure = M.error_structure; //0: normal-additive, 1:lognormal-multiplicative
	error_std = M.error_std;
	interval = M.interval;
	output = M.output;
	return *this;

}

void CSensor::append_output(double t, double C, int experiment_id)
{
	output[experiment_id].knock_out(t - interval / 10);
	output[experiment_id].append(t, C);
	return;
}