#include "stdafx.h"
#include "MBBlock.h"
#include "StringOP.h"
#include "Function.h"
#include "Medium.h"


CMBBlock::CMBBlock(void)
{
	cout<< "check" << endl;
	#ifdef Debug_API
        show_message("Creating default block");
	#endif // Debug_API
	cout<< "check done!" << endl;
	n_constts = 0;
	n_phases = 0;
	fixed = false;
	fixed_evaporation=false;
	fixed_evaporation_val=1;
	S=0;
	setzero=0;
	outflow_corr_factor = 1;
	q = 0;
	fs_params.resize(n_flow_params);
	fs_params[storativity] = 0.01;
	fs_params[theta_s] = 1;

	fs_params[storage_epsilon] = 0.01;
	fs_params[storage_n] = 2;
	fs_params[maximum_bio_volume] = 1e6;

	vapor_diffusion=0;
	DS = 0;
	precipitation_swch = true;
	light_swch = true;
	air_phase = -1;
	bulk_density = 1;

}

CMBBlock::CMBBlock(string s)
{
	cout<< "set properties check" << endl;
	#ifdef Debug_API
	show_message("Inside Setting Blocks ");
	#endif // Debug_API
	cout<< "check done!" << endl;
	n_constts = 0;
	n_phases = 0;
	fixed = false;
	fixed_evaporation=false;
	fixed_evaporation_val=1;
	S=0;
	setzero=0;
	outflow_corr_factor = 1;
	q = 0;
	fs_params.resize(n_flow_params);
	fs_params[storativity] = 0.01;
	fs_params[theta_s] = 1;

	fs_params[storage_epsilon] = 0.01;
	fs_params[storage_n] = 2;
	fs_params[maximum_bio_volume] = 1e6;

	vapor_diffusion=0;
	DS = 0;
	precipitation_swch = true;
	light_swch = true;
	air_phase = -1;
	bulk_density = 1;
#ifndef QT_version
	showmessages = true;
#endif // QT_version
	#ifdef Debug_API
	show_message("setting properties for block " + ID);
	#endif // Debug_API
	set_properties(s);
	show_message("Block: '" + ID + "' was created");

}


CMBBlock::~CMBBlock(void)
{
	for (unsigned int i=0; i<Solid_phase.size(); i++) Solid_phase[i] = NULL;
	for (unsigned int i = 0; i<evaporation_m.size(); i++) evaporation_m[i] = NULL;
	for (unsigned int i = 0; i<buildup.size(); i++) buildup[i] = NULL;
	light = NULL;
	temperature = NULL;
	current_temperature = NULL;
	current_light = NULL;
	current_wind = NULL;
	RXN = NULL;
	parent = NULL;


}

CMBBlock::CMBBlock(const CMBBlock& BB)// copy constructor
{
	n_constts = BB.n_constts;
	n_phases = BB.n_phases;
	G = BB.G;
	G_star = BB.G_star;
	CG = BB.CG;
	G_stored_mass = BB.G_stored_mass; //newly added
	CG_stored_mass = BB.CG_stored_mass; //newly added
	CG_star = BB.CG_star;
	phi = BB.phi;
	K = BB.K;
	K_star = BB.K_star;
	f = BB.f;
	kappa = BB.kappa;
	fs_params = BB.fs_params;
	ID = BB.ID;
	H = BB.H;
	A = BB.A;
	V = BB.V;
	S = BB.S;
	DS=BB.DS;
	porosity=BB.porosity;
	H_star = BB.H_star;
	A_star = BB.A_star;
	V_star = BB.V_star;
	S_star = BB.S_star;
	z0 = BB.z0;
	H_S_expression = BB.H_S_expression;
	H_S_expression_txt = BB.H_S_expression_txt;
	V_S_expression = BB.V_S_expression;
	rxn_params = BB.rxn_params;
	inflow_filename = BB.inflow_filename;
	inflow = BB.inflow;
	indicator=BB.indicator;
	MBBlocks=BB.MBBlocks;
	fixed=BB.fixed;
	connectors = BB.connectors;
	connectors_se = BB.connectors_se;
	vapor_diffusion = BB.vapor_diffusion;
	fixed_evaporation=BB.fixed_evaporation;
	fixed_evaporation_val = BB.fixed_evaporation_val;
	funcs = BB.funcs;
	setzero=BB.setzero;
	outflow_corr_factor = BB.outflow_corr_factor;
	Solid_phase_id = BB.Solid_phase_id;
	q = BB.q;
	capacity_c = BB.capacity_c; // colloid capacities
	capacity_c_star = BB.capacity_c_star;
	capacity_c_Q = BB.capacity_c_Q;
	capacity_c_star_Q = BB.capacity_c_star_Q;
	bulk_density = BB.bulk_density;
	RXN = BB.RXN;
	light = BB.light;
	temperature = BB.temperature;
	initial_g_counter_p = BB.initial_g_counter_p; initial_g_counter_l = BB.initial_g_counter_l; initial_g = BB.initial_g;
	initial_cg_counter_p = BB.initial_cg_counter_p; initial_cg_counter_c = BB.initial_cg_counter_c; initial_cg_counter_l = BB.initial_cg_counter_l; initial_cg = BB.initial_cg;
	precipitation_swch = BB.precipitation_swch;
	plant_prop = BB.plant_prop;
	light_swch = BB.light_swch;
	buildup = BB.buildup;
	buildup_id = BB.buildup_id;
	envexchange = BB.envexchange;
	envexchange_id = BB.envexchange_id;
	air_phase = BB.air_phase;
	evaporation_id = BB.evaporation_id;
	evaporation_m = BB.evaporation_m;
	light_reduction_factor = BB.light_reduction_factor;
	perform_rxn = BB.perform_rxn;
	location = BB.location;
}

CMBBlock& CMBBlock::operator=(const CMBBlock &BB)
{
	#ifdef Debug_API
	show_message("Assigning Block");
	#endif // Debug_API

	n_constts = BB.n_constts;
	n_phases = BB.n_phases;
	G = BB.G;
	G_star = BB.G_star;
	CG = BB.CG;
	CG_star = BB.CG_star;
	G_stored_mass = BB.G_stored_mass; //newly added
	CG_stored_mass = BB.CG_stored_mass; //newly added
	phi = BB.phi;
	K = BB.K;
	K_star = BB.K_star;
	f = BB.f;
	kappa = BB.kappa;
	fs_params = BB.fs_params;
	ID = BB.ID;
	H = BB.H;
	A = BB.A;
	V = BB.V;
	S = BB.S;
	DS=BB.DS;
	porosity=BB.porosity;
	H_star = BB.H_star;
	A_star = BB.A_star;
	V_star = BB.V_star;
	S_star = BB.S_star;
	z0 = BB.z0;
	H_S_expression = BB.H_S_expression;
	H_S_expression_txt = BB.H_S_expression_txt;
	V_S_expression = BB.V_S_expression;
	RXN = BB.RXN;
	rxn_params = BB.rxn_params;
	inflow_filename = BB.inflow_filename;
	inflow = BB.inflow;
	indicator=BB.indicator;
	MBBlocks=BB.MBBlocks;
	fixed=BB.fixed;
	connectors = BB.connectors;
	connectors_se = BB.connectors_se;
	vapor_diffusion = BB.vapor_diffusion;
	fixed_evaporation=BB.fixed_evaporation;
	fixed_evaporation_val = BB.fixed_evaporation_val;
	funcs = BB.funcs;
	setzero=BB.setzero;
	outflow_corr_factor = BB.outflow_corr_factor;
	Solid_phase_id = BB.Solid_phase_id;
	q = BB.q;
	capacity_c = BB.capacity_c; // colloid capacities
	capacity_c_star = BB.capacity_c_star;
	capacity_c_Q = BB.capacity_c_Q;
	capacity_c_star_Q = BB.capacity_c_star_Q;
	bulk_density = BB.bulk_density;
	initial_g_counter_p = BB.initial_g_counter_p; initial_g_counter_l = BB.initial_g_counter_l; initial_g = BB.initial_g;
	initial_cg_counter_p = BB.initial_cg_counter_p; initial_cg_counter_c = BB.initial_cg_counter_c; initial_cg_counter_l = BB.initial_cg_counter_l; initial_cg = BB.initial_cg;
	plant_prop = BB.plant_prop;
	precipitation_swch = BB.precipitation_swch;
	light_swch = BB.light_swch;
	buildup = BB.buildup;
	buildup_id = BB.buildup_id;
	envexchange_id = BB.envexchange_id;
	envexchange = BB.envexchange;
	air_phase = BB.air_phase;
	evaporation_id = BB.evaporation_id;
	evaporation_m = BB.evaporation_m;
	light_reduction_factor = BB.light_reduction_factor;
	perform_rxn = BB.perform_rxn;
	location = BB.location;
	return *this;
}

