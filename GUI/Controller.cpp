#include "Controller.h"
#include "StringOP.h"

enum controller_param {k_p, k_i, k_d, setpoint, k_u, T_u};
enum controller_type { P = 0, PI = 1, PD = 2, PID = 3, PID_NoOvershoot = 4 };

CController::CController()
{
	params.resize(10);
	value = 0;
}


CController::~CController()
{
}

CController::CController(const CController &M)
{
	name = M.name;
	params = M.params;
	type = M.type;
	sensor_id = M.sensor_id;
	value = M.value;
	interval = M.interval;
	min_val = M.min_val;
	max_val = M.max_val;
	output = M.output;
	zn_controller_type = M.zn_controller_type;
}

CController& CController::operator=(const CController &M)
{
	params = M.params;
	name = M.name;
	type = M.type;
	sensor_id = M.sensor_id;
	value = M.value;
	interval = M.interval;
	min_val = M.min_val;
	max_val = M.max_val;
	output = M.output;
	zn_controller_type = M.zn_controller_type;
	return *this;

}

double CController::calc_value(double t, int experiment_id)
{
	value += params[k_p] * ( P(t, experiment_id) + params[k_i] * I(t, experiment_id) + params[k_d] * D(t, experiment_id));
	value = min(value, max_val);
	value = max(value, min_val);
	append(t, value);
	return value;
}


void CController::append(double t, double C)
{
	for (int i = output.n - 1; i >= 0; i--)
	{
		if (output.t[i] == t) output.C[i] = C;
	}
	output.append(t, C);
	return;

}

double CController::P(double t, int experiment_id)
{
	if (tolower(type) == "pid")
		return (Sensor->output[experiment_id].interpol(t) - params[3]);

}
double CController::I(double t, int experiment_id)
{
	if (tolower(type) == "pid")
		return (Sensor->output[experiment_id].integrate(t) - params[3]*(t-Sensor->output[experiment_id].t[0]));

}
double CController::D(double t, int experiment_id)
{
	if (tolower(type) == "pid")
		if (Sensor->output[experiment_id].n > 1)
			return (Sensor->output[experiment_id].slope(t));
		else
			return 0;


}

void CController::set_val(string S, double val)
{
	if ((tolower(S) == "kp") || (tolower(S) == "k_p")) params[k_p] = val;
	if ((tolower(S) == "ki") || (tolower(S) == "k_i")) params[k_i] = val;
	if ((tolower(S) == "kd") || (tolower(S) == "k_d")) params[k_d] = val;
	if ((tolower(S) == "value") || (tolower(S) == "inivalue")) value = val;
	if (tolower(S) == "interval") interval = val;
	if ((tolower(S) == "min_value") || (tolower(S) == "min")) min_val = val;
	if ((tolower(S) == "max_value") || (tolower(S) == "max")) max_val = val;
	if ((tolower(S) == "set_point") || (tolower(S)=="setpoint")) params[setpoint] = val;
	if ((tolower(S) == "k_u") || (tolower(S) == "setpoint")) params[k_u] = val;
	if ((tolower(S) == "T_u") || (tolower(S) == "setpoint")) params[T_u] = val;


}