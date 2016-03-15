/***

1. (10 points) Measure the cost of a minimal function call in C/C++ (e.g., X seconds). The minimal cost can be emulated by measuring a bare function call that neither takes any parameter nor does anything inside the function

***/

void minimal_function(void);
int main(int argc, char *argv[]){
	/* #1 */
	minimal_function();
	return 0;
}

void minimal_function(void){
	return;
}