double CMBBlock::get_val(int i, const vector<int> &ii)
{
	/* variable codes:
	H: 1 : Hydraulic Head
	A: 2 : Area
	V: 3 : Volume
	S: 4 : Storage
	z0: 5 :elevation
	d: 6 :distance
	Q: 7 :flow rate
	v: 8 :velocity
	s: 9 :effective saturation
	theta: 10: volumetric water content
	Hydraulic Parameters: 50-99
	G: 101-199
	GS: 1000-1999
	Reaction parameters: 2000-2999
	*/

    if (i==state_vars::Head) return H;
    if (i==state_vars::Area) return A;
    if (i==state_vars::Volume) return V;
    if (i==state_vars::Storage) return S;
    if (i==state_vars::Bottom_Elev) return z0;
    if (i==state_vars::Moisture_Content) return V/A;    // blocks don't have d
	if (i==7) return 0;
    if (i==state_vars::Darcy_flux) return q;

    if (i==state_vars::Effective_Moisture)
    {   if ((indicator != Soil) && (indicator!=Darcy))
			return (Heavyside(S/V)*S/V - fs_params[theta_r])/(fs_params[theta_s]-fs_params[theta_r]);
        else
			return (S/V - fs_params[theta_r])/(fs_params[theta_s]-fs_params[theta_r]);   //allow s to be above 1

	}

    if (i==state_vars::_Effective_Moisture)
	{
		if ((indicator != Soil) && (indicator != Darcy))
			if (S>0) return S/(S+1e-5*A); else return 0;
		else
			return S/V;   //allow s to be above 1
	}


    //if (i==state_vars::Depression_Storage) return DS;
    if (i==state_vars::Vapor_Diffusion) return vapor_diffusion;
    if (i==state_vars::Bulk_Density) return bulk_density;
    if (i == state_vars::Air_Content)
	{
		if (air_phase == 0)
			return 0;
		else
			return Pos(V*fs_params[1] - S);
	}

	if (i == physical_params::light)
		return *current_light*light_reduction_factor;

	if (i == physical_params::temperature)
		return *current_temperature;

	if (i == physical_params::vapor_pressure)
		return 611 * exp(17.27*(*current_temperature) / ((*current_temperature) + 237.3));

	if (i == physical_params::latent_heat_of_evaporation)
		return 2.501e6 - 2370*(*current_temperature);

	if (i == physical_params::LAI)
		return plant_prop.LAI;

	if (i == physical_params::pan_evaporation_rate)
        return get_evaporation(parent->Solution_State.t);

	if (i>=50 && i<100) return fs_params[i-50];
	if (i>=100 && i<1000) return G[ii[0]][i];
	if (i>=1000 && i<2000) return CG[ii[0]][i];
	if (i>=2000 && i<3000) return rxn_params[i-2000];
	if (i == 3010)
	{
		if (Solid_phase[ii[0]]->c_params[i - 3000] != 0)
			return Solid_phase[ii[0]]->c_params[i - 3000];
		else
			return bulk_density;
	}

	if (i>=3000 && i<4000) return Solid_phase[ii[0]]->get_val(i);
	if (i>=4000 && i<5000) return envexchange[ii[1]]->parameters[i-4000];
	if (i >= 5000 && i<6000) return RXN->cons[ii[0]].get_val(i);
	if (i >= 6000 && i<6500) return evaporation_m[ii[0]]->parameters[i - 6000];
    if (i == 6501 && i<7000) return evaporation_m[ii[0]]->single_crop_coefficient.interpol(dayOfYear(parent->Solution_State.t));
	if (i >= 7000 && i < 8000) return
		plant_prop.half_saturation_constants[i - 7000];
	if (i >= 10000 && i<20000) return G[(i-10000)/1000][(i-10000)%1000];
	if (i >= 100000 && i<200000) return CG[(i-100000)/10000][(i-100000)%10000];
    return 0;
}

double CMBBlock::get_val(const string &SS)
{
	/* variable codes:
	H: 1 : Hydraulic Head
	A: 2 : Area
	V: 3 : Volume
	S: 4 : Storage
	z0: 5 :elevation
	d: 6 :distance
	Q: 7 :flow rate
	v: 8 :velocity
	s: 9 :effective saturation
	theta: 10: volumetric water content
	Hydraulic Parameters: 50-99
	G: 101-199
	GS: 1000-1999
	Reaction parameters: 2000-2999
	*/

	vector<char> del;
	del.push_back('[');
	del.push_back(']');
	del.push_back(':');
	vector<string> s = split(SS, del);

	if (s.size()==1)
	{
		if (tolower(trim(s[0]))=="depth") return max(V/A,0.0);
		if (tolower(trim(s[0]))=="a" || tolower(trim(s[0]))=="area") return A;
		if (tolower(trim(s[0]))=="h") return H;
		if (tolower(trim(s[0]))=="v") return V;
		if (tolower(trim(s[0]))=="s") return S;
		if (tolower(trim(s[0]))=="z0") return z0;
		if (tolower(trim(s[0])) == "lai") return plant_prop.LAI;
		if (tolower(trim(s[0]))=="se")
		{	if (indicator!=0)
			return (Heavyside(S/V)*S/V - fs_params[theta_r])/(fs_params[theta_s]-fs_params[theta_r]);
		else
			return (S/V - fs_params[theta_r])/(fs_params[theta_s]-fs_params[theta_r]);   //allow s to be above 1
		}
        if (tolower(trim(s[0]))=="theta" || tolower(trim(s[0]))=="~theta")
		{	if (indicator!=0)
			if (S>0) return S/(S+1e-5*A); else return 0;
		else
			return S/V;   //allow s to be above 1
		}

		if (tolower(trim(s[0]))=="porosity") return fs_params[theta_s];
		if (tolower(trim(s[0]))=="depression") return DS;
		if (tolower(trim(s[0]))=="vapor_diff") return vapor_diffusion;

		if (tolower(trim(s[0]))=="ks") return fs_params[ks];
		if (tolower(trim(s[0]))=="theta_s") return fs_params[theta_s];
		if (tolower(trim(s[0]))=="theta_r") return fs_params[theta_r];
		if (tolower(trim(s[0]))=="vg_alpha") return fs_params[vg_alpha];
		if (tolower(trim(s[0]))=="vg_n") return fs_params[vg_n];
		if (tolower(trim(s[0]))=="vg_m") return fs_params[vg_m];
		if (tolower(trim(s[0]))=="lambda") return fs_params[lambda];
		if ((tolower(trim(s[0]))=="sc") || (tolower(trim(s[0]))=="storativity")) return fs_params[storativity];
		if ((tolower(trim(s[0]))=="bulk_density") || (tolower(trim(s[0]))=="bd")) return bulk_density;
		if (tolower(trim(s[0]))=="storage_epsilon") return fs_params[storage_epsilon];
		if (tolower(trim(s[0]))=="storage_n") return fs_params[storage_n];
		if (tolower(trim(s[0])) == "light") return (*current_light)*light_reduction_factor;
		if (tolower(trim(s[0])) == "temperature") return *current_temperature;
		if (tolower(trim(s[0])) == "light_reduction_factor") return light_reduction_factor;
		if (tolower(trim(s[0]))=="a*") return A_star;
		if (tolower(trim(s[0]))=="h*") return H_star;
		if (tolower(trim(s[0]))=="v") return V_star;
		if (tolower(trim(s[0]))=="s*") return S_star;
        if (tolower(trim(s[0])) == "e") return get_evaporation(parent->Solution_State.t);
		if (tolower(trim(s[0]))=="se*")
		{
			if ((indicator != Soil) && (indicator != Darcy))
			return (Heavyside(S_star/V)*S_star/V - fs_params[theta_r])/(fs_params[theta_s]-fs_params[theta_r]);
		else
			return (S_star/V - fs_params[theta_r])/(fs_params[theta_s]-fs_params[theta_r]);   //allow s to be above 1
		}
		if (tolower(trim(s[0]))=="theta*")
		{
			if ((indicator != Soil) && (indicator != Darcy))
			if (S_star>0) return S_star/(S_star+1e-5*A); else return 0;
		else
			return S_star/V;   //allow s to be above 1
		}
	}
	else if (s.size()==2)
	{
		if (tolower(trim(s[0])) == "fp") return fs_params[atoi(s[1].c_str())];
		if (tolower(trim(s[0])) == "g")
		{
			int p = lookup_particle_type(s[1]);
			if (p!=-1) return G[lookup_particle_type(s[1])][0];
		}
		if (tolower(trim(s[0])) == "cg")
		{
			int k = RXN->look_up_constituent_no(s[1]);
			if (k != -1) return CG[k][0];
		}
		if (tolower(trim(s[0])) == "hsc")
		{
			int k = plant_prop.look_up_limiting_nutrient(s[1]);
			if (k != -1) return plant_prop.half_saturation_constants[k];
		}

		if (tolower(trim(s[0])) == "p") return rxn_params[atoi(s[1].c_str())];
	}
	else if (s.size()==3)
	{
		if (tolower(trim(s[0])) == "g")
		{
			int p = lookup_particle_type(s[1]);
			int l = Solid_phase[p]->lookup_phase(s[2]);
			if ((p!=-1) && (l!=-1)) return G[p][l];

		}

		if (tolower(trim(s[0])) == "cg")
		{
			int p = lookup_particle_type(s[2]);
			int k = RXN->look_up_constituent_no(s[1]);
			if (tolower(s[2]) == "soil") p = -1;
			if (tolower(s[2]) == "aqueous") p = -2;
			if (k != -1) return CG[k][get_member_no(p,0)];
		}
	}

	else if (s.size() == 4)
	{

		if (tolower(trim(s[0])) == "cg")
		{
			int p = lookup_particle_type(s[2]);
			int k = RXN->look_up_constituent_no(s[1]);
			int l = Solid_phase[p]->lookup_phase(s[3]);
			if (tolower(s[2]) == "soil") p = -1;
			if (tolower(s[2]) == "aqueous") p = -2;
			if ((l != -1) && (k != -1)) return CG[k][get_member_no(p, l)];
		}
	}
    return 0;
}

