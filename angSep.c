#include "angSep.h"
#include "math.h"
#include <Python.h>

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
  PyObject *pName, *pModule, *pDict, *pFunc, *pValue;
  
  // ------------- BEGIN ------------------

  // initialize?  
  Py_Initialize();
  
  // Build the name object
  pName = PyUnicode_FromString("dotprod");

  // Load the module object
  pModule = PyImport_Import(pName);

  // pDict is a borrowed reference 
  pDict = PyModule_GetDict(pModule);

  // pFunc is also a borrowed reference 
  pFunc = PyDict_GetItemString(pDict, "dotprod");
  
  X1 = cos(RA1*RAD) * cos(DEC1*RAD);
  Y1 = sin(RA1*RAD) * cos(DEC1*RAD);
  Z1 = sin(DEC1*RAD);

  X2 = cos(RA2*RAD) * cos(DEC2*RAD);
  Y2 = sin(RA2*RAD) * cos(DEC2*RAD);
  Z2 = sin(DEC2*RAD);

  //DOTPROD = (1.0-1.0E-15)*(X1*X2 + Y1*Y2 + Z1*Z2);

  pValue = PyObject_CallFunction(pFunc, "dddddd", X1,X2,Y1,Y2,Z1,Z2); //PyObject *arg);
  DOTPROD = PyFloat_AsDouble(pValue);
  
  sep = acos(DOTPROD)/RAD ; // angular sep, degrees

  // Clean up
  Py_DECREF(pModule);
  Py_DECREF(pName);
  Py_DECREF(pDict);
  Py_DECREF(pFunc);
  
  // Finish the Python Interpreter
  int Py_FinalizeEx();
  
  return (sep * scale) ;
  
}
