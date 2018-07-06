//
//  faulttoleranceFINAl.c
//  faullttoleranceFINAL
//
//  Created by Pavan Kumar  Paluri  on 9/7/17.
//  Copyright © 2017 Pavan Kumar  Paluri . All rights reserved.
//

//
//  main.cpp
//  Magic 7
//
//  Created by Carlos Rincon on 5/8/17.
//  Copyright © 2017 Carlos Rincon. All rights reserved.
//


#include <iostream>
#include <cmath>
#include <iomanip>


#define MAXPARTITIONNUMBER 15
#define MAXLEVELNUMBER 16
#define TIMESLICEARRAYSIZE 65536
#define MAXNUMBEROFTIMESLICESPERLEVEL 4096
#define QUANTUM 100

using namespace std;

//Helper functions
double aproximateValue(double);
double findmaxnumber(double[],int);
int findfirstAvailableTimeSlice();
void initializeSchedulingDiagramArrays();
void printSchedulingSolution(int,int);
double calculateW(int partitionMethod, int);
int calculateHyperPeriod(double[], int, int);
float RandomBetween(float, float);
unsigned int rand_interval(unsigned int , unsigned int);


//RTS Partition functions
double AAF(double, int);
double MAGIC7(double, int);
double L(double);
void PARTITION_SINGLE(double[], int, int, int);
void MAGIC7_SINGLE(double[], int);
void AAF_SINGLE(double[], int);


int timeslices[MAXPARTITIONNUMBER][MAXLEVELNUMBER][MAXNUMBEROFTIMESLICESPERLEVEL];
int schedulingDiagram[TIMESLICEARRAYSIZE];

int main()
{
    double alpha[MAXPARTITIONNUMBER],aaf[MAXPARTITIONNUMBER];  //a:availability k:supply regularity z:how many partition b:partition
    int availabilityFactor[MAXPARTITIONNUMBER],partitions, method, hyperperiod;       //z:how many partition b:partition
    
    initializeSchedulingDiagramArrays();
    // Data input
    
    //cout << "AAF and Magic7 implementation. RTS-LAB. Cs Department - University of Houston." << endl << endl;
    cout << "Select the partitioning algorithm (2 = AAF, 7 = Magic7): ";
    cin >> method;
    if ((method != 2) == (method != 7))
    {
        cout << "Incorrect method. Valid options: 2 (AAF) and 7 (Magic7)" << endl;
        return 0;
    }
    cout << "Number of partitions (Max = 15): ";
    cin  >> partitions;
    
    for (int i=0;i<partitions;i++)
    {
        alpha[i]= RandomBetween(0,0.025);
        availabilityFactor[i]=rand_interval(0,2);
    }
    
    //Calculating Magic7 for each partition
    
    for(int i=0; i<partitions;i++)
    {
        if (method == 2)
            aaf[i]=AAF(alpha[i],availabilityFactor[i]);
        else
            aaf[i]=MAGIC7(alpha[i],availabilityFactor[i]);
        
    }
    
    // Printing the information of each partition
    
    for (int i=0;i<partitions;i++)
    {
        cout << endl << "Partition " << i << ", alpha= " << alpha[i] << ", k= " << availabilityFactor[i] << ", AAF value= " << aaf[i]  << endl;
    }
    
    printf("\n");
    
    
    // Schedulability test
    
    double aafsum=0;
    for (int i=0; i < partitions; i++)
    {
        aafsum+=aaf[i];
    }
    if(aafsum>1)
    {
        cout << "The partitions were unschedulable" << endl;
        return 0;
    }
    
    cout << "Utilization = " << aafsum << endl;
    
    // Calculate Hyperperiod
    
    hyperperiod=calculateHyperPeriod(aaf, partitions, method);
    
    cout << "Hyper-Period = " << hyperperiod << endl << endl;
    
    // Running Partition Single (AAF or Magic7)
    
    PARTITION_SINGLE(aaf,partitions,method, hyperperiod);
    
    // Printing Scheduling Results
    
    printSchedulingSolution(partitions,hyperperiod);
}

