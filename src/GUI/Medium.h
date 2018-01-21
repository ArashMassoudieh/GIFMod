#pragma once
#ifdef GIFMOD
#include "Connection.h"
#include "MBBlock.h"
#include <vector>
#include "Vector.h"
#include "Matrix.h"
#include "BTCSet.h"
#include "string.h"
#include "LIDconfig.h"
#include "Precipitation.h"
#include "Solid_Phase.h"
#include "RxnNetwork.h"
#include "Buildup.h"
#include "RestoreInfo.h"
#include "Evaporation.h"
#include "Sensor.h"
#include "utility_funcs.h"
#include "ObjectiveFunction.h"
#include "Vector_arma.h"
#include "Matrix_arma.h"


#ifdef QT_version
#include "qstring.h"
#endif // QT_version

class GraphWidget;
class QProgressBar;
class runtimeWindow;

using namespace std;



struct measured_chrc //Properties of observed data
{
	string name;
	int loc_type; //0: block, 1: connector
	string quan;
	vector<string> id;
	int std_no;
	int error_structure; //0: normal-additive, 1:lognormal-multiplicative
	int std_to_param;
	string experiment;
};

class CMediumSet;

enum formulas
	{
		Pipe1, Pipe2, QDarcy, Vapor, Normal, Rating_curve
	};

class CMedium
{
public:
	
	string name;
	CMediumSet *parent;
	CMedium(void);
	~CMedium(void);
	CMedium(const CMedium &M);
	CMedium(string filename, CMediumSet *P = 0);
	CMedium(CLIDconfig _lid_config, CMediumSet *_parent = 0);
    void create(CLIDconfig _lid_config, CMediumSet *_parent);
	double& w(); //current time weight for CN solution
    CMedium& operator=(const CMedium &BB); //equal operator
	void get_state(const CMedium & M);
	
	vector<CSolid_Phase>& Solid_phase();
    void add_Richards_medium(int n, double dz, int id=-1);
    void add_Darcy_medium(int n, double dz,  int id=-1);
    void add_stream_medium(int n, double z0, double slope, double lenght, int id=-1);
    void add_catchment_medium(int n, double z0, double slope, double lenght, int id=-1);
    void add_KW_medium(int n, double dz, vector<double> params);
    void add_KW_medium(int n, double dz);
    void set_num_phases(int n);
    void set_num_constituents(int n);
    void set_var(int i, double v);
    void set_var(const string &S, const double &v);
    void set_var(const string &S, const vector<double> &v);
    void set_var(const string &S, const double &v, const int&, const int&);
    void set_var(const string &S, const vector<double> &v, const int&, const int&);
    void set_var(const string &S, const double &v, const int&);
    void set_var(const string &S, const vector<double> &v, const int&);
    void set_var(const string &S, int i, const double &v);
    void set_z0(double down, double up);
    void set_z0(double down);
    void set_z0(int id, int n, double z0, double dz);
    void setS_star(const CVector &X);
    void setS_star(CVector_arma &X);
    void set_G_star(const CVector &X);

    void setH_star();
    void setH();
    void setQ_star();
    void setQ();
    void setQ(const CVector &X);
    void setQ0();
    double get_var(int i, string j, int k); //i: type (i.e. connector vs. block), j: ID, k: variable ID
    double get_var(int i, string j, string k); //i: ID, j: type (i.e. connector vs. block), k: variable
    CVector get_val(string I, int j);
    double get_var(int i, vector<string> j, int k);
    double get_var(int i, vector<string> j, string k);
    double calc_term(int i, string loc_id, CStringOP k);
    double calc_term_star(int i, string loc_id, CStringOP k);
    CVector getS();
    CVector getres_S(const CVector &X, double dt);
    CVector getres_C(const CVector &X, double dt);
    CVector getres_Q(const CVector &X, double dtt);

    CMatrix Jacobian_S(const CVector &X, double dt, bool);
    CVector Jacobian_S(const CVector &V, int &i, double &dt);
    CVector Jacobian_S(const CVector &V, CVector &F0, int i, double dt);
    CMatrix Jacobian_C(const CVector &X, double dt, bool base=true);
    CVector Jacobian_C(const CVector &V, const int i, double dt);
    CVector Jacobian_C(const CVector &V, const CVector &F0, int i, double dt);
    CMatrix Jacobian_Q(const CVector &X, double dt, bool base=true);
    CVector Jacobian_Q(const CVector &V, int i, double dt);
    CVector Jacobian_Q(const CVector &V, const CVector &F0, int i, double dt);

