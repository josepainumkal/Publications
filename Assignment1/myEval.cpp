#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

// This function takes a vector as input
// returns 100, only when input vector contains the bit value 1 at all index positions that are
// multiples of 13 and rest of the bits are 0.
// For all other vectors, the return value will be 50

double eval(int *vec){
	int sumOfPrimeOnes;
	int sumOfZeroes;

	for(int i=0;i<100;i++){
        if(vec[i]==0){
            sumOfZeroes++;
        }
		if((i%13)==0){
              if(vec[i]==1){
                 sumOfPrimeOnes++;
              }
		}
	}

	if((sumOfZeroes+sumOfPrimeOnes)==100){
           return 100; 
	}else{
	   return 50;
	}
}

