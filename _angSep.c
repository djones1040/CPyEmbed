#include <Python.h>
#include <numpy/arrayobject.h>
#include "angSep.h"

static char module_docstring[] =
    "This module provides an interface for calculating angular separation using C";
static char angSep_docstring[] =
    "Calculate angular separation";

static PyObject *angSep_angSep(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
    {"angSep", angSep_angSep, METH_VARARGS, angSep_docstring},
    {NULL, NULL, 0, NULL}
};


PyMODINIT_FUNC PyInit__angSep(void)
{
  PyObject *module;
  static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "_angSep",
    module_docstring,
    -1,
    module_methods,
    NULL,
    NULL,
    NULL,
    NULL
  };

  module = PyModule_Create(&moduledef);
  if (!module) return NULL;

  /* Load `numpy` functionality. */
  import_array();

  return module;
  
}

static PyObject *angSep_angSep(PyObject *self, PyObject *args)
{
  double ra1, dec1, ra2, dec2, scale;
  
  if (!PyArg_ParseTuple(args, "ddddd", &ra1, &dec1, &ra2, &dec2,
			&scale))
    return NULL;
  
  double sep = angSep(ra1,dec1,ra2,dec2,scale);
  
  if ((sep < 0.0) || (sep != sep)) {
    PyErr_SetString(PyExc_RuntimeError,
                    "sep returned an impossible value.");
    return NULL;
  }
  
  PyObject *ret = Py_BuildValue("d", sep);
    return ret;
  
}
