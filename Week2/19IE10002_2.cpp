/* Name: Aditya Basu
Roll No: 19IE10002
Info: 19IE10002_2.cpp, Algorithms Lab, Assignment 2
Date: Jan 19, 2021
*/


#include<iostream>

using namespace std;

void vote_dist(int *D, int p, int v, int *C, int C_size, int winning_num, int *A, int fixed_p);
void print(int *D, int *C, int C_size, int p, int winning_num);

int main()
{
    int v,p,winning_num; 

    cout<<"#Voters: ";
    cin>>v;
    winning_num = (v/2) + 1; // minimum no. of votes to win
 
    cout<<"#Parties: ";
    cin>>p;

    int *C = new int[p]; // C is the coalition array // maximum possible size of coalition array is p
    cout<<endl<<"Coalition: "<<endl;
    int input,i = 0;
    cin>>input;

    while(input > 0)
    {
        C[i] = input;
        i++;
        cin>>input;
    }

    int C_size = i; // size of the coalition array

    int *D = new int[p]; // array to store the distribution
    int *A = D;          // helper pointer to print during recursion
    int fixed_p = p;    // helper variable to print during recursion
    
    cout<<endl<<endl;
    vote_dist(D,p,v,C,C_size,winning_num,A,fixed_p);
    
    return 0;
}

/*
    Function to print the distribution if coalition wins majority 
    D -> Distribution array
    C -> coalition array
    C_size -> size of coalition array
    p -> size of distribution array
    winning_num -> threshold to be crossed to get simple majority

*/

void print(int *D, int *C, int C_size, int p, int winning_num)
{
    int sum = 0;

    int i;
    for(i = 0; i<C_size; i++)
    {
        sum += D[C[i]- 1];
    }

    if(sum>= winning_num)
    {
        for(i=0; i<p; i++)
        {
            cout<<i+1<<": "<<D[i]<<"   ";
        }
        cout<<"Total votes for the coalition: "<<sum;
        cout<<endl;
        return;
    }
}

/*
    Function to print the generate distribtuion and call print
    D -> Distribution array
    C -> coalition array
    v -> total no. of voters
    C_size -> size of coalition array
    p -> size of distribution array
    winning_num -> threshold to be crossed to get simple majority
    A,fixed_p -> helper pointers and variables that will be passed to print() so that
    full length of array can be printed (during recursion)
    Note: A points to D, fixed_p = p
*/


void vote_dist(int *D, int p, int v, int *C, int C_size, int winning_num, int *A, int fixed_p)
{
    if(p == 1) // base case: only one party
    {
        D[0] = v;
        print(A,C,C_size,fixed_p, winning_num); // print when the length is exhausted i.e root of the recursion tree
    }

    else
    {
        int i;
        for(i=0; i<=v; i++)
        {
            D[0] = i;   // assign first element a value(of all possible values) and then recurse
            vote_dist(D+1,p-1,v-i,C,C_size,winning_num, A, fixed_p); 
        }
    }
}