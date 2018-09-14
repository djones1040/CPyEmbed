'''dotprod.py - Python source designed to '''
'''demonstrate the use of python embedding'''

def dotprod(X1,X2,Y1,Y2,Z1,Z2):
	
	DOTPROD = (1.0-1.0e-15)*(X1*X2 + Y1*Y2 + Z1*Z2)

	return DOTPROD