double aproximateValue(double value)    // Function to overcome the rounding problems
{
    double result=floor(value);
    if(value - result > 0.99999)
        return(result+1);
    if(value - result >0.49999 && value - result < 0.5)
        return(result+0.5);
    if(value - result > 0 && value - result < 0.00001)
        return(result);
    return(value);
    
}

double findmaxnumber(double array[], int size)  //Function to find the maximun value of an array
{
    double result=0;
    for (int i=0;i<size;i++)
    {
        if (array[i] > 0 && array[i]>result)
        {
            result=array[i];
        }
    }
    return result;
    
}


int findfirstAvailableTimeSlice()           //Function to find the first available timeslice
{
    for (int i=0;i < TIMESLICEARRAYSIZE ; i++)
        if(schedulingDiagram[i]==-1)
            return(i);
    return -1;
}

void initializeSchedulingDiagramArrays()    //Function to initialize the arrays used to store the results
{
    for(int i=0;i< TIMESLICEARRAYSIZE;i++)
        schedulingDiagram[i]=-1;
    for(int i=0;i<MAXPARTITIONNUMBER;i++)
        for(int j=0;j<MAXLEVELNUMBER;j++)
            for(int k=0;k<MAXNUMBEROFTIMESLICESPERLEVEL;k++)
                timeslices[i][j][k]=-1;
}

double calculateW(int partitionMethod, int n)   //Function to calculate w based on the selected method (2 = AAF, 7= Magic7)
{
    if (partitionMethod==2) // AAF
        return(1.0/pow(2,n));
    if (partitionMethod==7) // Magic7
    {
        if(n<=3)
            return(1.0-(1.0/(112/pow(2,n)))); //  from 111/112 to 13/14
        if(n>3 && n<=9)                       //  from 6/7 to 1/7
            return((10.0-n)/7);
        else                                  //  from 1/14 to ....
            return(1.0/(7*pow(2,n-10+1)));
    }
    return 0;
    
}

int calculateHyperPeriod(double aaf[], int partitions, int method)  //Function to calculate the hyperperiod based on the AAF array and the method (2=AAF, 7=Magic7)
{
    int count;
    int hyperperiod=method;
    
    do
    {
        count=0;
        for(int i=0;i<partitions;i++)
        {
            if (fmod(aproximateValue(aaf[i]*hyperperiod),1) == 0)
                count++;
            else
                break;
        }
        if (count<partitions)
            hyperperiod=hyperperiod*2;
        
    }
    while(count < partitions);
    return(hyperperiod);
    
}


double AAF(double alpha, int availabilityFactor)    //AAF function based on Yu Li and Dr. Cheng 2012 RTSS paper
{
    float result;
    int n;
    
    if(alpha==0)
        return 0;
    if (alpha>0 && availabilityFactor==1)
    {
        n=floor((log(alpha))/(log(.5)));
        return(1/(pow(2,n)));
    }
    else
    {
        n=ceil(((log(alpha))/(log(.5))));
        result=(1/(pow(2,n)));
        return (AAF((alpha-result),(availabilityFactor-1))+result);
    }
}


double MAGIC7(double alpha, int availabilityFactor) //Magic7 function based on Yu Li and Dr. Cheng 2012 RTSS paper
{
    double n;
    if(alpha==0)
        return 0;
    if (availabilityFactor==1)
    {
        if (alpha>0 && alpha < 1.0/7)
        {
            n=floor(aproximateValue(log(7.0*alpha)/log(0.5)));
            return(1/(7*pow(2,n)));
        }
        if (alpha>=1.0/7 && alpha<=6.0/7)
        {
            return(ceil(aproximateValue(7.0*alpha)))/7;
        }
        if (alpha>6.0/7 && alpha < 1)
        {
            n=ceil(aproximateValue(log(7.0*(1-alpha))/log(.5)));
            return(1-(1/(7*pow(2,n))));
        }
    }
    else
        return (L(alpha)+MAGIC7(alpha-L(alpha),availabilityFactor-1));
    return 0;
}


