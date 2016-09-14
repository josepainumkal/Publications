#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;
std::ofstream out;

double eval(int *pj);

int add[100];
int modeChange=0;

void printArray(int *vec){
    for(int z=0; z<100; z++) {
             cout<<vec[z];
    }
    cout<<"\n";
}

void copyArray(int* copyTo, int* copyFrom){
  for(int i=0;i<100;i++){
     copyTo[i] = copyFrom[i];
  }
}

//Flip rightmost 1 in the vector to 0 
int flipLeftmostZero(int *vec){
  int pos = -1;
  int z=0;

  for(z=0; z<=100; z++) {
        if(vec[z]==0){
           pos = z;
           break;
        }
    }

    if(pos==-1){
       pos = 99;
       vec[pos]=0;
    }else if(pos>0){
      pos = pos-1;
      vec[pos]=0;
    }

    return pos;
}

//Function used for printing the fitness to a text file for debugging
void printToFile(int fbest, int *sbest){
  out.open("evResults.txt", std::ios::app);
            std::string str = "\nFitness_Best:";
            out<< str;
            out<< fbest;

            std::string str2 = "\nCurrent_Vector:";
               out<<str2;
               for(int i=0;i<100;i++){
                 out<< sbest[i];
            }
            out.close();
}

//Init function: Initializing the vector to 100 1's.  
void init(int* vec, int* add, int* sum){
 
   for(int i = 0; i < 100; i++){
      vec[i] = 1;
      sum[i] = 0;
      add[i] = 0;
    }

    add[99] = 1;
}

void subtractBinary(int *sold, int *sub){
  int diff[100];
  for(int i = 99; i >= 0; i--){
        diff[i] = sold[i] - sub[i];
        if(diff[i] < 0){
            sold[i-1] = sold[i-1] - 1;
        }
        diff[i] = fabs(diff[i]%2);
    }
    copyArray(sold,diff);
}

// Function to increment the vector by one (binary addition by 1)
void addBinary(int *vec, int *add, int *sum){
    int i, c = 0;
    for(i = 99; i >=0 ; i--){
       sum[i] = ((vec[i] ^ add[i]) ^ c); // c is carry
       c = ((vec[i] & add[i]) | (vec[i] & c)) | (add[i] & c);
    }

    sum[i] = c;
    copyArray(vec,sum);
}

// The modify function used for climbing the hill step by step.
int modify(int *vec, int *add, int *sum ){
  int pos = flipLeftmostZero(vec);
  //subtractBinary(vec,add);
  return pos; 
}

int main()
{
    std::ofstream out;
    int pos=0;
    double fbest=0,fnew=0;
    int vec[100], sum[100], sbest[100], sold[100];

    init(vec,add,sum);
    fbest = eval(vec);  
    copyArray(sbest, vec); //sbest = vec;

    int stopAllLoop=0;


    while(fbest!=100 && stopAllLoop==0){
        //sold=sbest;
        if(stopAllLoop==1){
          break;
        }

        copyArray(sold, sbest);
        pos = modify(sold,add,sum);
        fnew = eval(sold);
		
        if(fnew>=fbest){
            fbest = fnew;
            copyArray(sbest,sold); //sbest= sold;
            cout<<"\nFITNESS = "<<fbest << endl;
        }
        else{
            for(int j=99;j>pos;j--){
                //if(j%2==0)
                sold[j]=1;
                for(int q=0;q<pow(2,10);q++){
                    addBinary(sold,add,sum);
                    printArray(sold);
                    fnew =eval(sold);
                    if(fnew>=fbest){
                        fbest = fnew;
                        cout<<"\nFITNESS = "<<fbest << endl;
                        copyArray(sbest,sold); //sbest= sold;   
                      }
                }
            }
            if(fnew<fbest){
                stopAllLoop=1;
            }
              
        }
    } 
            
    return 0;
  }
