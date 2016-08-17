#include "my_utilities.h"
#include "utilities.h"
#include <math.h>

int randInt(int a, int b){
	
	// handle case of negative input
	a = abs(a);
	b = abs(b);

	int span = abs(b - a);

	return randInt(span + 1) + a;
}