# HMM1
### AIM
Solution to HMM problem-1
### EXECUTION: 
Build and run the code on Visual Studio 2010. Use F5 key to run the code.

### INPUT: 
Initial_Model.txt, HMM_OBSERVATION_SEQUENCE_1.txt
### OUTPUT: 
The probability of the observation sequence, given the model.

### CONSTANTS:
1. M: The number of observation symbols per state (32)
2. N: The number of states (5)
3. MAX_T: Maximum time value (160)

### VARIABLES:
1. A[N+1][N+1]: Array to store the state transition probability distribution.
2. B[N+1][M+1]: Array to store the observation symbol probability distribution.
3. Pi[N+1]: Array to store the initial state distribution.
4. T: Variable to store number of observations
5. alpha[MAX_T+1][N+1]: Array to store the forward variable values.
6. beta[MAX_T+1][N+1]: Array to store the backward variable values.
7. O[MAX_T+1]: Array to store the observation sequence.
8. P_O_given_lambda: Long double variable to store the solution of problem 1.

### FUNCTIONS:
1. forwardProcedure():
	Function to inductively solve for the forward variable, where alpha is the probability of the partial observation sequence until time t and state Si at time t given model lambda. 

2. backwardProcedure():
	Function to inductively solve for the backward variable, where beta is the probability of the partial observation from t+1 till the end, given state Si at time t and model lambda. 

### PROCEDURE:
1. Read the input files and populate the A, B, Pi and O arrays.
2. Call the forwardProcedure and backwardProcedure functions.
