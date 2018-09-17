#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "angSep.h"
#include <Python.h>

//compilation:
//gfortran -I/anaconda2/envs/python3/lib/python3.5/site-packages/numpy/core/include -I/anaconda2/envs/python3/include/python3.5m -framework python angSep.c

struct {
  int NDUM1, NDUM2;
  double ARRAY_DUM1[3] ;
  double ARRAY_DUM2[3] ;
  
} TEST ;


int main() {
  double RA1  = 22.0 ;
  double DEC1 = -4.0 ;
  double RA2  = -22.1 ;
  double DEC2 = -4.1 ;
  double SCALE = 1.0 ;
  
  double ANGSEP;

  ANGSEP = angSep(RA1,DEC1,RA2,DEC2, SCALE);

  printf(" ANGSEP(test) = %le \n", ANGSEP);
  
} // end main


double angSep( double RA1,double DEC1,
               double RA2,double DEC2, double  scale) {

  // Copied from DIFFIMG on Nov 16 2015
  //
  // Oct 9, 2012 R. Kessler
  // for input coords of point 1 (RA1,DEC1) and point 2 (RA2,DEC2),
  // return angular separation. Inputs are in degrees and output
  // is in degrees x scale ->
  // * scale = 1    -> output is in degrees
  // * scale = 60   -> output is in arcmin
  // * scale = 3600 -> output is in arcsec

  double X1,Y1,Z1, X2, Y2, Z2, DOTPROD, sep;
  double RAD = RADIAN ;
  PyObject *pName, *pModule, *pDict, *pFunc;//, *pValue;
  PyObject *pmod, *pinst, *pValue, *pmeth, *pargs, *pclass, *pinit, *pret;
  
  Py_Initialize();
  pmod   = PyImport_ImportModule("angsep_class");
  if (pmod == NULL) {
    printf("ERROR importing class");
    exit(-1);
    }
  pclass = PyObject_GetAttrString(pmod, "angSep");
  if (pclass == NULL) {
    printf("ERROR importing module");
    exit(-1);
    }
  Py_DECREF(pmod);

  pargs  = Py_BuildValue("dddd",RA1,DEC1,RA2,DEC2);
  pinst  = PyEval_CallObject(pclass, pargs);
  if (pinst == NULL) {
    printf("ERROR running module");
    exit(-1);
    }
  
  Py_DECREF(pclass);
  Py_DECREF(pargs);
    
  X1 = cos(RA1*RAD) * cos(DEC1*RAD);
  Y1 = sin(RA1*RAD) * cos(DEC1*RAD);
  Z1 = sin(DEC1*RAD);

  X2 = cos(RA2*RAD) * cos(DEC2*RAD);
  Y2 = sin(RA2*RAD) * cos(DEC2*RAD);
  Z2 = sin(DEC2*RAD);

  DOTPROD = (1.0-1.0E-15)*(X1*X2 + Y1*Y2 + Z1*Z2);

  pmeth  = PyObject_GetAttrString(pinst, "dotprod");
  pValue   = PyEval_CallObject(pmeth, NULL);
  DOTPROD = PyFloat_AsDouble(pValue);
  
  sep = acos(DOTPROD)/RAD ; // angular sep, degrees

  Py_DECREF(pinst);
  Py_DECREF(pmeth);
  Py_DECREF(pValue);
  
  // Finish the Python Interpreter
  int Py_FinalizeEx();
  
  return (sep * scale) ;
  
}