double CMBBlock::get_val_star(int i, const vector<int> &ii)
{
    if (i==state_vars::Head) return H_star;
    if (i==state_vars::Area) return A_star;
    if (i==state_vars::Volume) return V_star;
    if (i==state_vars::Storage) return S_star;
    if (i==state_vars::Bottom_Elev) return z0;
    if (i==state_vars::Moisture_Content) 
		return V_star/A_star;
	if (i==7) return 0;
    if (i==state_vars::Darcy_flux) return q;
    if (i==state_vars::Effective_Moisture)
	{
		if ((indicator != Soil) && (indicator != Darcy))
			return (Heavyside(S_star/V_star)*S_star/V_star - fs_params[theta_r])/(fs_params[theta_s]-fs_params[theta_r]);
		else
			return (S_star/V_star - fs_params[theta_r])/(fs_params[theta_s]-fs_params[theta_r]);   //allow s to be above 1
		}
    //if (i==12) return DS;
    if (i==state_vars::Vapor_Diffusion) return vapor_diffusion;

    if (i==state_vars::_Effective_Moisture)
	{
		if ((indicator != Soil) && (indicator != Darcy))
			if (S_star>0) return S_star/(S_star+1e-5*A); else return 0;
		else
			return S_star/V;   //allow s to be above 1
	}
    if (i==state_vars::Bulk_Density) return bulk_density;
    if (i == state_vars::Air_Content)
	{
		if (air_phase == 0)
			return 0;
		else
			return Pos(V*fs_params[theta_s] - S);

	}
	if (i == physical_params::light)
		return (*current_light)*light_reduction_factor;

	if (i == physical_params::temperature)
		return *current_temperature;

	if (i == physical_params::wind)
		return *current_wind;

	if (i == physical_params::humidity)
		return *current_humidity;

	if (i == physical_params::vapor_pressure)
		return 611 * exp(17.27*(*current_temperature) / ((*current_temperature) + 237.3));

	if (i == physical_params::latent_heat_of_evaporation)
		return 2.501e6 - 2370 * (*current_temperature);

	if (i == physical_params::LAI)
		return plant_prop.LAI;

	if (i == physical_params::pan_evaporation_rate)
        return get_evaporation(parent->Solution_State.t);

	if (i>=50 && i<100) return fs_params[i-50];
	if (i>=100 && i<1000) return G_star[ii[0]][i];
	if (i>=1000 && i<2000) return CG_star[ii[0]][i];
	if (i>=2000 && i<3000) return rxn_params[i-2000];
	if (i == 3010)
	{
		if (Solid_phase[ii[0]]->c_params[i - 3000] != 0)
			return Solid_phase[ii[0]]->c_params[i - 3000];
		else
			return bulk_density;
	}

	if (i>=3000 && i<4000) return Solid_phase[ii[0]]->get_val(i);
	if (i>=4000 && i<5000) return envexchange[ii[1]]->parameters[i-4000];
	if (i >= 5000 && i<6000) return RXN->cons[ii[0]].get_val(i);
	if (i >= 6000 && i<6500) return evaporation_m[ii[0]]->parameters[i - 6000];
    if (i == 6501 && i<7000) return evaporation_m[ii[0]]->single_crop_coefficient.interpol(dayOfYear(parent->Solution_State.t));
	if (i >= 7000 && 8000) return plant_prop.half_saturation_constants[i - 7000];
	if (i >= 10000 && i<20000) return G_star[(i - 10000) / 1000][(i - 10000) % 1000];
	if (i >= 100000 && i<200000) return CG_star[(i - 100000) / 10000][(i - 100000) % 10000];

	return 0;
}

