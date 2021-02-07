/* Name: 19IE10002_1.cpp
   Creator: Aditya Basu(aditya.basu1@yahoo.com)
   Roll: 19IE10002
   Date: 11 Jan 2021
   Details: Assignment 1, Algorithms Lab Spring 2021
   Description: In this file 4 ways to compute I(n) has been implemented
*/

#include<iostream>
#include<cmath>
#include<ctime>

using namespace std;

double compute_iterative(int n);
double compute_recursive(int n);
double power(double x, int n);
double compute_formula(int n);
void multiply_two_matrices_of_size2(double **A, double **B, double **C);
double** allocate_2D_array();
double compute_matrix(int n);
double get_time(clock_t tic, clock_t toc);

int main()
{
    int n; // <40
    cout<<"Write n: ";
    cin>>n;

    double m1,m2,m3,m4; // outputs using the four methods
    clock_t tic,toc;

    tic = clock();
    m1 = compute_iterative(n);
    toc = clock();

    printf("I_%d (computed using iterative method) = %lf\n",n,m1);
    printf("Time taken in iterative method = %lf seconds\n\n",get_time(tic,toc));

    tic = clock();
    m2 = compute_recursive(n);
    toc = clock();
    printf("I_%d (computed using recursive method) = %lf\n",n,m2);
    printf("Time taken in recursive method = %lf seconds\n\n",get_time(tic,toc));

    tic = clock();
    m3 = compute_formula(n);
    toc = clock();
    printf("I_%d (computed using formula) = %lf\n",n,m3);
    printf("Time taken in formula = %lf seconds\n\n",get_time(tic,toc));
 
    tic = clock();
    m4 = compute_matrix(n);
    toc = clock();
    printf("I_%d (computed using matrix multiplication) = %lf\n",n,m4);
    printf("Time taken in matrix = %lf seconds\n\n",get_time(tic,toc));   
    return 0;
}

/* Name: compute_iterative()
   Input: n - a non-negative integer
   Output: value of I(n)[double] using iteration
   Time Complexity: O(n)
*/

double compute_iterative(int n)
{
    double prev = 0, current = 1, next = 2;
    int i;

    if(n==0) return 0;
    else if(n==1) return 1;
    else
    {
        for(i=2; i<n; i++)
        {
            prev = current;
            current = next;
            next = 2*current + prev;
        }
        return next;
    }
}

/* Name: compute_recursive()
   Input: n - a non-negative integer
   Output: value of I(n)[double] using the method of recursion
   Time Complexity: exponential
*/

double compute_recursive(int n)
{
    //base cases
    if(n==0) return 0; 
    else if(n==1) return 1;

    //recursion
    else
    {
        return ( 2*compute_recursive(n-1) + compute_recursive(n-2) );
    } 
}

double power(double x, int n)
{
    if(n==0) return 1;
    if( (n%2) == 0)
    {
        double p = power(x,n/2);
        return p*p;
    }

    else
    {
        double p = power(x,n/2);
        return x*p*p;
    }
}

/* Name: compute_formula()
   Input: n - a non-negative integer
   Output: value of I(n)[double] using the formula given
   Time Complexity: O(log n)
   Additional info: (-1)^n has been taken common in the second term
*/

double compute_formula(int n)
{
    double rt2 = sqrt(2);

    double first = power(1 + rt2, n);
    double second = power(rt2 -1, n);
    //(-1)^n has been taken common in the second term

    if(n%2) // if n odd
    {
        double ans = (first + second)/(2*rt2);
        return ans;
    }

    else // if n even
    {
        double ans = (first - second)/(2*rt2);
        return ans;
    }
}

/* Name: allocate_2D_array()
   Output: allocates a 2D array(2X2)
*/

double** allocate_2D_array() // returns a 2D array of size 2(size = 2 is our requirement)
{
    double **A = new double *[2];
    int i = 0;
    for(i = 0; i<2; i++)
    {
        A[i] = new double [2];
    }
    return A;
}

/* Name: multiply_two_matrices_of_size2()
   Input: Two 2D matrices of size 2 and a third matrix where the result
   would be stored
   Time Complexity: constant time since size = 2(a constant)
*/

void multiply_two_matrices_of_size2(double **A, double **B, double **C)
{
    int i=0, j=0, k=0;

    // initializing
    for(i=0; i<2; i++)
    {
        for(j=0; j<2; j++) 
        C[i][j] = 0;
    }

    for(i=0; i<2; i++)
    {
        for(j=0; j<2; j++)
        {
            for(k=0; k<2; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* Name: compute_matrix_p1()
   Input: n - a non-negative integer
   Output: returns the matrix containing {{I(n+1), I(n)}, {I(n),I(n-1)}}
   Time Complexity: O(log n)
   Additional info: This function will be called by compute_matrix()
*/

double** compute_matrix_p1(int n)
{
    double **A = allocate_2D_array();
    A[0][0] = 2; A[0][1] = 1; A[1][0] = 1; A[1][1] = 0;
    // have to compute A^n

    if(n==0)
    {
        double **B = allocate_2D_array();

        // return identity matrix since say matrix M, then M X I = M
        B[0][0] = 1; B[0][1] = 0; B[1][0] = 0; B[1][1] = 1;
        return B;
    }

    if( (n%2) == 0) // n even
    {
        double **temp = allocate_2D_array();
        double **mat = allocate_2D_array();
        temp = compute_matrix_p1(n/2);
        multiply_two_matrices_of_size2(temp,temp,mat);
        return mat;
    }

    else
    {
        double **temp = allocate_2D_array();
        double **mat1 = allocate_2D_array();
        double **mat = allocate_2D_array();
        temp = compute_matrix_p1(n/2);
        multiply_two_matrices_of_size2(temp,temp,mat1);
        multiply_two_matrices_of_size2(A,mat1,mat);
        return mat;
    }
}


/* Name: compute_matrix()
   Input: n - a non-negative integer
   Output: value of I(n)[double] using the method of matrix multiplication
   Time Complexity: O(log n)
*/

double compute_matrix(int n)
{
    double **A = allocate_2D_array();
    A = compute_matrix_p1(n);   // calling the previous function that returns a matrix
    return A[0][1];
}

/* Name: get_time()
   Input: two structures tic, toc of type clock_t used for 
   Output: time spent (in seconds)
   Description: Simple subtraction and division by 
   CLOCKS_PER_SEC to find out the length of the time interval
*/

double get_time(clock_t tic, clock_t toc)
{
    double time_spent = (double)(toc - tic)/CLOCKS_PER_SEC;
    return time_spent;
}

