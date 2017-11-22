#pragma once
#include "BTC.h"
#include <vector>
#include "Vector.h"

class CBTCSet
{
public:
	CBTCSet(void);
	CBTCSet(int n);
	CBTCSet(int numberofBTCs, int sizeofBTCvector);
	CBTCSet(const CBTCSet &BTC);
	CBTCSet(const CBTC &BTC);
	CBTCSet(string filename, bool varytime);
	int nvars;
	vector<CBTC> BTC;
	void writetofile(char outputfile[]);
	int maxnumpoints();
	CBTCSet& operator = (const CBTCSet &C);
	vector<string> names;
	bool unif;
	void writetofile(string outputfile, bool writeColumnHeaders = false);
	void writetofile(string outputfile, int writeinterval);
	vector<double> interpolate(double t);
	vector<double> interpolate(double t, int fnvars);
	void getfromfile(string filename, bool varytime);
	double maxtime();
	double mintime();
	vector<double> getrandom();
	vector<double> percentile(double x);
	vector<double> mean(int limit);
	vector<double> mean(int limit, vector<int> index);
	vector<double> std(int limit);
	vector<double> std(int limit, vector<int> index);
	CMatrix correlation(int limit, int n);
	vector<double> integrate();
	vector<double> average();
	vector<double> percentile(double x, int limit);
	vector<double> percentile(double x, int limit, vector<int> index);
	vector<double> getrandom(int burnin);
	void append(double t, vector<double> c);
	CBTC add(vector<int> ii);
	CBTC add_mult(vector<int> ii, vector<double> mult);
	CBTC add_mult(vector<int> ii, CBTCSet &mult);
	CBTC divide(int ii, int jj);
	CBTCSet make_uniform(double increment, bool assgn_d=true);
	CBTCSet getpercentiles(vector<double> percents);
	CVector out_of_limit(double limit);
	CBTCSet distribution(int n_bins, int n_columns, int limit);
	CBTCSet add_noise(vector<double> std, bool logd);
	void clear();
	vector<double> max_wiggle();
	vector<double> max_wiggle_corr(int _n = 10);
	vector<int> max_wiggle_sl(int ii, double tol);
	CBTCSet getflow (double A);
	void knockout(double t);
	int lookup(string S);
	vector<double> getrow(int a);
	void setname(int i, string name);

	//Sassan
	bool file_not_found=false;
	CBTC &operator[](int index);
	CBTC &operator[](string BTCName);
	CBTC &operator[](QString BTCName) {
		return operator[](BTCName.toStdString());
	}
	CBTCSet(vector < vector<double>> &, int writeInterval = 1);
	int indexOf(const string& name) const;
	void pushBackName(string name);
	void append(CBTC &BTC, string name = "");
	CBTCSet sort(int burnOut = 0);
	void compact(QDataStream &data) const;
	static CBTCSet unCompact(QDataStream &data);
	~CBTCSet(void);
};

double diff(CBTCSet B1, CBTCSet B2);
CBTCSet operator * (const CBTCSet &BTC, const double &C);
CVector norm2dif(CBTCSet &A, CBTCSet &B);
CBTCSet merge(CBTCSet A, const CBTCSet &B);
CBTCSet merge(vector<CBTCSet> &A);
CVector sum_interpolate(vector<CBTCSet> &BTC, double t);
double sum_interpolate(vector<CBTCSet> &BTC, double t, string name);
int max_n_vars(vector<CBTCSet> &BTC);