double CMBBlock::calc(CStringOP &term, const vector<int> &ii)  //Works w/o reference(&)
{
	if (term.function==true)
    {
        if (term.number == min_)
			return min(calc(term.terms[0],ii), calc(term.terms[1],ii));
		if (term.number == max_)
			return max(calc(term.terms[0],ii), calc(term.terms[1],ii));
		if (term.number == sq1_)
			return 0.5/calc(term.terms[1],ii)*(calc(term.terms[0],ii)*calc(term.terms[1],ii)+sqrt(pow(calc(term.terms[0],ii)*calc(term.terms[1],ii),2)+1));
        if (term.number == frs_)
			return funcs[0].evaluate(get_val(9,ii));
		if (term.number == fas_)
			return funcs[0].evaluate(get_val(4,ii));
        if (term.number == mon_)
			return mon(calc(term.terms[0],ii),calc(term.terms[1],ii));
		if (term.number == sq2_)
		{	double term1 = calc(term.terms[0],ii);
			double term2 = calc(term.terms[1],ii);
			return pow(term1,(0.5*term1+term2)/(term1+term2));
		}

    }

	double out = 0;
	if ((term.nterms == 1) && (term.nopts == 0))
	{
		if (term.parameter == true)
			out = RXN->parameters[term.number].eff_value;
		else if (term.s_concentration == true)
			if (term.particle_type == -1) out = G[ii[0]][term.phase]; else out = G[term.particle_type][term.phase];
		else if (term.concentration == true)
			if (term.particle_type==-1)
				if (term.number!=-1)
					out = CG[term.number][get_member_no(-2,0)];
				else
					out = CG[ii[0]][get_member_no(-2,0)];
			else
				if (term.number!=-1)
					out = CG[term.number][get_member_no(term.particle_type,term.phase)];
				else
					out = CG[ii[0]][get_member_no(term.particle_type,term.phase)];
		else if (term.physical_ch == true)
			out = get_val(term.number,ii);
		else if (term.constant == true)
			out = term.value;
		else
			out = calc(term.terms[0],ii);
	}

	if ((term.nterms == 1) && (term.nopts == 1))
	{
		if (term.operators[0] == 0)
			out = calc(term.terms[0],ii);

		if (term.operators[0] == 1)
			out = -calc(term.terms[0],ii);
	}

	if ((term.nterms == 2) && (term.nopts == 1))
	{
		if (term.operators[0] == 0)
			out = calc(term.terms[0],ii)+calc(term.terms[1],ii);
		if (term.operators[0] == 1)
			out = calc(term.terms[0],ii)-calc(term.terms[1],ii);
		if (term.operators[0] == 2)
			out = calc(term.terms[0],ii)*calc(term.terms[1],ii);
		if (term.operators[0] == 3)
			out = calc(term.terms[0],ii)/calc(term.terms[1],ii);
		if (term.operators[0] == 4)
			out = pow(calc(term.terms[0],ii),calc(term.terms[1],ii));
	}

	if ((term.nterms == 2) && (term.nopts == 2))
	{
		double sum = 0;
		if (term.operators[0] == 0)
			sum = calc(term.terms[0],ii);
		else if (term.operators[0] == 1)
			sum = -calc(term.terms[0],ii);

		if (term.operators[1] == 0)
			out = sum+calc(term.terms[1],ii);
		if (term.operators[1] == 1)
			out = sum-calc(term.terms[1],ii);
		if (term.operators[1] == 2)
			out = sum*calc(term.terms[1],ii);
		if (term.operators[1] == 3)
			out = sum/calc(term.terms[1],ii);
		if (term.operators[1] == 4)
			out = pow(fabs(sum),calc(term.terms[1],ii))*fabs(sum)/sum;

	}

	if ((term.nterms>2) && (term.nopts == term.nterms-1))
	{
		out = calc(term.terms[0],ii);
		for (int j=1; j<term.nterms; j++)
		{
			if (term.operators[j-1] == 0)
				out+=calc(term.terms[j],ii);
			if (term.operators[j-1] == 1)
				out-=calc(term.terms[j],ii);
			if (term.operators[j-1] == 2)
				out*=calc(term.terms[j],ii);
			if (term.operators[j-1] == 3)
				out/=calc(term.terms[j],ii);
			if (term.operators[j-1] == 4)
				out=pow(out,calc(term.terms[j],ii));
		}

	}


	if ((term.nterms>2) && (term.nopts == term.nterms))
	{
		out = 0;
		if (term.operators[0] == 0)
			out = calc(term.terms[0],ii);
		else if (term.operators[0] == 1)
			out = -calc(term.terms[0],ii);


		for (int j=1; j<term.nterms; j++)
		{
			if (term.operators[j] == 0)
				out+=calc(term.terms[j],ii);
			if (term.operators[j] == 1)
				out-=calc(term.terms[j],ii);
			if (term.operators[j] == 2)
				out*=calc(term.terms[j],ii);
			if (term.operators[j] == 3)
				out/=calc(term.terms[j],ii);
			if (term.operators[j] == 4)
				out=pow(out,calc(term.terms[j],ii));
		}

	}
	if (term.function==true)
	{	if (term.number == exp_)
			return exp(out);
		if (term.number == hsd_)
			return Heavyside(out);
		if (term.number == lne_)
			return log(out);
		if (term.number == lnt_)
			return log10(out);
		if (term.number == sgm_)
			return 1.0/(1.0+exp(-out));
		if (term.number == pos_)
			return 0.5*(fabs(out)+out);
		if (term.number == sqr_)
			return sqrt(out);
		if (term.number == ply_)
			return pipe_poly(out);
		if (term.number==abs_)
			return fabs(out);
		if (term.number==sqs_)
		{
		 	if (out!=0)
				return out/fabs(out)*sqrt(fabs(out));
			else
				return 0;
		}
		if (term.number == sig_)
		{
			return exp(out) / (1 + exp(out));
		}
	}

	return out;

}

double CMBBlock::calc_star(CStringOP &term, const vector<int> &ii)
{
	if (term.function==true)
    {
        if (term.number == min_)
			return min(calc_star(term.terms[0],ii), calc_star(term.terms[1],ii));
		if (term.number == max_)
			return max(calc_star(term.terms[0],ii), calc_star(term.terms[1],ii));
		if (term.number == sq1_)
			return 0.5/calc_star(term.terms[1],ii)*(calc_star(term.terms[0],ii)*calc_star(term.terms[1],ii)+sqrt(pow(calc_star(term.terms[0],ii)*calc_star(term.terms[1],ii),2)+1));
        if (term.number == frs_)
			return funcs[0].evaluate(get_val_star(9,ii));
		if (term.number == fas_)
			return funcs[0].evaluate(get_val_star(4,ii));
        if (term.number == mon_)
			return mon(calc_star(term.terms[0],ii),calc_star(term.terms[1],ii));
		if (term.number == sq2_)
		{	double term1 = calc_star(term.terms[0],ii);
			double term2 = calc_star(term.terms[1],ii);
			return pow(term1,(0.5*term1+term2)/(term1+term2));
		}

    }

	double out = 0;
	if ((term.nterms == 1) && (term.nopts == 0))
	{
		if (term.parameter == true)
			out = RXN->parameters[term.number].eff_value;
		else if (term.s_concentration == true)
			if (term.particle_type == -1) out = G_star[ii[0]][term.phase]; else out = G[term.particle_type][term.phase];
		else if (term.concentration == true)
			if (term.particle_type==-1)
				if (term.number!=-1)
					out = CG_star[term.number][get_member_no(-2,0)];
				else
					out = CG_star[ii[0]][get_member_no(-2,0)];
			else
				if (term.number!=-1)
					out = CG_star[term.number][get_member_no(term.particle_type,term.phase)];
				else
					out = CG_star[ii[0]][get_member_no(term.particle_type,term.phase)];
		else if (term.physical_ch == true)
			out = get_val_star(term.number,ii);
		else if (term.constant == true)
			out = term.value;
		else
			out = calc_star(term.terms[0],ii);
	}

	if ((term.nterms == 1) && (term.nopts == 1))
	{
		if (term.operators[0] == 0)
			out = calc_star(term.terms[0],ii);

		if (term.operators[0] == 1)
			out = -calc_star(term.terms[0],ii);
	}

	if ((term.nterms == 2) && (term.nopts == 1))
	{
		if (term.operators[0] == 0)
			out = calc_star(term.terms[0],ii)+calc_star(term.terms[1],ii);
		if (term.operators[0] == 1)
			out = calc_star(term.terms[0],ii)-calc_star(term.terms[1],ii);
		if (term.operators[0] == 2)
			out = calc_star(term.terms[0],ii)*calc_star(term.terms[1],ii);
		if (term.operators[0] == 3)
			out = calc_star(term.terms[0],ii)/calc_star(term.terms[1],ii);
		if (term.operators[0] == 4)
			out = pow(calc_star(term.terms[0],ii),calc_star(term.terms[1],ii));

	}

	if ((term.nterms == 2) && (term.nopts == 2))
	{
		double sum = 0;
		if (term.operators[0] == 0)
			sum = calc_star(term.terms[0],ii);
		else if (term.operators[0] == 1)
			sum = -calc_star(term.terms[0],ii);

		if (term.operators[1] == 0)
			out = sum+calc_star(term.terms[1],ii);
		if (term.operators[1] == 1)
			out = sum-calc_star(term.terms[1],ii);
		if (term.operators[1] == 2)
			out = sum*calc_star(term.terms[1],ii);
		if (term.operators[1] == 3)
			out = sum/calc_star(term.terms[1],ii);
		if (term.operators[1] == 4)
			out = pow(fabs(sum),calc_star(term.terms[1],ii))*fabs(sum)/sum;

	}

	if ((term.nterms>2) && (term.nopts == term.nterms-1))
	{
		out = calc_star(term.terms[0],ii);
		for (int j=1; j<term.nterms; j++)
		{
			if (term.operators[j-1] == 0)
				out+=calc_star(term.terms[j],ii);
			if (term.operators[j-1] == 1)
				out-=calc_star(term.terms[j],ii);
			if (term.operators[j-1] == 2)
				out*=calc_star(term.terms[j],ii);
			if (term.operators[j-1] == 3)
				out/=calc_star(term.terms[j],ii);
			if (term.operators[j-1] == 4)
				out=pow(out,calc_star(term.terms[j],ii));
		}

	}


	if ((term.nterms>2) && (term.nopts == term.nterms))
	{
		out = 0;
		if (term.operators[0] == 0)
			out = calc_star(term.terms[0],ii);
		else if (term.operators[0] == 1)
			out = -calc_star(term.terms[0],ii);


		for (int j=1; j<term.nterms; j++)
		{
			if (term.operators[j] == 0)
				out+=calc_star(term.terms[j],ii);
			if (term.operators[j] == 1)
				out-=calc_star(term.terms[j],ii);
			if (term.operators[j] == 2)
				out*=calc_star(term.terms[j],ii);
			if (term.operators[j] == 3)
				out/=calc_star(term.terms[j],ii);
			if (term.operators[j] == 4)
				out=pow(out,calc_star(term.terms[j],ii));
		}

	}
	if (term.function==true)
	{	if (term.number == exp_)
			return exp(out);
		if (term.number == hsd_)
			return Heavyside(out);
		if (term.number == lne_)
			return log(out);
		if (term.number == lnt_)
			return log10(out);
		if (term.number == sgm_)
			return 1.0/(1.0+exp(-out));
		if (term.number == pos_)
			return 0.5*(fabs(out)+out);
		if (term.number == sqr_)
			return sqrt(out);
		if (term.number == ply_)
			return pipe_poly(out);
		if (term.number==abs_)
			return fabs(out);
		if (term.number==sqs_)
		{
			if (out!=0)
				return out/fabs(out)*sqrt(fabs(out));
			else
				return 0;
		}
		if (term.number == sig_)
		{
			return exp(out) / (1 + exp(out));
		}
	}

	return out;
}

