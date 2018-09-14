#!/usr/bin/env python
import sys

if __name__ == "__main__":
	import _angSep
	ra1,dec1,ra2,dec2 = sys.argv[1:]
	ra1,dec1,ra2,dec2 = float(ra1),float(dec1),float(ra2),float(dec2)

	sep = _angSep.angSep(ra1,dec1,ra2,dec2,1)
	print('coords (%.7f,%.7f) and (%.7f,%.7f) separated by %.2f degrees'%(ra1,dec1,ra2,dec2,sep))
