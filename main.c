//updated code ; updated on Sep 5 @ 8:13 pm
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <setjmp.h>
#include <time.h> //for generating random numbers
#define MAX 10000
typedef long long int ll;

//function declarations
double AFF7(double ,int ,int);
double L(double ); //to be used in AFF7 for in depth calculations
void cpc(double *); //function for checkpoint calculation
//cpc returns alpha_c and n for number of checkpoints
double rpc(double ); //returns alpha_r
int timeslices(); //this function returns number of time slices for the number of partitions
int random_number(int,int);
int period(); //returns period
float * availability_facotr(int* ,int*,int); //takes timeslices and period as inputs and returns availability factors
int hyperperiod(int*,int);
int gcd(int,int);
int hcf_function(int ,int );
int lcm_function(int,int);
int hyperperiod(int*,int);
long int best_lcm(int,int);
double MAGIC7(float ,int ); // AAF function that takes availability factor and supply
double L(double );
double aproximateValue(double );
int supply_regularity(); //returns k value for each partition
//Alpha_c is obtained from n/hp for which the checkpoint placement algorithm has to be coded
//global declaratons
void checkpt_calc(int,int,double *,int *); // returns multiple values ; to return Alpha_c and number of checkpoints to be placed
int checkpoint_placement(int ,int );
static float alpha[MAX];
double factorial(int );
ll hp; //hyper period would be common for all the periods and partitions
ll findlcm(int [],int);


//---------------------------------------------------------------------------
int main()
{
    int *s,n,*p,*k,n1,z;
    static long int lcm;
    //int s[50],p[50],n;
    // float a[50];
    double *AAF,AAF1,alpha_c;
    float *a;
    
    printf("Enter the number of partitions:(max:7)");
    scanf("%d",&n);
    if(n>7)
    {
        return(EXIT_FAILURE);
    }
    else if (n==0 || n<0)
        return(EXIT_FAILURE);
    p=(int *)malloc(n*sizeof(int)); //p has been allocated a size of n, an array of size n
    s=(int *)malloc(n*sizeof(int)); //s has been allocated a size of n, an array of size n
    //ll ans = p[0];
    a=(float *)malloc(n*sizeof(float)); //a has been allocated a size of n, an array of sizen
    //int p[MAX];
    k=(int *)malloc(n*sizeof(int)); //supply regularity for n partitions
    AAF = (double *) malloc(n*sizeof(double)); // AAF for AAF(APLHA_I,K_I);
    //AAF'= (double *)malloc(n*sizeof(double)); // Summation of AAF's
    for(int i=0;i<n;i++) // this loop is the loop for number of iterations
    {
        s[i]=timeslices(); //returns the randomly generated timeslices for each partition
        p[i]=period(); //ok
        k[i]=supply_regularity(); //not ok
    }
    lcm = p[0];
    for(int i=0;i<n;i++)
    {
        printf("Period values:%d\n",p[i]);
        
        
        //printf("LCM:%ld",lcm);
        
        if(s[i]<p[i])
        {
            printf("\nPartition %d has %d timeslices\n",i+1,s[i]);
            printf("\nPartition %d has %d period\n",i+1,p[i]);
            printf("\nPartition %d has k= %d \n",i+1,k[i]);
            a=availability_facotr(s,p,n);
            printf("\nAvailability factor for partition %d is:%f\n",i+1,a[i]);
            AAF[i] = MAGIC7(a[i],k[i]); //calculates AAF for every respective alpha and K
            
            AAF1+=AAF[i]; //AAF' has cumulative sum of i AAF'
            if(AAF1>1)
            {
                s[i]='\0'; //freeing the i'th elements
                p[i]='\0';
                k[i]='\0';
                a[i]='\0';
                AAF[i]='\0';
                printf("The partition %d has been removed to accomodate for schedulability",i+1);
            }
            printf("\nAdjust Availability factor for partition %d is:%f\n",i+1,AAF[i]);
            
            if(p[i]=='\0')
            {
                // p[i]=p[i-1];
                lcm = best_lcm(lcm,p[i-1]);
                printf("\nHyperperiod:%ld\n",lcm);
                checkpt_calc(lcm, n,&alpha_c,&n1);
                z=checkpoint_placement(n, n1); //n1 for number of checkpoints and n is the number of partitions
                printf("\nnumber of total checkpoints to be placed %d\n",n1);
                printf("Availability factor for checkpoint partition is %f",alpha_c);
                printf("\nNumber of regular partitions per checkpoint:%f\n",z);
                
                exit(0);
                
            }
            else
            {
                lcm = best_lcm(lcm,p[i]);
                
            }
            
        }
        else
            exit(0);
    }
    printf("\nHyperperiod:%ld\n",lcm);
    checkpt_calc(lcm, n,&alpha_c,&n1);
    printf("\nAvailability factor for checkpoint partition is %f\n",alpha_c);
    printf("\nnumber of total checkpoints to be placed %d\n",n1);
    z=checkpoint_placement(n, n1); //n1 for number of checkpoints and n is the number of partitions
    printf("\nNumber of regular partitions per checkpoint:%f\n",z);
    
    
    
    
    return 0;
}

