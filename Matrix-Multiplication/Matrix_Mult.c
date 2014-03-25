//Matrix Multiplication Serial Code
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>

int main()
{

int **a,**b,**c;
int a_r,a_c,b_r,b_c;
clock_t start,end; /* variables to store time difference between start of paralleization and end ofparallelization */
double dif; /*variable to calculate the time difference between the parallelization */
int i,j,k;

again:
printf("\nEnter number of Rows and Columns for Matrix one:");
scanf("%d%d",&a_r,&a_c);
printf("\nEnter number of Rows and Columns for matrix two:");
scanf("%d%d",&b_r,&b_c);
if(a_c!=b_r )
  {
   printf("\Matrices can't be multiplied, please enter another dimensions");
   goto again;
   }
// Memory allocation for Matrix 1
a=(int **) malloc(10*a_r);
for( i=0;i<a_c; i++)
  {
   a[i]=(int *) malloc(10*a_c);
  }
//Memory allocation for Matrix 2
b=(int **) malloc(10*b_r);
for( i=0;i<b_c; i++)
  {
   b[i]=(int *) malloc(10*b_c);
  }
// Memory allocation for Multiplication Matrix
c=(int **) malloc(10*a_r);
for( i=0;i< b_c; i++)
  {
   c[i]=(int *) malloc(10*b_c);
  }
 printf("By default Matrix Initialization\n");
 printf("Under Process CLOCK STARTED\n");
 start =clock();
//start the timer
//Initialization of Matrix 1
int count = 1;
for(i=0;i<a_r; i++)
 {
  for(j=0;j<a_c; j++)
   {
     a[i][j] = count;
     count++;
   }
 }

// Initialization of Matrix 2
count = 10;
for(i=0;i<b_r; i++)
  {
   for(j=0;j<b_c; j++)
    {
      b[i][j] = count;
      count++;
    }
  }

// Initialization of Product Matrix
for(i=0;i<a_r; i++)
  {
   for(j=0;j< b_c; j++)
   {
    c[i][j]=0;
   }
  }

// Multiplication code
for(i=0;i<a_r; i++)
{
for(j=0;j<a_c; j++)
{
for(k=0;k<b_c; k++)
{
c[i][j]=c[i][j]+a[i][k]*b[k][j];
}
}
}

printf ("Calculation Done Timer Stopped\n");
 end= clock();                               //Timer Stopped
 dif = ((double) (end - start)) / CLOCKS_PER_SEC; //Time difference calculation

 printf("Total time taken %.10f sec. time.\n", dif);
//Clearing Memory
for(i=0;i<a_r; i++)
 {
  free(a[i]);
 }
free(a);
for(i=0;i<a_c; i++)
 {
  free(b[i]);
 }
free(b);
for(i=0;i<b_c; i++)
 {
  free(c[i]);
 }
free(c);
}