void CMBBlock::set_val(int i, const double &val)
{
	if (i==1) H = val;
	if (i==2) A = val;
	if (i==3) V = val;
	if (i==4) S = val;
	if (i==5) z0 = val;
	if (i==9) S = V*(val*(fs_params[theta_s]-fs_params[theta_r]) + fs_params[theta_r]);
	if (i==10) S = V*val;
	if (i==13) vapor_diffusion=val;
	if (i==14) bulk_density = val;
	if (i>=50 && i<100) fs_params[i-50] = val;
	if (i>=100 && i<1000) G[(i-100)/100][(i-100)%100] = val;
	if (i>=1000 && i<2000) CG[int((i-1000)/n_phases)][(i-1000)%n_phases] = val;
	if (i>=2000 && i<3000) rxn_params[i-2000] = val;


}

void CMBBlock::set_val_star(int i, const double &val)
{
	if (i==1) {H_star = val; return;}
	if (i==2) {A_star = val; return;}
	if (i==3) {V = val; return;}
	if (i==4) {S_star = val; return;}
	if (i==5) {z0 = val; return; }
	if (i==9) {S_star = V*(val*(fs_params[theta_s]-fs_params[theta_r]) + fs_params[theta_r]); return; }
	if (i==10) {S_star = V*val; return; }
	if (i==13) {vapor_diffusion=val; return; }
	if (i==14) {bulk_density = val; return; }

	if (i>=50 && i<100) {fs_params[i-50] = val; return;}
	if (i>=100 && i<200) {G[(i-100)/100][(i-100)%100] = val; return;}// colloidal phases
	if (i>=1000 && i<2000) {CG[int((i-1000)/n_phases)][(i-1000)%n_phases] = val; return;}
	if (i>=2000 && i<3000) {rxn_params[i-2000] = val; return;}
	// 3000-3999: solid_phase

}

bool CMBBlock::set_val(const string &SS, const double &val)
{
	bool success = false;
	vector<char> del;
	del.push_back('[');
	del.push_back(']');
	del.push_back(':');
	vector<string> s = split(SS,del);
	if (s.size()==1)
	{
		if (tolower(trim(s[0]))=="a" || tolower(trim(s[0]))=="area") {A = val; A_star = val; success = true;}
		if (tolower(trim(s[0]))=="h") {H = val;success = true;}
		if (tolower(trim(s[0]))=="v") {V = val; V_star=val; success = true;}
		if (tolower(trim(s[0]))=="s") {S = val;success = true;}
		if (tolower(trim(s[0]))=="z0") {z0 = val;success = true;}
		if (tolower(trim(s[0]))=="se") {S = V*(val*(fs_params[theta_s]-fs_params[theta_r]) + fs_params[theta_r]);success = true;}
		if (tolower(trim(s[0]))=="theta")
		{
			S = V*val;success = true;
		}
		if (tolower(trim(s[0]))=="vapor_diffusion") {vapor_diffusion=val;success = true;}
		if ((tolower(trim(s[0]))=="bulk_density") || (tolower(trim(s[0]))=="bd")) {bulk_density = val;success = true;}

		if (tolower(trim(s[0])) == "depth") { V = A * val; V_star = A * val; success = true; }
		if (tolower(trim(s[0]))=="h0") {S = A*val*fs_params[theta_s];success = true;}   //fs_params[1] must be read earlier than h0
		if (tolower(trim(s[0]))=="porosity") {fs_params[theta_s] = val;success = true;}
		if (tolower(trim(s[0]))=="depression") {fs_params[depression_storage]=val;success = true;}

		if (tolower(trim(s[0]))=="ks") {fs_params[ks] = val;success = true;}
		if (tolower(trim(s[0]))=="theta_s") {fs_params[theta_s] = val;success = true;}
		if (tolower(trim(s[0]))=="theta_r") {fs_params[theta_r] = val;success = true;}
		if (tolower(trim(s[0]))=="vg_alpha") {fs_params[vg_alpha] = val;success = true;}
		if (tolower(trim(s[0]))=="vg_n") {fs_params[vg_n] = val;success = true;}
		if (tolower(trim(s[0]))=="vg_m") {fs_params[vg_m] = val;success = true;}
		if (tolower(trim(s[0]))=="lambda") {fs_params[lambda] = val;success = true;}
		if ((tolower(trim(s[0]))=="sc") || (tolower(trim(s[0]))=="storativity")) {fs_params[storativity] = val;success = true;}
		if (tolower(trim(s[0]))=="storage_epsilon") {fs_params[storage_epsilon] = val;success = true;}
		if (tolower(trim(s[0]))=="storage_n") {fs_params[storage_n] = val;success = true;}
		if (tolower(trim(s[0])) == "lai") {plant_prop.LAI = val;success = true;}
		if (tolower(trim(s[0])) == "lai_max") {fs_params[LAI_max] = val;success = true;}
		if (tolower(trim(s[0])) == "k_lai") {fs_params[K_LAI] = val;success = true;}
		if (tolower(trim(s[0])) == "plant_growth_rate_coefficient") {fs_params[plant_growth_rate_coefficient] = val;success = true;}
		if (tolower(trim(s[0])) == "temperature_base") {fs_params[temperature_base] = val;success = true;}
		if (tolower(trim(s[0])) == "temperature_spread_factor") {fs_params[temperature_spread_factor] = val;success = true;}
		if (tolower(trim(s[0])) == "plant_biomass_decay_factor") {fs_params[plant_biomass_decay_factor] = val;success = true;}
		if (tolower(trim(s[0])) == "plant_leaf_decay_factor") {fs_params[plant_leaf_decay_factor] = val;success = true;}
		if (tolower(trim(s[0])) == "optimal_temperature") {fs_params[optimal_temperature] = val;success = true;}
		if (tolower(trim(s[0])) == "maximum_biovolume") {fs_params[maximum_bio_volume] = val;success = true;}


		if (tolower(trim(s[0]))=="outflow_corr_factor") {outflow_corr_factor = val;success = true;}
		if (tolower(trim(s[0]))=="fixed_status") {fixed = val;success = true;}
		if (tolower(trim(s[0])) == "air_phase") {air_phase = int(val);success = true;}
		if (tolower(trim(s[0]))=="a*") {A_star = val;success = true;}
		if (tolower(trim(s[0]))=="h*") {H_star = val;success = true;}
		if (tolower(trim(s[0]))=="v") {V_star = val;success = true;}
		if (tolower(trim(s[0]))=="s*") {S_star = val;success = true;}
		if (tolower(trim(s[0]))=="se*") {S_star = V*(val*(fs_params[theta_s]-fs_params[theta_r]) + fs_params[theta_r]);success = true;}
		if (tolower(trim(s[0]))=="theta*") {S_star = V*val;success = true;}
		if (tolower(trim(s[0])) == "light_reduction_factor") {light_reduction_factor = val;success = true;}
        if (tolower(trim(s[0])) == "x") location.x = val;
        if (tolower(trim(s[0])) == "y") location.y = val;
        if (tolower(trim(s[0])) == "z") location.z = val;
	}
	else if (s.size()==2)
	{
		if (tolower(trim(s[0])) == "fp") {fs_params[atoi(s[1].c_str())] = val;success = true;}
		if (tolower(trim(s[0])) == "p") {rxn_params[atoi(s[1].c_str())] = val;success = true;}
		if (tolower(trim(s[0])) == "g") { initial_g_counter_p.push_back(s[1]); initial_g_counter_l.push_back("mobile"); initial_g.push_back(val); success = true;}
		if (tolower(trim(s[0])) == "cg") { initial_cg_counter_p.push_back(""); initial_cg_counter_l.push_back(""); initial_cg_counter_c.push_back(s[1]);  initial_cg.push_back(val); success = true;}
		if (tolower(trim(s[0])) == "hsc") { plant_prop.limiting_nutrients.push_back(s[1]);  plant_prop.half_saturation_constants.push_back(val); success = true;}
	}
	else if (s.size()==3)
	{
		if (tolower(trim(s[0])) == "g") {initial_g_counter_p.push_back(s[1]); initial_g_counter_l.push_back(s[2]); initial_g.push_back(val);success = true;}
		if (tolower(trim(s[0])) == "cg") { initial_cg_counter_p.push_back(s[2]); initial_cg_counter_l.push_back(""); initial_cg_counter_c.push_back(s[1]);  initial_cg.push_back(val); success = true;}
	}

	else if (s.size() == 4)
	{
		if (tolower(trim(s[0])) == "cg") { initial_cg_counter_p.push_back(s[2]); initial_cg_counter_l.push_back(s[3]); initial_cg_counter_c.push_back(s[1]);  initial_cg.push_back(val); success = true;}
	}

	return success;

}

