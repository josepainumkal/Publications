
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <limits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <algorithm>
using namespace std;

/*
1. Randomly select a swath of alleles from parent 1 and copy them directly to the child. Note the indexes of the segment.
2. Looking in the same segment positions in parent 2, select each value that hasn't already been copied to the child.
   A. For each of these values:
            I)   Note the index of this value in Parent 2. Locate the value, V, from parent 1 in this same position.
            II)  Locate this same value in parent 2.
            III) If the index of this value in Parent 2 is part of the original swath, go to step i. using this value.
            IV)  If the position isn't part of the original swath, insert Step A's value into the child in this position.
3. Copy any remaining positions from parent 2 to the child. 
Source: http://www.rubicite.com/Tutorials/GeneticAlgorithms/CrossoverOperators/PMXCrossoverOperator.aspx

Below is my implementation of the above logic
*/

int locateInP2(int findValue, int *p2){
	  int found=0;
	  for(int i=0;i<10;i++){
		  if(p2[i] == findValue ){
			  found=1;
        return i;
		}
	}
}

void doStepA(int i, int *p2, int *p1, int *c1, int xp1, int xp2, int insertValue){
	int valueinP1 = p1[i];

	//Locate this same value in parent 2.
	int pos = locateInP2(valueinP1, p2);

	if(pos>= xp1 && pos<= xp2){
		doStepA(pos, p2, p1, c1, xp1, xp2, insertValue);
	}else{
        c1[pos] =  insertValue;
	}
}

void PMXCrossover(int xp1, int xp2, int *p1, int *p2, int *c1){

    int foundInC1 =0;
	  for(int i=xp1;i<=xp2;i++){
      c1[i] = p1[i];
    }

    for(int i=xp1;i<=xp2;i++){
  	   foundInC1 = 0;
   	   for(int j=xp1;j<=xp2;j++){
   	  	  if(p2[i] == c1[j]){
            foundInC1 = 1;
            break;
   	  	  }
   	    }
        // p2[i] not found in C1
   	    if(foundInC1 == 0){
   	  	  doStepA( i, p2, p1, c1, xp1, xp2, p2[i]);
   	    }
    }

    //Copy any remaining positions from parent 2 to the child.
    for(int i=0;i<10;i++){
   	   if(c1[i]==88){
   	  	   c1[i]=p2[i];
   	  }
    }
}


int main(){
   int p1[10] = {9,8,4,5,6,7,1,3,2,10};
   int p2[10] = {8,7,1,2,3,10,9,5,4,6};
   //Unknown elements are marked as 88
   int c1[10] = {88,88,88,88,88,88,88,88,88,88};
   int c2[10] = {88,88,88,88,88,88,88,88,88,88};

   int max=9,min=0;
   int t1 = rand()%(max-min + 1) + min;
   int t2 = rand()%(max-min + 1) + min;
   int xp1 = std::min(t1, t2);
   int xp2 = std::max(t1, t2);

   xp1 = 3; xp2 = 5;
   int foundInC1 = 0, valueinP1 =0, foundInP2=0; 

   PMXCrossover(xp1, xp2, p1, p2, c1);
   PMXCrossover(xp1, xp2, p2, p1, c2);


   cout<<"\nP1: ";
   for(int i=0;i<10;i++){
      cout<<p1[i]<<"\t";
   }

   cout<<"\nP2: ";
   for(int i=0;i<10;i++){
      cout<<p2[i]<<"\t";
   }

   cout<<"\nC1: ";
   for(int i=0;i<10;i++){
      cout<<c1[i]<<"\t";
   }

   cout<<"\nC2: ";
   for(int i=0;i<10;i++){
      cout<<c2[i]<<"\t";
   }
   cout<<endl;
   return 0;
}
