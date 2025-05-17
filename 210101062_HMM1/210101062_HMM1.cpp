// 210101062_HMM1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

#define M 32	//Number of observation symbols per state
#define N 5		//Number of states
const int MAX_T = 160;	//Maximum number of observations

//Model parameters A, B and Pi
long double A[N+1][N+1] = {0};
long double B[N+1][M+1] = {0};
long double Pi[N+1] = {0};

int T=1;			//Time sequence
int O[MAX_T+1];		//Observation sequence
long double alpha[MAX_T+1][N+1];	//P(o1, o2,..., ot, qt=Si | lambda)
long double beta[MAX_T+1][N+1];		//P(ot+1, ...., oT | qt=Si, lambda)
long double P_O_given_lambda = 0;

//Function to calculate alpha variable to find the solution of problem number 1
void forwardProcedure(){
	long double sum;
	int obs = O[1];
	for(int i=1; i<=N; i++){			//initialization
		alpha[1][i] = Pi[i]*B[i][obs];
	}
	
	for(int t=1; t<T; t++){				//induction
		for(int j=1; j<=N; j++){
			sum = 0;
			for(int i=1; i<=N; i++){
				sum += (alpha[t][i] * A[i][j]);
			}
			alpha[t + 1][j] = (sum * B[j][O[t + 1]]);
			cout<<alpha[t+1][j]<<"    ";
			//printf("%.28lf ", alpha[t+1][j]);
		}
		cout<<'\n';
	}

	for(int i=1; i<=N; i++){			//termination
		P_O_given_lambda += alpha[T][i];
	}
	cout<<"\n-----------------------------------------------\n";
	cout<<"P(O|model): "<<P_O_given_lambda<<"\n\n";
}

//Function to calculate beta variable.
void backwardProcedure(){
	long double sum;
	for(int i=1; i<=N; i++){		//initialization
		beta[T][i] = 1.0;
	}
	for(int t=T-1; t>=1; t--){		//induction
		int obs = O[t+1];
		for(int i=1; i<=N; i++){
			sum = 0;
			for(int j=1; j<=N; j++){
				sum += B[j][obs]*A[i][j]*beta[t+1][j];
			}
			beta[t][i]=sum;
			cout<<beta[t][i]<<"    ";
		}
		cout<<"\n";
	}
}

int main(){
	FILE *f1 = NULL;    // Read the data from the input file
	double x;
    int err = fopen_s(&f1, "Files/Initial_Model.txt", "r");
    if(err != NULL)     //error handling for file opening
    {
        printf("\nCannot open the file\n");
        system("pause");
        exit(1);
    }

	int count = 0; 
	int i=1, j=1;
	while( !feof(f1) )
	{
		if( fscanf_s( f1, "%lf", &x) == 1)
		{
			if(count<25){
				A[i][j] = x;
				j++;
				if(j==N+1){
					i++,j=1;
					if(i==N+1) i=1,j=1;
				}
				count++;
			}
			else if(count<185){
				B[i][j] = x;
				j++;
				if(j==M+1){
					i++,j=1;
					if(i==N+1) i=1,j=1;
				}
				count++;
			}
			else{
				Pi[i]=x;
				i++;
			}
		}
		else{
			char lines[500];
			fgets(lines, 500, f1);
		}
	}
	fclose(f1);

	FILE* f2= fopen("Files/HMM_OBSERVATION_SEQUENCE_1.txt","r");
    while( !feof(f2) )
	{
		if( fscanf_s( f2, "%lf", &x) == 1){
			O[T++]=x;
		}
	}
	T--;
	fclose(f2);

	forwardProcedure();
	backwardProcedure();
	return 0;
}

