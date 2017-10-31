
#pragma once


#include <string>
#include <vector>
#include "QuickSort.h"
#include "NormalDist.h"

//GUI
#include "qlist.h"
#include "qmap.h"
#include "qvariant.h"



using namespace std;


class CBTC  
{
public:
	bool structured;
	CBTC();
	CBTC(int n);
	virtual ~CBTC();
	int n;
	vector<double> t;
	vector<double> C;
	
	string name = "";
	string unit = "";
	string defaultUnit = "";
	vector<string> unitsList;

	//MM
	vector<double> D;

	double interpol(double x); //interpolate at location x
	CBTC MA_smooth(int span); //Moving average smoothing with span of 1+2*span
	double interpol_D(double x); //interpolate the distance to the next non-zero data point
	CBTC interpol(vector<double> x); //interpolate at each value in vector x
	CBTC interpol(CBTC &x); //interpolate at times in the time axis of x
	CBTC(const CBTC &C); 
	CBTC(string Filename); //create BTC based on the filename
	CBTC& operator = (const CBTC &C);
	void readfile(string); //read the values from a text file
	void writefile(string Filename); //writes the BTC contets into a fild
	double maxC(); //returns the maximum value
	double minC(); //returns the minimum value
	void setnumpoints(int); //resize the timeseries
	CBTC Log(); //take the log of all the data points
	CBTC Log(double min); //log(min(min,C))
	double std(); //standard deviation of C
	double mean(); //mean of C
	double percentile(double x); //x^th percentile of C
	double percentile(double x, int limit); //x^th percentile with the exception of the first "limit" data points
	double mean(int limit); // mean of the data after excluding "limit" data points
	double std(int nlimit); // standard deviation of the data after excluding "limit" data points
	double mean_log(int limit); //mean of log transformed data after excluding "limit" data points
	double integrate(); // integral of the time series
	double integrate(double t); //integral from the begining to time t
	double integrate(double t1, double t2); //integral between time t1 and t2
	int lookupt(double t); // finds the index of the datapoint with time t
	double average(); //integral of time-series devided by the domail length
	double average(double t); // integral to time t devided by domain length
	double slope(double tt); //slope of time-series at time tt
	CBTC distribution(int n_bins, int limit); //extract the histogram of values
	void append(double x); //appends a data point with value x
	void append(double tt, double xx); //appends a datapoint with value xx at time tt
	void append(CBTC &CC);// appends a time-series to the time-series
	CBTC& operator+=(CBTC &v); //adds another time-series to the existing one
	CBTC& operator%=(CBTC &v); //adds another time-series by corresponding indexes
	CBTC make_uniform(double increment); //create a new time-series with uniformly distributed time-axis
	CBTC extract(double t1, double t2); //extracts a sub time-series from t1 to t2.
	vector<double> trend(); //calculate the slope based on regression
	double mean_t(); //mean of t values of data point
	CBTC add_noise(double std, bool); //adds Gaussian noise to values 
	void assign_D(); //Assign distances to the next non-zero values
	void clear(); // clears the time-series
	double wiggle(); //calculate oscillation
	double wiggle_corr(int _n=10); 
	bool wiggle_sl(double tol);
	double maxfabs();
	double max_fabs;
	void knock_out(double t);
	double AutoCor1(int i=0);
	bool file_not_found = false;
	CBTC getcummulative();
	CBTC Exp();
	CBTC fabs();
	//GUI 
	//QList <QMap <QVariant, QVariant>> compact() const;
	CBTC(QList <QMap <QVariant, QVariant>> data);
	CBTC(double a, double b, const vector<double>&x);
	CBTC(double a, double b, const CBTC &btc);
	CBTC(const vector<double> &t, const vector<double> &C);
	CBTC(vector<double>&, int writeInterval = 1);
	bool error = false;

	void compact(QDataStream &data) const;
	static CBTC unCompact(QDataStream &data);

};

double diff(CBTC &BTC_p, CBTC &BTC_d);
double diff_abs(CBTC &BTC_p, CBTC &BTC_d);
double diff_log(CBTC &BTC_p, CBTC &BTC_d, double lowlim);
double diff_norm(CBTC &BTC_p, CBTC &BTC_d);
double diff(CBTC BTC_p, CBTC BTC_d, int scale);
double diff(CBTC BTC_p, CBTC BTC_d, CBTC Q);
double diff2(CBTC BTC_p, CBTC BTC_d);
double diff_mixed(CBTC &BTC_p, CBTC &BTC_d, double lowlim, double std_n, double std_ln);
double ADD(CBTC &BTC_p, CBTC &BTC_d);
double diff_relative(CBTC &BTC_p, CBTC &BTC_d, double m);
double R2(CBTC BTC_p, CBTC BTC_d);
double R(CBTC BTC_p, CBTC BTC_d, int nlimit);
CBTC operator*(double, CBTC&);
CBTC operator*(CBTC&, double);
CBTC operator*(CBTC&, CBTC&);
CBTC operator/(CBTC&, CBTC&);
CBTC operator+(CBTC&, CBTC&);
CBTC operator-(CBTC&, CBTC&);
CBTC operator%(CBTC&, CBTC&);
CBTC operator&(CBTC&, CBTC&);
CBTC operator>(CBTC& BTC1, CBTC& BTC2);
double XYbar(CBTC& BTC_p, CBTC &BTC_d);
double X2bar(CBTC& BTC_p, CBTC &BTC_d);
double Y2bar(CBTC& BTC_p, CBTC &BTC_d);
double Ybar(CBTC &BTC_p, CBTC &BTC_d);
double Xbar(CBTC &BTC_p, CBTC &BTC_d);
CBTC operator+(CBTC &v1, CBTC &v2); 
double prcntl(vector<double> C, double x);
vector<double> prcntl(vector<double> C, vector<double> x);
double sgn(double val);
int sgn(int val);
double sum_interpolate(vector<CBTC>, double t);
double R2_c(CBTC BTC_p, CBTC BTC_d);
double norm2(CBTC BTC1);
CBTC max(CBTC A, double b);
//GUI
map<string, double> regression(vector<double> x, vector<double> y);