	CVector getLAI();

	CVector getV();

	//use arma
    CVector_arma getres_S(CVector_arma &X, double dt);
    CVector_arma getres_C(CVector_arma &X, double dt);
    CVector_arma getres_Q(CVector_arma &X, double dtt);
    CMatrix_arma Jacobian_S(CVector_arma &X, double dt, bool);
    CVector_arma Jacobian_S(CVector_arma &V, int &i, double &dt);
    CVector_arma Jacobian_S(CVector_arma &V, CVector_arma &F0, int i, double dt);
    CMatrix_arma Jacobian_C(CVector_arma &X, double dt, bool base = true);
    CVector_arma Jacobian_C(CVector_arma &V, const int i, double dt);
    CVector_arma Jacobian_C(CVector_arma &V, const CVector_arma &F0, int i, double dt);
    CMatrix_arma Jacobian_Q(CVector_arma &X, double dt, bool base = true);
    CVector_arma Jacobian_Q(CVector_arma &V, int i, double dt);
    CVector_arma Jacobian_Q(CVector_arma &V, const CVector_arma &F0, int i, double dt);

    void set_CG_star(CVector_arma &X);
    void set_CG(CVector_arma &X);
    void set_G(CVector_arma &X);
    void set_G_star(CVector_arma &X);

	void write_flows(string filename);

	vector<int> infnan_H_blocks();

	vector<int> infnan_H_flows();

    void onestepsolve_flow_ar(double dt);
    void onestepsolve_colloid_ar(double dt);
    void onestepsolve_const_ar(double dtt);
	//use arma

    CVector getH(const CVector &X);
    CVector getQ(const CVector &X);
    void onestepsolve_flow(double dt);
    void onestepsolve_colloid(double dt);
    void onestepsolve_const(double dtt);
	void do_plant_growth(double dtt);
    void solve_fts_m2(double dt);

//Sassan
//	bool solve();
    void renew();
    void renew_G();
    void renew_CG();
    void initialize();
	double& tol();
	CBTCSet ANS; //Solution containing all the outputs
	CBTCSet ANS_colloids; //Solution containing all the outputs for colloidal phases
	CBTCSet ANS_constituents; //Solution containing all the outputs for chemical constituents
	CBTCSet ANS_obs; //Solutions containing correspondents to the observed data
	CBTCSet ANS_obs_noise; ////Solutions containing correspondents to the observed data with added noise
	CBTCSet ANS_MB;//mass balance check timeseries
	CBTCSet ANS_control; //control outputs
	CBTCSet Solution_dt;
	double Timemin,Timemax;
	CLIDconfig lid_config;
	double& dt();
	vector<range>& parameters(); // properties of unknown parameters
	vector<CSensor>& sensors(); // properties of sensors
	vector<CController>& controllers(); //propoerties of controllers;
	vector<CObjectiveFunction>& objective_functions(); //objective functions for control;
    void getparams(string filename);
	vector<measured_chrc>& measured_quan();
	vector<double>& std(); // the vector of measured error standard deviations
	CBTCSet& measured_data(); //measured data
	string& pathname(); //pathname of where the files are saved
	string& outputpathname(); //pathname of where the files are saved
    double calc_log_likelihood(); //calculate sum log likelihood
    double calc_log_likelihood(int i); //calculate sum log likelihood for observed quantity i
    void set_param(int param_no, double value); //set the value of an unknown parameter
    void finalize_set_param();
    void set_default_params(); //set the value of the parameters to the default values
	int& solution_method(); //0: Fixed timestep 1: variable timestep
	string& PE_info_filename(); //file name containing parameter estimation configuration
	string detoutfilename_hydro; //file name where the deterministic hydraulic output is saved
	string detoutfilename_wq; //file name where the deterministic water quality output is saved
	string detoutfilename_control; //file name where the controller values are saved
	string detoutfilename_prtcle; //file name where the deterministic partcile output is saved
	string& detoutfilename_obs(); ////file name where the deterministic outputs corresponding to the observed data is saved
	int& writeinterval(); //the interval at which the output are save in output files (default = 1)
	string& realizeparamfilename(); //output file name for Monte-Carlo realizations
	double& minimum_acceptable_negative_conc(); //returns the minimum acceptable negative concentration criteria
	double t; // time
	int counter_flow, counter_colloid, counter_const; // counter for number of iteration
    void Blocksmassbalance();
	vector<string> Precipitation_filename;
	vector<CPrecipitation> Precipitation;

