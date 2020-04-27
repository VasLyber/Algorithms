#include <iostream>      
#include <fstream>      
#include <string>      
#include <bits/stdc++.h>       
using namespace std;        
         
void swap(long long int* a, long long int* b)        
{        
    int t = *a;        
    *a = *b;        
    *b = t;        
}        
        
int partition (long long int arr[], int low, int high)        
{        
    long long int pivot = arr[high];        
    int i = (low - 1);       
        
    for (int j = low; j <= high - 1; j++)        
    {         
        if (arr[j] < pivot)        
        {        
            i++;       
            swap(&arr[i], &arr[j]);        
        }        
    }        
    swap(&arr[i + 1], &arr[high]);        
    return (i + 1);        
}        
        
void quickSort(long long int arr[], int low, int high)        
{        
    if (low < high)        
    {        
              
        int pi = partition(arr, low, high);        
        
             
        quickSort(arr, low, pi - 1);        
        quickSort(arr, pi + 1, high);        
    }        
}        
      
      
int main(int argc, char **argv){      
          
long long int N,K,D,T,DSM,TM,CAR,Cf,Cs,Tf,Ts,i,Cmin,Pmin;      
      
cin >> N >> K >> D >> T;      
      
long long int p[N],c[N],d[K+1];      
      
for(i=0;i<N;i++) cin >> p[i] >> c[i];      
for(i=0;i<K;i++) cin >> d[i];      
      
cin >> Ts >> Cs >> Tf >> Cf;      
quickSort(d,0,K-1);      
      
d[K] = D - d[K-1];      
      
for(i=1;i<K-1;i++) d[i] = d[i+1] - d[i];      
      
DSM= (T-Tf*D)/(Ts-Tf);      
       
Cmin = 0;  
i = K;      
    
while(true){      
      
  
  
  
   if(DSM<d[i] && DSM!=0){      
        TM= DSM*Cs + (d[i]- DSM)*Cf;      
        DSM=0;      
   // if(TM>Cmin) Cmin=TM;      
        i--;      
     //   printf("%d\n",Cmin);   
    }      
    if(DSM==0){      
    TM = d[i]*Cf;      
    if(TM>Cmin) Cmin=TM;    
    break;      
    }      
          
    else {      
    DSM -= d[i];      
    i--;      
    }      
}      
      
Pmin = 1000000000;      
CAR=-1;      
   
for (i=0;i<N;i++){      
    if(p[i]<Pmin && c[i]>=Cmin && c[i]>=Cs*d[K]){      
        CAR=i;      
        Pmin=p[i];      
   
  
    }      
}      
      
      
if(CAR!=-1)      
printf("%d\n",p[CAR]);      
      
else      
printf("%d\n",CAR);      
      
return 0;      
      
}   
