
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <stdlib.h>
using namespace std;
std::ofstream out;

double eval(int *pj);

int gpos = 0;
int totalRun=0;

int add[150];
int modeChange=0;

void printArray(int *vec){
    for(int z=0; z<150; z++) {
             cout<<vec[z];
    }
    cout<<"\n";
}

void copyArray(int* copyTo, int* copyFrom){
  for(int i=0;i<150;i++){
     copyTo[i] = copyFrom[i];
  }
}


//Function used for printing the fitness to a text file for debugging
void printToFile(int fbest, int *sbest){
  out.open("evResults.txt", std::ios::app);
            std::string str = "\nFitness_Best:";
            out<< str;
            out<< fbest;

            std::string str2 = "\nCurrent_Vector:";
               out<<str2;
               for(int i=0;i<150;i++){
                 out<< sbest[i];
            }
            out.close();
}

//Init function: Initializing the vector to 100 1's.
void init(int* vec, int* add, int* sum){

   for(int i = 0; i < 150; i++){
      vec[i] = 0;
      sum[i] = 0;
      add[i] = 0;
    }

    add[149] = 1;
}


// Function to increment the vector by one (binary addition by 1)
void addBinary(int *vec, int *add, int *sum){
    int i, c = 0;
    for(i = 149; i >=0 ; i--){
       sum[i] = ((vec[i] ^ add[i]) ^ c); // c is carry
       c = ((vec[i] & add[i]) | (vec[i] & c)) | (add[i] & c);
    }

    sum[i] = c;
    copyArray(vec,sum);
}

// The modify function used for climbing the hill step by step.
int modify(int *vec, int *add, int *sum ){
  //int pos = flipLeftmostZero(vec);
  //subtractBinary(vec,add);
  for(int i=0;i<1024;i++){
    addBinary(vec, add, sum);
  }
 
  return 0;
}

int main()
{
    std::ofstream out;
    int pos=0;
    double fbest=0,fnew=0;
    int vec[150], sum[150], sbest[150], sold[150];

    init(vec,add,sum);
    fbest = eval(vec);
    copyArray(sbest, vec); //sbest = vec;

    int stopAllLoop=0;

while(stopAllLoop==0){
        //sold=sbest;
        if(stopAllLoop==1){
          break;
        }

        copyArray(sold, sbest);
        pos = modify(sold,add,sum);
        fnew = eval(sold);
  
        cout<<"\nFnew: "<<fnew<<" fbest: "<<fbest;
        if(fnew>fbest){
          // cout<<"gpos:"<<gpos;
            fbest = fnew;
            copyArray(sbest,sold); //sbest= sold;
             printToFile(fbest, sbest);
            cout<<"\nFITNESS = "<<fbest << endl;
        }
        else{

            //int randNum = rand()%(max-min + 1) + min;
            int foundFbest=0;

            for(int k=0;k<=150;k++){
              if(foundFbest==1){
                  printArray(sold);
                  copyArray(sbest,sold);
                  fbest = fnew;
                  printToFile(fbest, sbest);
                  cout<<"\nFITNESS = "<<fbest << endl;
                 break;
              }

              if(k==1000){
                    stopAllLoop=1; 
              }


                  for(int j=0;j<1;j++){
                     gpos = rand()%(149-120 + 1) + 120;
                     sold[gpos]=1;
                     fnew =eval(sold);
                     if(fnew>fbest){
                        foundFbest = 1;
                        break;
                     }
                      
                  }
                
                  if(foundFbest==0){
                      for(int j=0;j<1;j++){
                         gpos = rand()%(119-90 + 1) + 90;
                         sold[gpos]=1;
                         fnew =eval(sold);
                         if(fnew>fbest){
                            foundFbest = 1;
                            break;
                         }  
                      }
                  }

                  if(foundFbest==0){
                      for(int j=0;j<1;j++){
                          gpos = rand()%(89-60 + 1) + 60;
                         sold[gpos]=1;
                         fnew =eval(sold);
                         if(fnew>fbest){
                            foundFbest = 1;
                            break;
                         }  
                      }
                  }

                  if(foundFbest==0){
                      for(int j=0;j<1;j++){
                         gpos = rand()%(59-30 + 1) + 30;
                         sold[gpos]=1;
                         fnew =eval(sold);
                         if(fnew>fbest){
                            foundFbest = 1;
                            break;
                         }  
                      }
                  }

                  if(foundFbest==0){
                      for(int j=0;j<1;j++){
                         gpos = rand()%(29-0 + 1) +0;
                         sold[gpos]=1;
                         fnew =eval(sold);
                         if(fnew>fbest){
                            foundFbest = 1;
                            break;
                         }  
                      }
                  }
                
            }
            
        }
}
return 0;
}