	//vector<string> Evaporation_filename;
	//vector<CBTC> Evaporation;

	int& nr_iteration_treshold_max();
	int &nr_iteration_treshold_min();
	double& dt_change_rate();
	double& dt_change_failure();
	int& nr_failure_criteria();
	bool &sorption();
	int n_default_phases; //number of aquesous/soil matrix phases =1 for solely aqueous =2 when sorption to soil matrix occures
	bool failed;
	CMatrix InvJ1; //Inverse Jacobian Matrix
	CMatrix InvJ2; //Inverse Jacobian Matrix
	CMatrix InvJ_C;
	CMatrix InvJ_Q;

	//arma
	CMatrix_arma InvJ1_arma; //Inverse Jacobian Matrix
	CMatrix_arma InvJ2_arma; //Inverse Jacobian Matrix
	CMatrix_arma InvJ_C_arma;
	CMatrix_arma InvJ_Q_arma;
	//arma

	bool J_update,J_update_C, J_update_Q;
	int& max_J_interval();
	double cr;
	double dt0;
	vector<string>& formulas();
	vector<string>& formulasH();
	vector<vector<string>>& formulasQ();
	vector<vector<string>>& formulasQ2();
	vector<vector<string>>& formulasA();
	vector<vector<bool>>& const_area();
	vector<bool>& air_phase();
	vector<vector<bool>>& vaporTransport();
	vector<vector<bool>>& settling();
    void get_funcs();
    void evaluate_functions();
    int getblocksq(string id);
    int getconnectorsq(string id);
	bool& write_details();
    bool is_there_any_fixed_connectors();
	double& wiggle_tolerance();
    CVector get_flow_factors();
    void set_flow_factors(CVector &X);
    vector<int> get_fixed_connect_status();
    void set_fixed_connect_status(vector<int> X);
    void set_block_fluxes();
    void evaluate_K();
    void evaluate_K_star();
    void evaluate_dispersion();
    void evaluate_capacity();
    void evaluate_capacity_star();
    void evaluate_capacity_c();
    void evaluate_capacity_c_star();
    void evaluate_area(bool all=false);

    void correct_S(double dtt);
	bool failed_colloid;
	bool failed_const;
	double pos_def_ratio;
	double pos_def_ratio_const;
	bool& uniformoutput();
	bool& mass_balance_check();
	bool& colloid_transport();
	bool& constituent_transport();
	bool& forward();
	int& epoch_limit();

	int epoch_count;
	double& avg_dt_limit();
	CMatrix M;
	CMatrix_arma M_arma;
	string fail_reason;

    void write_state(string filename);
    void read_state(string filename);
	int& restore_interval();
	double dtt;
	double base_dtt;
	int where_base_dtt_changed = 0;
	double avg_redo_dtt=0;
	int redo_count = 0;
    int get_member_no(int solid_id, int phase_no);
    int get_member_no(int block_no, int solid_id, int phase_no);
    int get_member_no(int block_no, int solid_id, int phase_no, int const_no);
    double get_capacity(int block_no, int phase_no, int particle_no);
    double get_capacity_star(int block_no, int phase_no, int particle_no);
    vector<int> get_phase_solid_id(int i);
	CRxnNetwork& RXN();
    void evaluate_const_dispersion();
    void set_CG_star(const CVector &X);
    void set_CG(const CVector &X);
    void set_G(const CVector &X);
    CVector get_X_from_CG();
    CVector get_X_from_G();
    void set_default();
	CMatrix M_Q;
	CMatrix M_C;
	CMatrix_arma M_Q_arma;
	CMatrix_arma M_C_arma;
	string& log_file_name();

    void f_get_environmental_params();
    void f_get_model_configuration();
    void f_set_default_connector_expressions();
    void f_set_default_block_expressions();
    void f_load_inflows();
    void f_make_uniform_inflows();


    CVector get_rxn_chng_rate();

	vector<CBuildup>& buildup();
	vector<CEnvExchange>& externalflux();
	vector<CEvaporation>& evaporation_model();

	double dtt_J_h1, dtt_J_h2, dtt_J_q, dtt_J_c;
	int J_h_update_count, J_q_update_count, J_c_update_count;
    void writedetails();
	double pos_def_mult;
	double pos_def_mult_Q;
	double max_wiggle, wiggle_dt_mult, dt_fail, max_wiggle_id;

