// fluidfriction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "pipe.h"

int main(){
    
	std::cout << "Hello World!\n"; 
	pipe p1;

	double q = 1.00;
	double dia = 1.0;
	double l = 2.0;
	p1.input_args(q, dia, l);
	p1.calc_dp();
	p1.print_calc();



	return 0;

}