void CMBBlock::set_num_phases_constts(int n, int m)
{
	n_constts = m;
	n_phases = n;
	G.resize(n_phases);
	CG.resize(n_phases);
	for (int i=0; i<n_phases; i++)
		CG[i].resize(n_constts);

}

void CMBBlock::set_num_phases(int n)
{
	n_phases = n;
	set_num_phases_constts(n_phases, n_constts);

}

void CMBBlock::set_num_constts(int m)
{
	n_constts = m;
	set_num_phases_constts(n_phases, n_constts);
}



void CMBBlock::get_funcs(CStringOP &term)  //Works w/o reference(&)
{
	if ((term.nterms == 1) && (term.nopts == 0))
	{
		if (term.terms.size()>0)
			get_funcs(term.terms[0]);
	}

	if ((term.nterms == 2) && (term.nopts == 1))
	{
		get_funcs(term.terms[0]);
		get_funcs(term.terms[1]);
	}

	if ((term.nterms == 2) && (term.nopts == 2))
	{
		get_funcs(term.terms[0]);
		get_funcs(term.terms[1]);

	}

	if ((term.nterms>2) && (term.nopts == term.nterms-1))
	{
		for (int j=0; j<term.nterms; j++)
			get_funcs(term.terms[j]);

	}


	if ((term.nterms>2) && (term.nopts == term.nterms))
	{
		for (int j=0; j<term.nterms; j++)
			get_funcs(term.terms[j]);

	}
	if (term.function==true)
	{
		if (term.number == 11)
		{	CFunction XX;
			XX.Expression = term;
			XX.Expression.function=false;
			XX.var_id = 0;
			XX._min=1e-16;
			XX._max=2;
			funcs.push_back(XX);
		}
		else if (term.number==12)
		{	CFunction XX;
			XX.Expression = term;
			XX.Expression.function=false;
			XX.var_id = 1;
			XX._min = 1e-16*V;
			XX._max = 1.1*V;
			funcs.push_back(XX);
		}
	}
}

void CMBBlock::evaluate_functions(int i) //i=0->small s; i=1->large S
{
	funcs[i].X.clear();


	for (double x=funcs[i]._min; x<=funcs[i]._max; x+=(funcs[i]._max-funcs[i]._min)/double(funcs[i].n_steps))
	{	if (funcs[i].var_id==0)
			set_val_star(9,x);
		if (funcs[i].var_id==1)
			set_val_star(4,x);

		funcs[i].X.append(x,calc_star(funcs[i].Expression));
	}

	funcs[i].X = funcs[i].X.MA_smooth(2);
	funcs[i].X.structured = true;
}

void CMBBlock::evaluate_functions()
{
	for (unsigned int i=0; i<funcs.size(); i++) evaluate_functions(i);
}

double CMBBlock::get_evaporation(double t)
{

		double sum=0;
		for (unsigned int j = 0; j < evaporation_m.size(); j++)
		{
			if (evaporation_m[j]->model != "time_series")
				sum += evaporation_m[j]->calculate_star(this);
			if ((evaporation_m[j]->evaporation_TS.n>0) && (evaporation_m[j]->model == "time_series"))
				sum += evaporation_m[j]->evaporation_TS.interpol(t)*A;
		}

		return sum;
}

double CMBBlock::get_evaporation(int j, double t)
{
	double sum=0;
	if (evaporation_m[j]->model != "time_series")
		sum = evaporation_m[j]->calculate_star(this);
	if ((evaporation_m[j]->evaporation_TS.n>0) && (evaporation_m[j]->model == "time_series"))
		sum = evaporation_m[j]->evaporation_TS.interpol(t)*A;

	return sum;

}

void CMBBlock::evaluate_K()
{
	for (unsigned int ii=0; ii<Solid_phase.size(); ii++)
	{
		K[ii] = CMatrix(Solid_phase[ii]->n_phases);
		for (int i=0; i<K[ii].getnumrows(); i++)
			for (int j=0; j<K[ii].getnumrows(); j++)
				if (Solid_phase[ii]->K[i][j].nterms==0)
					K[ii][i][j]=0;
				else
				{
					vector<int> jj;
					jj.push_back(ii);
					K[ii][i][j] = calc(Solid_phase[ii]->K[i][j], jj);
				}
	}
}

void CMBBlock::evaluate_K_star()
{
	for (unsigned int ii=0; ii<Solid_phase.size(); ii++)
	{
		K_star[ii] = CMatrix(Solid_phase[ii]->n_phases);
		for (int i=0; i<K_star[ii].getnumrows(); i++)
			for (int j=0; j<K_star[ii].getnumrows(); j++)
				if (Solid_phase[ii]->K[i][j].nterms==0)
					K_star[ii][i][j]=0;
				else
				{
					vector<int> jj;
					jj.push_back(ii);
					K_star[ii][i][j] = calc_star(Solid_phase[ii]->K[i][j], jj);
				}
	}

}


void CMBBlock::evaluate_capacity()
{
	for (unsigned int ii=0; ii<Solid_phase.size(); ii++)
	{
		capacity_c[ii] = CVector(Solid_phase[ii]->n_phases);
		for (int j = 0; j < Solid_phase[ii]->n_phases; j++)
		{
			vector<int> jj;
			jj.push_back(ii);
			capacity_c[ii][j] = calc(Solid_phase[ii]->capacity[j], jj);
		}
	}

}

void CMBBlock::evaluate_capacity_star()
{
	for (unsigned int ii=0; ii<Solid_phase.size(); ii++)
	{
		capacity_c_star[ii] = CVector(Solid_phase[ii]->n_phases);
		for (int j = 0; j < Solid_phase[ii]->n_phases; j++)
		{
			vector<int> jj;
			jj.push_back(ii);
			capacity_c_star[ii][j] = calc_star(Solid_phase[ii]->capacity[j], jj);
		}
	}
}

void CMBBlock::evaluate_capacity_c()
{
	for (unsigned int ii=0; ii<Solid_phase.size(); ii++)
	{
		capacity_c_Q[ii] = CVector(Solid_phase[ii]->n_phases);
		for (int j = 0; j < Solid_phase[ii]->n_phases; j++)
		{
			vector<int> jj;
			jj.push_back(ii);
			capacity_c_Q[ii][j] = calc(Solid_phase[ii]->capacity_c[j], jj);
		}
	}

}

