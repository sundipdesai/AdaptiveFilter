#include <iostream>
#include <fstream>
#include <iomanip>
#include "dataStruct.h"
#include "utilities.h"


using namespace std;

int main()
{

	ifstream fin1("fhb.txt");

	// Allocate memory on the heap due to large
	// data set
	double *dptr = new double[numSamples];

	for (int i = 0; i < numSamples; i++) {

		 fin1 >> *(dptr + i);
	 }
	 
	 fin1.close();

	 ifstream fin2("mhb.txt");

	 // Allocate memory on the heap due to large
	 // data set
	 double *mptr = new double[numSamples];

	 for (int i = 0; i < numSamples; i++) {

		 fin2 >> *(mptr + i);
	 }

	 fin2.close();

	// Instantiate NodeList Objects
    	NodeList noiseNode;
	NodeList filterCoeffs;

	// Node pointers to head nodes
	Node * f = filterCoeffs.head;
	Node * n = noiseNode.head;

	// Output of filter
	double* yptr = new double[numSamples];

	// Error signal between reference signal and desired+noise signal
	double* eptr = new double [numSamples];

	// Simulation Loop
	int j = 0;

	while (j < numSamples) {
		//Push a single measurement to stream
		n = noiseNode.push( *(mptr + j) ); 

		//Filter measurements
		*(yptr+j) = filter(f, n);

		//Adaptive Filter Error
		*(eptr+j) = *(dptr + j) - *(yptr+j);

		//Update Filter Coefficients, 
		//output head node of coefficient stream
		f = adapt(f, n, *(eptr+j));

		j++;
	}

	// Spool data to text file 
	ofstream myfile;
	myfile.open("yout.txt");
	myfile << "error" << setw(15) << "\n";


	for (int i = 0; i < numSamples; i++) {

		// Capture output, y, to file
		myfile << *(eptr+i) << "\n";

	}
	
	myfile.close();

	return 0; 


}
