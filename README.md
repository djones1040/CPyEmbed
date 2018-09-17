python/C embedding example.  Python calls C, that in turn calls a python 
function, to compute angular separation between two sets of RA/Dec coords.  To run:

```
python setup.py build_ext --inplace
python runAngSep.py ra1 dec1 ra2 dec2
```

After making changes:
```
git add <changed_filenames>
git commit -m 'description of changes'
git push
```

For compiling the C code alone with, need the python and numpy include directories.  On my computer, for example:

```
gfortran -I/anaconda2/envs/python3/lib/python3.5/site-packages/numpy/core/include -I/anaconda2/envs/python3/include/python3.5m angSep_noPython.c
```