void CMBBlock::evaluate_capacity_c_star()
{
	for (unsigned int ii=0; ii<Solid_phase.size(); ii++)
	{
		capacity_c_star_Q[ii] = CVector(Solid_phase[ii]->n_phases);
		for (int j = 0; j < Solid_phase[ii]->n_phases; j++)
		{
			vector<int> jj;
			jj.push_back(ii);
			capacity_c_star_Q[ii][j] = calc_star(Solid_phase[ii]->capacity_c[j], jj);
		}
	}
}

int CMBBlock::get_tot_num_phases()
{
	int out = 0;
	for (unsigned int i=0; i<Solid_phase.size(); i++)
		out+=Solid_phase[i]->n_phases;

	return out;

}

double CMBBlock::get_exchange_rate(int particule_type, int phase, int constituent)
{
	int i;
	if (particule_type == -1)
		i = lookup(RXN->cons[constituent].capacity_ptr, "soil");
	else
		i = lookup(RXN->cons[constituent].capacity_ptr, Solid_phase[particule_type]->name);
	if (i != -1)
	{
		vector<int> jj;
		jj.push_back(constituent);
		return RXN->cons[constituent].rate_exchange[i] * calc(RXN->cons[constituent].exchange_rate_scale_factor, jj);

	}

	else
		return 0;
}

double CMBBlock::get_exchange_rate_star(int particule_type, int phase, int constituent)
{
	int i;
	if (particule_type == -1)
		i = lookup(RXN->cons[constituent].capacity_ptr, "soil");
	else
		i = lookup(RXN->cons[constituent].capacity_ptr, Solid_phase[particule_type]->name);
	if (i != -1)
	{
		vector<int> jj;
		jj.push_back(constituent);
		return RXN->cons[constituent].rate_exchange[i] * calc_star(RXN->cons[constituent].exchange_rate_scale_factor, jj);
	}
	else
		return 0;
}

double CMBBlock::get_kd(int particule_type, int phase, int constituent)
{
	int i;
	if (particule_type == -1)
		i = lookup(RXN->cons[constituent].capacity_ptr, "soil");
	else
		i = lookup(RXN->cons[constituent].capacity_ptr, Solid_phase[particule_type]->name);
	if (i!=-1)
		return RXN->cons[constituent].capacity[i];
	else
		return 0;
}

void CMBBlock::set_CG(int particle_type, int phase, int constituent, double val)
{
	CG[get_member_no(particle_type, phase)][constituent] = val;
}

double &CMBBlock::_CG(int particle_type, int phase, int constituent)
{
	return CG[constituent][get_member_no(particle_type, phase)];
}

double CMBBlock::get_CG(int particle_type, int phase, int constituent)
{
	return CG[constituent][get_member_no(particle_type, phase)];
}

int CMBBlock::get_member_no(int solid_id, int phase_no)
{
	if (solid_id==-2)
		return 0;
	else if (solid_id==-1)
		return 1;
	else
	{
		int k=0;
		for (int i=0; i<solid_id; i++) k+=Solid_phase[i]->n_phases;
		return k+phase_no+2;
	}
}

int CMBBlock::get_member_no(int solid_id, int phase_no, int const_no)
{
	if (solid_id==-2)
		return const_no;
	else if (solid_id==-1)
		return const_no+int(RXN->cons.size());
	else
	{
		int k=0;
		for (int i=0; i<solid_id; i++) k+=Solid_phase[i]->n_phases*RXN->cons.size();
		return k+phase_no*RXN->cons.size()+2*int(RXN->cons.size())+const_no;
	}

}

double CMBBlock::get_rate_exchange(int particle_type, int constituent)
{
	int i;
	if (particle_type==-1)
		i = lookup(RXN->cons[constituent].rate_exchange_ptr, "soil");
	else
		i = lookup(RXN->cons[constituent].rate_exchange_ptr, Solid_phase[particle_type]->name);
	if (i==-1)
		return 0;
	else
		return RXN->cons[constituent].rate_exchange[i];
}

double CMBBlock::get_reaction_rate(int i, CVector &X, bool star)
{
	CVector X_old = get_X_from_CG();
	set_CG_star(X);
	double r;
	if (star==true)
		r = calc_star(RXN->Rxts[i].rate);
	else
		r = calc(RXN->Rxts[i].rate);
	set_CG_star(X_old);
	return r;
}

CVector CMBBlock::get_reaction_rates(CVector &X, bool star)
{
	CVector X_old = get_X_from_CG();
	set_CG_star(X);
	CVector R(RXN->Rxts.size());
	for (unsigned int i=0; i<RXN->Rxts.size(); i++)
	{	if (star==true)
			R[i] = calc_star(RXN->Rxts[i].rate);
		else
			R[i] = calc(RXN->Rxts[i].rate);
	}
	set_CG_star(X_old);
	return R;

}

CVector CMBBlock::get_reaction_rates(bool star)
{

	CVector X(RXN->Rxts.size()) ;
	for (unsigned int i=0; i<RXN->Rxts.size(); i++)
	{	if (star==true)
			X[i] = calc_star(RXN->Rxts[i].rate);
		else
			X[i] = calc(RXN->Rxts[i].rate);
	}
	return X;
}

CVector CMBBlock::get_rxn_change(bool star)
{
	CVector R = get_reaction_rates(star);
	CMatrix M = Eval_Stoichiometry(star);
	return Transpose(M)*R;
}

CVector CMBBlock::get_rxn_change(CVector &X, bool star)
{
	CVector X_old = get_X_from_CG();
	set_CG_star(X);
	CVector R = get_rxn_change(star);
	set_CG_star(X_old);
	return R;

}

CMatrix CMBBlock::Eval_Stoichiometry(bool star)
{
	CMatrix M(RXN->Rxts.size(),(n_phases+2)*RXN->cons.size());
	for (unsigned int i=0; i<RXN->Rxts.size(); i++)
		for (unsigned int j=0; j<RXN->Rxts[i].prodrates.size(); j++)
			if (star)
				M[i][get_member_no(RXN->Rxts[i].product_p_type[j], RXN->Rxts[i].product_phase[j], RXN->Rxts[i].products[j])] = calc_star(RXN->Rxts[i].prodrates[j]);
			else
				M[i][get_member_no(RXN->Rxts[i].product_p_type[j], RXN->Rxts[i].product_phase[j], RXN->Rxts[i].products[j])] = calc(RXN->Rxts[i].prodrates[j]);

	return M;


}

CVector CMBBlock::get_X_from_CG()
{
	CVector X((n_phases+2)*RXN->cons.size());

	for (unsigned int k=0; k<RXN->cons.size(); k++)
		for (int p=-2; p<int(Solid_phase.size()); p++)
		{	int _t=1; if (p>-1) _t=Solid_phase[p]->n_phases;
			for (int l=0; l<_t; l++)
				X[get_member_no(p,l,k)] = get_CG(p,l,k);
		}
	return X;
}

void CMBBlock::set_CG_star(const CVector &X)
{
	for (unsigned int k=0; k<RXN->cons.size(); k++)
		for (int p=-2; p<int(Solid_phase.size()); p++)
		{	int _t=1; if (p>-1) _t=Solid_phase[p]->n_phases;
			for (int l=0; l<_t; l++)
				CG_star[k][get_member_no(p,l)] = X.vec[get_member_no(p,l,k)];
		}

}

int CMBBlock::lookup_particle_type(string S)
{
	int out = -1;
	for (unsigned int i = 0; i < Solid_phase.size(); i++)
		if (tolower(S) == tolower(Solid_phase[i]->name))
			out = i;

	return out;
}

int CMBBlock::lookup_env_exchange(string S)
{
	int out = -1;
	for (unsigned int i = 0; i <  envexchange.size(); i++)
		if (tolower(S) == tolower(envexchange[i]->name))
			out = i;

	return out;
}

