#include "Sensor.h"


CSensor::CSensor()
{
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
	for (int i = output[experiment_id].n-1; i >= 0; i--)
	{
		if (output[experiment_id].t[i] == t) output[experiment_id].C[i] = C;
		return;
	}
	output[experiment_id].append(t, C);
	return;
}