int timeslices()
{
    int s;
    s=random_number(1,10);
    return s;
}

int period() //returns the period per partition
{
    int p;
    p=random_number(15,25);
    return p;
}


//seeding random number with specific ranges for all the timeslices to be uniform
int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;
    
    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }
    
    // srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

float *availability_facotr(int* s,int* p,int n)
{
    int i;
    // p=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++) {
        alpha[i] = ((float) s[i] / p[i]);
        //printf("\nAvailability factor for partition %d is:%f\n", i, alpha[i]);
    }
    return alpha; //returns an array of alpha values to be passed to the main function
    //return (alpha[i]);
    // i++;
}


// LCM calculation for hyperperiod

long int best_lcm(int n1,int n2)
{
    
    long int minMultiple;
    
    // minMultiple =n1;
    minMultiple = (n1>n2) ? n1 : n2;
    
    // Always true
    while(1)
    {
        if( minMultiple%n1==0 && minMultiple%n2==0 )
        {
            //printf("The LCM of %d and %d is %ld.", n1, n2,minMultiple);
            break;
        }
        ++minMultiple;
    }
    return minMultiple;
}

int supply_regularity()
{
    int k;
    k= random_number(1, 2);
    return k;
}

//Functions for MAGIC 7 and L
double MAGIC7(float alpha, int availabilityFactor) //Magic7 function based on Yu Li and Dr. Cheng 2012 RTSS paper
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


double L(double alpha)  //L function based on Yu Li and Dr. Cheng 2012 RTSS paper (used by
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


void checkpt_calc(int hyperperiod,int partitions,double  *alpha, int *k) //takes hyperperiod and number of partitions as input and returns alpha_c and number of checkpoints to be placed for an even distribution
{
    //int n=0;
    double  i;
    float a=0;
    //  int partitions;
    //float hp; //number of summed probabilities
    //double alpha,k; //availability factor
    float Pr_sum ;
    float g;//,result;
    // double l=0;//gamma is avg number of faults and i is the exact number of faults within a hyperperiod
    if(partitions>7)
    {
        printf("Maximum limit Exceeded,Exiting");
        exit(0);
        
    }
    printf("\nNumber of average faults within a hyperperiod is:"); //Assumption: fault occurs at a single time slice
    scanf("%f",&g);
    i=1;
    do {
        //for (i = 1; ; i++) {
        Pr_sum += (pow(g, i) / (factorial(i) * exp(g)));//*pow(g,i)/factorial;
        printf("\ncumulative prob:%f\n", Pr_sum);
        
        
        if (Pr_sum <= 0.9) {
            (*k)++;
            // if (alpha < 1) {
            //printf("\nNumber of fault occurances:%f\n", k);
            //printf("\nAvailability factor thus obtained is:%f\n", alpha);
            // }
            //return &alpha; // returns checkpoint availability factor
            
        }
        else {
            break;
        }
        
        
        i++;
        // }
    }
    while(Pr_sum<0.999);
    printf("Hyperperiod, printing it in checkpoint placement function %d\n",hyperperiod);
    (*alpha) =  *k /(double) hyperperiod; // returns checkpoint availability factor
   // printf("\nprinting alpha c in checkpoint placement fn:%f\n",alpha);
    //return &k; // returns number of fault occurances
    
    // printf("number of checkpoints to be placed:%f",k);
    // result = checkpoint_placement(k,partitions);
    
    
    
}

double factorial(int k)
{
    if (k == 1)
        return 1;
    else
        return k* factorial(k - 1);
}

int checkpoint_placement(int n,int partition) {
    int ch;
    double result = partition / n;
    printf("\n1:Utilisation Effective Checkpoint Placement\n 2:Fault Tolerant Effective Checkpoint Placement\n");
    scanf("%d", &ch);
    switch (ch) {
        case 1:
            result = ceil(result);
            printf("\nCheckpoints are placed for every %f partitions of total %d\n", result, partition);
            return result;
            break;
        case 2:
            result = floor(result);
            printf("\n Checkpoint are placed for every %f partitions of toal %d\n", result, partition);
            return result;
            break;
            
        default:
            printf("Error!!, Invalid Option");
            return (EXIT_SUCCESS);
    }
}