void CMBBlock::set_up_plant_growth_expressions()
{
	string s = "86400*(1.0-(f[3]/f[84]))*f[77]*f[2]*f[18]*_max((1-_exp(-0.65*f[24])):0)";
	string l_constituent;
	for (unsigned int i = 0; i < plant_prop.limiting_nutrients.size(); i++)
	{
		string CG = "cg[" + numbertostring(parent->RXN().look_up_constituent_no(plant_prop.limiting_nutrients[i])) + "]";
		l_constituent += "*(" + CG + "/(" + CG + "+f["+ numbertostring(7000+i) + "]))";
	}
	string temperature_stress = "_exp(-2*((f[19]-f[82])^2)/((f[82]-f[78])^2))";
	s = "(" + s + l_constituent + "*f[9]*" + temperature_stress +" ) - (f[80]*f[3]*_sig((f[78]-f[19])/f[79]))";
	plant_prop.plant_growth_rate_expression = CStringOP(s);

	s = "(f[75]*f[76]*_pos(f[19]-f[78])*_max((1-_exp(5.0*(f[24]-f[76]))):0)" + l_constituent + "*f[9]*" + temperature_stress + ")";
	s = s + "-(f[81]*f[24]*_sig((f[78]-f[19])/f[79]))";
	plant_prop.LAI_growth_rate_expression = s;

}

double CMBBlock::calc(CStringOP &C)
{
	return calc(C, dummy_vec);

}

double CMBBlock::calc_star(CStringOP &C)
{
	return calc_star(C, dummy_vec);
}

double CMBBlock::get_val_star(int i)
{
	return get_val_star(i, dummy_vec);
}

double CMBBlock::get_val(int i)
{
	return get_val(i, dummy_vec);
}

bool CMBBlock::set_properties(string s)
{
        bool success = true;
        vector<string> ss = split(s);
        for (unsigned int i=0; i<ss.size(); i++)
        {
            vector<string> prop = split(ss[i],'=');
            if (prop.size()!=2)
            {
                errors.push_back(string("Syntax error in '") + ss[i] + string("' in command ") + s);
                show_message(string("Syntax error in '") + ss[i] + string("' in command ") + s);
                success = false;
            }
            bool done = set_property(prop[0],prop[1]);
            if (!done)
            {
                success = false;
            }

        }

        return success;

}

bool CMBBlock::set_property(string s, double value)
{
    bool success = true;
    bool done = set_val(s,value);

    if (!done)
    {
        errors.push_back("Property " + s + " was not found");
        show_message("Property " + s + " was not found");
        success = false;
    }

    return success;
}

bool CMBBlock::set_property(string s, string value)
{
    bool success = true;
    if (tolower(trim(s))=="name") {ID = value; show_message("Property [" + s + "] was set to " + value); return success;}
    if (tolower(trim(s))=="inflow") {inflow_filename.clear(); inflow_filename.push_back(value); show_message("Property [" + s + "] was set to " + value); return success;}
	if (tolower(trim(s)) == "hs_relationship") { H_S_expression = CStringOP(value); }
    if (tolower(trim(s))=="type")
    {
        bool done = settype(value);
        if (!done)
            {success = false; show_message("Type [" + value + "] was not found!"); return success;}
        else
        {
            show_message("Property [" + s + "] was set to " + value); return success;
        }
    }
    if (tolower(trim(s))=="precipitation")
    {
        if (tolower(trim(value))=="yes")
            precipitation_swch = true;
        else
            precipitation_swch = false;
    }
    bool done = set_val(s,atof(value.c_str()));
    if (!done)
    {
        errors.push_back("Property " + s + " was not found. In " + s);
        show_message("Property " + s + " was not found. In " + s);
        success = false;
    }
    else
        show_message("Property [" + s + "] was set to " + value);

    return success;
}

void CMBBlock::show_message(string s)
{
    if (show_messages())
    {
        cout << "Block [" + ID + "]:" + s << endl;
    }
}

bool CMBBlock::show_messages()
{
    bool parent_showmessages=false;
    if (parent)
        parent_showmessages = parent->showmessages;
    if (showmessages || parent_showmessages)
        return true;
    else
        return false;
}

bool CMBBlock::settype(string s)
{
    if (tolower(trim(s))=="soil") {indicator = Block_types::Soil; return true; }
    if (tolower(trim(s))=="darcy") {indicator = Block_types::Darcy;return true; }
    if (tolower(trim(s))=="stream") {indicator = Block_types::Stream;return true; }
    if (tolower(trim(s))=="pond") {indicator = Block_types::Pond;return true; }
    if (tolower(trim(s))=="plant") {indicator = Block_types::Plant;return true; }
    if (tolower(trim(s))=="storage") {indicator = Block_types::Storage;return true; }
    if (tolower(trim(s))=="catchment") {indicator = Block_types::Catchment;return true; }

    errors.push_back("Type '" + s + " was not recognized!");
    return false;
}

string CMBBlock::gettype()
{
    if (indicator == Block_types::Soil) return "soil";
    if (indicator == Block_types::Darcy) return "darcy";
    if (indicator == Block_types::Plant) return "plant";
    if (indicator == Block_types::Pond) return "pond";
    if (indicator == Block_types::Storage) return "storage";
    if (indicator == Block_types::Stream) return "stream";
    if (indicator == Block_types::Catchment) return "catchment";

    return "";
}

string CMBBlock::tostring()
{
    string s;
    s += "Block [" + ID + "]:\n";
    s += "   Name = " + ID + "\n";
    s += "   Type = " + gettype() + "\n";
    s += "   Area = " + numbertostring(A) + "\n";
    s += "   Head = " + numbertostring(H) + "\n";
    s += "   Volume = " + numbertostring(V) + "\n";
    s += "   Storage = " + numbertostring(S) + "\n";
    s += "   Bottom Elevation = " + numbertostring(z0) + "\n";
	s += "   Moisture Content = " + numbertostring(S/V) + "\n";
    s += "   Vapor Diffusion = " + numbertostring(vapor_diffusion) + "\n";
	s += "   Bulk Density = " + numbertostring(bulk_density) + "\n";
	s += "   Depth = " + numbertostring(V/A) + "\n";
    s += "   Porosity = " + numbertostring(fs_params[theta_s]) + "\n";
    s += "   Depression Storage  = " + numbertostring(fs_params[depression_storage]) + "\n";
	s += "   Saturated Hydraulic Conductivity  = " + numbertostring(fs_params[ks]) + "\n";
    s += "   Theta_s  = " + numbertostring(fs_params[theta_s]) + "\n";
    s += "   Theta_r  = " + numbertostring(fs_params[theta_r]) + "\n";
    s += "   VG_alpha  = " + numbertostring(fs_params[vg_alpha]) + "\n";
    s += "   VG_n  = " + numbertostring(fs_params[vg_n]) + "\n";
    s += "   VG_m  = " + numbertostring(fs_params[vg_m]) + "\n";
    s += "   VG_lambda  = " + numbertostring(fs_params[lambda]) + "\n";
    s += "   Storativity  = " + numbertostring(fs_params[storativity]) + "\n";
	s += "   Storage epsilon  = " + numbertostring(fs_params[storage_epsilon]) + "\n";
    s += "   Storage n  = " + numbertostring(fs_params[storage_n]) + "\n";
    if (indicator==Block_types::Plant)
    {
        s += "   Leaf Area Index  = " + numbertostring(plant_prop.LAI) + "\n";
        s += "   Maximum Leaf Area Index  = " + numbertostring(plant_prop.LAI) + "\n";
        s += "   Leaf Area Index  = " + numbertostring(fs_params[LAI_max]) + "\n";
        s += "   Area Index Growth rate  = " + numbertostring(fs_params[K_LAI]) + "\n";
        s += "   Plant Growth rate coefficient = " + numbertostring(fs_params[plant_growth_rate_coefficient]) + "\n";
        s += "   Base Temperature = " + numbertostring(fs_params[temperature_base]) + "\n";
        s += "   Temperature Spread Factor = " + numbertostring(fs_params[temperature_spread_factor]) + "\n";
        s += "   Plant Leaf Decay Factor = " + numbertostring(fs_params[plant_leaf_decay_factor]) + "\n";
        s += "   Plant Biomass Decay Factor = " + numbertostring(fs_params[plant_biomass_decay_factor]) + "\n";
        s += "   Optimal Temperature = " + numbertostring(fs_params[optimal_temperature]) + "\n";
        s += "   Maximum Biovolume = " + numbertostring(fs_params[maximum_bio_volume]) + "\n";
    }

	s += "   Air Phase = " + numbertostring(air_phase) + "\n";
	s += "   Light reduction factor = " + numbertostring(light_reduction_factor) + "\n";

	return s;

}
