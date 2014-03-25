/*objective:
matrix multiplication in dynamic way
*/
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
int main()
{
int **a,**b,**c;    // Variable for saving memory allocation
int a_r,a_c,b_r,b_c, nthreads, tid, chunk =10;  //Variables for Matrix dimensions and for OpenMP functions
double dif;       //For time difference calculation
int i,j,k;
again:
printf("Enter number of Rows & Columns for Matrix 1: \n");
scanf("%d%d",&a_r,&a_c);
printf("Enter number of Rows & Columns for Matrix 2: \n");
scanf("%d%d",&b_r,&b_c);
if(a_c!=b_r )
 {
     printf("\ncan not multiply");
     goto again;
 }
// Memory allocation for Matrix 1
a=(int **) malloc(10*a_r);
for( i=0;i<a_c; i++)
 {
  a[i]=(int *) malloc(10*a_c);
 }
// Memory allocation for Matrix 2
b=(int **) malloc(10*b_r);
for( i=0;i<b_c; i++)
 {
  b[i]=(int *) malloc(10*b_c);
 }
// Memory allocation for Product Matrix
c=(int **) malloc(10*a_r);
for( i=0;i< b_c; i++)
 {
  c[i]=(int *) malloc(10*b_c);
 }
printf("Matrix default Initialization\n");
printf("Clock Started\n");
//Setting up Clock
double start = omp_get_wtime( );
                                                                        //Code Parallelization Initiated
    #pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
     {
       tid = omp_get_thread_num();
       if (tid == 0)
       {
         nthreads = omp_get_num_threads();
         printf("Starting matrix multiple example with %d threads\n",nthreads);
        }
                                                                      //Initialization of Matrix 1
       #pragma omp for schedule (static, chunk)
        for(i=0;i<a_r; i++)
        {
          for(j=0;j<a_c; j++)
           {
            a[i][j] = i+j;
            }
         }
                                                                    //Initialization of Matrix 2
      #pragma omp for schedule (static, chunk)
       for(i=0;i<b_r; i++)
       {
        for(j=0;j<b_c; j++)
         {
           b[i][j] = i*j;
          }
        }
                                                                    //Initialization of Product Matrix 3
      #pragma omp for schedule (static, chunk)
       for(i=0;i<a_r; i++)
        {
         for(j=0;j< b_c; j++)
          {
           c[i][j]=0;
           }
         }
                                                                   //Matrix Multiplication
      printf("Thread %d starting Matrix Multiply\n",tid);
      #pragma omp for schedule (static, chunk)
       for(i=0; i<a_r; i++)
        {
         printf("Thread %d performed row = %d \n",tid,i);
         for(j=0;j<a_c; j++)
          {
           for(k=0;k<b_c; k++)
            {
              c[i][j]=c[i][j]+a[i][k]*b[k][j];
             }
           }
         }
    }

    printf("Matrix Multiplication Done\n");
//Stop Timer
    double end = omp_get_wtime( );
    dif = end - start;
    printf("Parallelization took %f Seconds\n", dif);
// Releasing Memory
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