double L(double alpha)  //L function based on Yu Li and Dr. Cheng 2012 RTSS paper (used by Magic7)
{
    
    double n;
    
    if (alpha>0 && alpha<1.0/7)
    {
        n=ceil(aproximateValue(1.0*log(7*alpha)/log(0.5)));
        return(1.0/(7*pow(2,n)));
    }
    else if (alpha>=1.0/7 && alpha <= 6.0/7)
    {
        return(floor(aproximateValue(7.0*alpha))/7);
    }
    else if (alpha>6.0/7 && alpha < 1)
    {
        n=floor(aproximateValue(log(7.0*(1-alpha))/log(0.5)));
        return(1-(1.0/(7*pow(2,n))));
    }
    else if(alpha==1)
        return 1;
    return 0;
}


void PARTITION_SINGLE(double aaf[], int partitions, int method, int hyperperiod) // Partition function based on Yu Li and Dr. Cheng 2012 RTSS paper based on the method (2=AAF_Single, 7= Magic7_Single)
{
    int level=0,scheduledPartitions=partitions;
    double w=1,maxaaf;
    int distance[MAXPARTITIONNUMBER],distindex[MAXPARTITIONNUMBER],firstLevel,firstAvailableTimeSlice=0,timeslicesize=0;
    
    // Find the first used level
    
    maxaaf=findmaxnumber(aaf,partitions);
    
    while(maxaaf<w)
    {
        level++;
        w=calculateW(method, level);
    }
    firstLevel=level;
    
    // Calculate the initial distance per partition
    
    for(int i=0;i<partitions;i++)
    {
        distance[i]=floor(1.0/w);
        if(1.0/w-distance[i] > 0.5)
            distance[i]+=1;
        distindex[i]=1;
    }
    
    while(scheduledPartitions>0)
    {
        
        w=calculateW(method, level);
        for(int i=0;i<partitions;i++)
        {
            
            timeslicesize=w*hyperperiod;
            timeslices[i][level-firstLevel][0]=timeslicesize;   // For printing purpose
            if((aaf[i]>=w || aproximateValue(abs(aaf[i]-w))==0) && aaf[i] > 0)
            {
                
                for(int j=1;j<=timeslicesize;j++)
                {
                    timeslices[i][level-firstLevel][j]=firstAvailableTimeSlice+(j-1)*distance[i];
                    schedulingDiagram[firstAvailableTimeSlice+(j-1)*distance[i]]=i;
                }
                firstAvailableTimeSlice=findfirstAvailableTimeSlice();
                aaf[i]-=w;
                if(aaf[i]<=0.0001)
                    scheduledPartitions--;
                distindex[i]++;
                distance[i]*=distindex[i];
            }
        }
        if(scheduledPartitions == 0)
        {
            for(int i=0;i<partitions;i++)
                timeslices[i][level-firstLevel][timeslicesize+1]=-2;    // For printing purpose
        }
        level++;
        
    }
    
}

void printSchedulingSolution(int partitionN, int hyperperiod)
{
    
    int numberofTimeSlices=0;
    
    cout << "Partitions Diagram" << endl << endl;
    
    for(int partition=0; partition<partitionN; partition++)
    {
        for(int level=0; level<MAXLEVELNUMBER; level++)
        {
            numberofTimeSlices=timeslices[partition][level][0];
            for(int j=1; j<=numberofTimeSlices; j++)
            {
                if (timeslices[partition][level][j] == -1)
                    cout << setw(5) << "-";
                else
                    cout << setw(5) << timeslices[partition][level][j];
                
            }
            if (timeslices[partition][level][numberofTimeSlices+1] == -2)
                break;
            cout << "  | ";
        }
        cout << endl << endl;
    }
    cout << "Scheduling Diagram (Quantum = " << QUANTUM << " ms.)" << endl << endl;
    cout << setw(25) << "Time (ms)" << setw(25) << "Partition" << endl;
    for(int i=0;i<hyperperiod;i++)
    {
        cout << setw(25) << i*QUANTUM << setw(25);
        if (schedulingDiagram[i] == -1)
            cout << setw(25) << "-";
        else
            cout << setw(25) << schedulingDiagram[i];
        cout << endl;
    }
    cout << endl;
    
}

float RandomBetween(float smallNumber, float bigNumber)
{
    float diff = bigNumber - smallNumber;
    return (((float) rand() / RAND_MAX) * diff) + smallNumber;
}

unsigned int rand_interval(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;
    
    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);
    
    return min + (r / buckets);
}








