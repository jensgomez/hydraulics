#pragma once
#include <iostream>
#include <cmath>
#include <fstream>

class pipe{
public:
	pipe();
	void input_args(double a, double b, double c);
	double calc_dp(void);
	double calc_fric(void);
	void print_calc(void);
	~pipe();

private:
	double dia = 0.0;
	double area = 0.0;
	double dp = 0.0;
	double l = 0.0;
	double k = 0.0;
	double q = 0.0; 
	double vel = 0.0; 
	double rho = 0.0; 
	double f = 0.0;
	double re = 0.0;
	double eps = 0.0;
	
	int err_arg;
	int eqn_choice;


	const double pi = 4.0 * atan(1.0);
	const double gc = 386.4;

	
};

pipe::pipe(){
	std::cout << "PIPE CALCULATIONS" << std::endl << std::endl;
}

// Input function
// a => volumetric flow rate (q)
// b => diameter (dia)
// c =? length (l)
void pipe::input_args(double a, double b, double c) {
	if (a <= 0 || b <= 0) {
		std::cout << "ERROR! INPUT ARGUMENTS LESS THAN OR EQUAL TO ZERO!" << std::endl;
		err_arg = 1;
	}

	else {
		q = a;
		dia = b;
		l = c;
		eqn_choice = 1;
		err_arg = 0;
	}
}


// Calculate pressure drop
// dp = (k/a**2 + f*l/d)*(rho*l*v**2)/(2*gc)
double pipe::calc_dp(void) {
	if (err_arg != 0) {
		std::cout << "ERROR! SEE ABOVE ERROR MESSAGES. CALCULATIONS NOT PERFORMED FOR PRESSURE DROP.";
		return -1.0;
	}

	//	Only perform calculations if error argument (err_arg) is zero
	if (err_arg == 0) {
		area = pi * (pow(dia, 2) / 4.0);
		vel = q / area;
		rho = 1e3;
		f = calc_fric();
		dp = (k + f * l / dia) * rho * pow(vel, 2) / (2 * gc);
		
		return dp;
	}

}


// Calculate friction factor
double pipe::calc_fric(void) {


	// Reynolds number
	re = 4e3;

	// Pipe roughness
	eps = 0.0025;


	// Solve friction factor....assuming turbulent flow	
	double fric = 0.0;
	// IMPLEMENT Colebrook–White equation	
	if (eqn_choice == 0) {
		
	}

	// Haaland equation	
	else if (eqn_choice == 1) {
		fric = -1.0 / (1.8 * log10(pow((eps / dia / 3.7), 1.11) + 6.9 / re));
	}

	return fric;
}


// Write to text
void pipe::print_calc(void){
	std::ofstream outputfile;
	outputfile.open("output.txt");
	outputfile.precision(3);
	outputfile << "INPUTS: \n";
	std::fixed;
	outputfile << "VOLUMETRIC FLOW RATE (Q) = " << q << "\n";
	outputfile << "PIPE DIAMETER      (DIA) = " << dia << "\n";
	outputfile << "PIPE LENGTH          (L) = " << l << "\n\n\n";

	outputfile << "ASSUMPTIONS: \n";
	outputfile << "REYNOLDS NUMBER          = " << re << "\n";
	outputfile << "PIPE SURFACE ROUGHNESS   = " << eps << "\n";
	outputfile << "FRICTION EQUATION:  ";
	if (eqn_choice == 1) {
		outputfile << "HAALAND EQUATION\n";
	}
	outputfile << "DENSITY                  = " << rho << "\n\n\n";

	outputfile << "CALCULATED VARIABLES: \n";
	outputfile << "VELOCITY                 = " << vel << "\n";
	outputfile << "FRICTION FACTOR          = " << f << "\n";
	outputfile << "PRESSURE DROP            = " << dp << "\n";

}



pipe::~pipe(){
}