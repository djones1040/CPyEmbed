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
