#def dotprod(X1,X2,Y1,Y2,Z1,Z2):
	
#	DOTPROD = (1.0-1.0e-15)*(X1*X2 + Y1*Y2 + Z1*Z2)

#	return DOTPROD

import math
RAD = math.pi / 180.0

class angSep:
	def __init__(self,ra1,dec1,ra2,dec2):
		self.ra1 = ra1
		self.dec1 = dec1
		self.ra2 = ra2
		self.dec2 = dec2
		
	def dotprod(self):

		X1 = math.cos(self.ra1*RAD) * math.cos(self.dec1*RAD);
		Y1 = math.sin(self.ra1*RAD) * math.cos(self.dec1*RAD);
		Z1 = math.sin(self.dec1*RAD);

		X2 = math.cos(self.ra2*RAD) * math.cos(self.dec2*RAD);
		Y2 = math.sin(self.ra2*RAD) * math.cos(self.dec2*RAD);
		Z2 = math.sin(self.dec2*RAD);

		DOTPROD = (1.0-1.0e-15)*(X1*X2 + Y1*Y2 + Z1*Z2)

		return DOTPROD
