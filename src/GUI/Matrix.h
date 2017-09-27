// Matrix.h: interface for the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <iostream>
#include <math.h>
#define ARMA_DONT_PRINT_ERRORS
#include "armadillo"
class QVariant;
//class QString;
//class QList;
#include <QMap>
#include "Matrix_arma.h"
#include "Vector_arma.h"

using namespace arma;
class CVector;
class CMatrix  
{
friend class D5Matrix;
private:
	int numrows;
	int numcols;
	int range(int);
public:
	vector<CVector> matr;
	CMatrix(int, int);
	CMatrix(int);
	CMatrix();
	CMatrix(const CMatrix&);
	CMatrix(CMatrix_arma&);
	CMatrix(const CVector&);
	CVector& operator[](int);
    int Cgetnumrows() const;
    int Cgetnumcols() const;
	virtual ~CMatrix();
    CMatrix& operator=(const CMatrix&);
    CMatrix& operator+=(const CMatrix&);
    CMatrix& operator-=(const CMatrix &);
    CMatrix& operator=(mat&);
	friend CMatrix mult(CMatrix&, CMatrix&);
	friend CVector mult(CMatrix&, CVector&);
	friend CVector mult(CVector&, CMatrix&);
	friend void triangulate(CMatrix&, CVector&);
	friend void backsubst(CMatrix&, CVector&, CVector&);
	friend CVector gauss0(CMatrix, CVector);
	friend CVector diag(CMatrix);
	friend CMatrix Cholesky_factor(CMatrix &M);
	friend CMatrix LU_decomposition(CMatrix &M);
    CMatrix CLU_decomposition();
    CMatrix CCholesky_factor();
    double Cdet();
    void CPrint(FILE *FIL);
    void Cprint(string s);
    void Csetval(double a);
    void Csetvaldiag(double a);
    void Cwritetofile(FILE *f);
    void Cwritetofile(string filename);
    void Cwritetofile_app(string filename);
	friend void write_to_file(vector<CMatrix> M, string filename);
	friend CMatrix Average(vector<CMatrix> M);
    CVector Cdiag_ratio();
    vector<vector<bool>> Cnon_posdef_elems(double tol = 1);
    CMatrix Cnon_posdef_elems_m(double tol = 1);
    CMatrix CPreconditioner(double tol = 1);
	vector<string> toString(string format = "", vector<string> columnHeaders = vector<string>(), vector<string> rowHeaders = vector<string>());
	vector<string> toHtml(string format = "", vector<string> columnHeaders = vector<string>(), vector<string> rowHeaders = vector<string>());
    void Csetnumcolrows();

    QMap<QString, QVariant> Ccompact() const;
    static CMatrix CunCompact(QMap<QString, QVariant>);

};
	
double det(CMatrix &);
CMatrix Log(CMatrix &M1);
CMatrix Exp(CMatrix &M1);
CMatrix Sqrt(CMatrix &M1);
CMatrix operator+(const CMatrix&, const CMatrix&);
CMatrix operator+(double, CMatrix);
CMatrix operator+(CMatrix, double);
CMatrix operator-(double d, CMatrix m1);
CMatrix operator+(CMatrix m1, double d);
CMatrix operator-(CMatrix m1,double d);
CMatrix operator/(CMatrix m1,double d);
CMatrix operator/(double d, CMatrix m1);
CMatrix operator-(const CMatrix&, const CMatrix&);
CMatrix operator*(CMatrix&, CMatrix&);
CVector operator*(CMatrix&, CVector&);
CMatrix operator*(CVector, CMatrix);
CMatrix operator*(double, CMatrix);
CVector operator/(CVector&, CMatrix&);
CMatrix Transpose(CMatrix &M1);
CMatrix Invert(CMatrix M1);
CVector SpareSolve(CMatrix, CVector);
CMatrix oneoneprod(CMatrix &m1, CMatrix &m2);
CVector solve_ar(CMatrix&, CVector&);
CMatrix inv(CMatrix&);
CMatrix normalize_diag(CMatrix&, CMatrix&);
CVector normalize_diag(CVector&, CMatrix&);
CMatrix Identity(int rows);