	int lookup_blocks(string S);
	int lookup_connectors(string S);
	int lookup_external_flux(string S);
    int lookup_particle_type(string S);
    int lookup_buildup(string S);
    int lookup_evaporation(string S);
    int lookup_parameters(string S);
    int lookup_sensors(string S);
    int lookup_controllers(string S);
    int lookup_objective_functions(string S);
//	int lookup_observation(string S);

    void writetolog(string S);
	CMatrix Preconditioner_Q;
	CMatrix Preconditioner_C;
	CMatrix Preconditioner_S;
	CMatrix_arma Preconditioner_Q_arma;
	CMatrix_arma Preconditioner_C_arma;
	CMatrix_arma Preconditioner_S_arma;
	bool& pos_def_limit();
	double& maximum_run_time();
    bool& check_oscillation();
	bool& negative_concentration_allowed();

    CRestoreInfo getrestoreinfo();
    void doredo(CRestoreInfo &R);
	vector<CBTC> temperature;
	vector<string> temperature_filename;
	vector<CBTC> light;
	vector<string> light_filename;
	vector<CBTC> wind;
	vector<string> wind_filename;
	vector<CBTC> r_humidity;
	vector<string> r_humidity_filename;


	void update_rxn_params();
	double current_light;
	double current_temperature;
	double current_wind;
	double current_relative_humidity;
	void update_light_temperature();
	void update_wind_humidity();
	double get_nextcontrolinterval(double _t);
	void set_control_params(int);
#ifdef QT_version
	QString solution_detail;
#else
	string solution_detail;
#endif // QT_version
	void clear(); //clear the model

#ifdef QT_version
//	void g_get_params();
//	void g_get_observed();
    void g_get_environmental_params();
    void g_get_model_configuration(runtimeWindow* = 0);
//	void g_get_particle_types();
//	void g_get_constituents();
//	void g_get_reactions();
    void g_set_default_connector_expressions();
    void g_set_default_block_expressions();
//	void g_get_buildup();
//	void g_get_external_flux();
    void g_load_inflows();
//	void g_get_evapotranspiration();
    void warning(QString text);

	//CMedium(GraphWidget *, runtimeWindow * = 0);
	GraphWidget *gw;
#endif // QT_version
    bool solve();
	bool solved() { return !this->failed; }
#ifdef QT_version
    int get_member_no(QString block_name, QString solid_name, QString phase_name);
    int get_member_no(QString block_name, QString solid_name, QString phase_name, QString const_name);
    void updateProgress(bool finished = false);
#endif // QT_version
	runtimeWindow * runtimewindow = 0;
	bool stop_triggered = false;
    vector<string> get_everything_from_id(int x);
    vector<CRestoreInfo> clean_up_restore_points(vector<CRestoreInfo> &Res, double t);

	//Bioest
    void onestepsolve_flow_bioest(double dtt);
    double getflow(int connector_ID);
    vector<int> get_num_block_unpres_inflows(int connector_ID);
	bool& steady_state_hydro();
	double& max_dt();
	void false_connector_flow_calc();
	CMatrix hydro_steady_matrix_inv;
	string create_hydro_steady_matrix_inv();
	CVector get_steady_hydro_RHS();
    vector<int> get_member_no_inv(int i);
    vector<int> get_relevant_measured_quans();
    int lookup_experiment(string S);

	int blocks_count() { return (int)Blocks.size(); };
	int connectors_count() { return (int)Connectors.size(); };
	CMBBlock& Block(int i)
	{
		if (Blocks.size() > i) 
			return Blocks[i]; 
		else 
			error = error + "Block " + numbertostring(i) + " was not found";
	
	}

	CConnection& Connector(int i)
	{
		if (Connectors.size() > i)
			return Connectors[i];
		else
			error = error + "Connector " + numbertostring(i) + " was not found";

	}

	CMBBlock& Block(string blockname)
	{
		int out = lookup_blocks(blockname);
		if (out == -1)
			error = error + "Block " + blockname + " does not exist";
		else
			return Blocks[out];

	}

	CConnection& Connector(string connectorname)
	{
		int out = lookup_connectors(connectorname);
		if (out == -1)
			error = error + "Connector " + connectorname + " does not exist";
		else
			return Connectors[out];

	}

	void clear_blocks() { Blocks.clear(); };
	void clear_connectors() { Connectors.clear(); };
	// Control
    double calc_obj_function(double time_interval);
private:
	bool use_arma = true;
	vector<CConnection> Connectors;
	vector<CMBBlock> Blocks;
	string error; 
};

#ifdef QT_version
QString Export(const QString& s);
#endif // QT_version

#endif
