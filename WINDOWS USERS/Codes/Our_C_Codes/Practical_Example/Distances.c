#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
  Please, uncomment the section containing your selected value of Beta
  and comment the sections containing the two other values of Beta.
  
  The sections where (Beta = 2) and (Beta = 3) are commented by default
*/

double EuclideanDistance(double X[], double Y[], int N){
	double x,y,D;
	int i;
	
	D = 0.0;
	for(i=0;(i < N);i++){
		x = X[i];
		y = Y[i];
		D += (x-y)*(x-y);
	}
	D = sqrt(D);
	return D;
}

double ManhattanDistance(double X[], double Y[], int N){
	double x,y,D;
	int i;
	
	D = 0.0;
	for(i=0;(i < N);i++){
		x = X[i];
		y = Y[i];
		D += fabs(x-y);
	}
	return D;
}

int main(int NbArg, char ** MesArg) {
		
	
	//Beta = 1
	
	double XP3[] = {0.31,0.69};
	double XP7[] = {0,0.83,0.17};
	double XP8[] = {0.41,0.28,0.31,0,0,0};
	double XP3P7[] = {0.31,0.69,0,0.83,0.17};
	double XP3P8[] = {0.31,0.69,0.41,0.28,0.31,0,0,0};
	double XP7P8[] = {0,0.83,0.17,0.41,0.28,0.31,0,0,0};
	double XP3P7P8[] = {0.31,0.69,0,0.83,0.17,0.41,0.28,0.31,0,0,0};

	double YP3[] = {0.62,0.38};
	double YP7[] = {0.36,0.25,0.39};
	double YP8[] = {1,0,0,0,0,0};
	double YP3P7[] = {0.62,0.38,0.36,0.25,0.39};
	double YP3P8[] = {0.62,0.38,1,0,0,0,0,0};
	double YP7P8[] = {0.36,0.25,0.39,1,0,0,0,0,0};
	double YP3P7P8[] = {0.62,0.38,0.36,0.25,0.39,1,0,0,0,0,0};
	
	
	/*
	//Beta = 2
	
	double XP3[] = {0.31,0.69};
	double XP7[] = {0,1,0};
	double XP8[] = {0,0.43,0.57,0,0,0};
	double XP3P7[] = {0.31,0.69,0,1,0};
	double XP3P8[] = {0.31,0.69,0,0.43,0.57,0,0,0};
	double XP7P8[] = {0,1,0,0,0.43,0.57,0,0,0};
	double XP3P7P8[] = {0.31,0.69,0,1,0,0,0.43,0.57,0,0,0};
	
	double YP3[] = {0.80,0.20};
	double YP7[] = {0.42,0.22,0.36};
	double YP8[] = {1,0,0,0,0,0};
	double YP3P7[] = {0.80,0.20,0.42,0.22,0.36};
	double YP3P8[] = {0.80,0.20,1,0,0,0,0,0};
	double YP7P8[] = {0.42,0.22,0.36,1,0,0,0,0,0};
	double YP3P7P8[] = {0.80,0.20,0.42,0.22,0.36,1,0,0,0,0,0};
	*/

	
	/*
	//Beta = 3
	
	double XP3[] = {0.69,0.31};
	double XP7[] = {0.45,0.55,0};
	double XP8[] = {0,0.33,0.67,0,0,0};
	double XP3P7[] = {0.69,0.31,0.45,0.55,0};
	double XP3P8[] = {0.69,0.31,0,0.33,0.67,0,0,0};
	double XP7P8[] = {0.45,0.55,0,0,0.33,0.67,0,0,0};
	double XP3P7P8[] = {0.69,0.31,0.45,0.55,0,0,0.33,0.67,0,0,0};
	
	double YP3[] = {1,0};
	double YP7[] = {0.38,0.29,0.33};
	double YP8[] = {1,0,0,0,0,0};
	double YP3P7[] = {1,0,0.38,0.29,0.33};
	double YP3P8[] = {1,0,1,0,0,0,0,0};
	double YP7P8[] = {0.38,0.29,0.33,1,0,0,0,0,0};
	double YP3P7P8[] = {1,0,0.38,0.29,0.33,1,0,0,0,0,0};
	*/

	printf("P3: Euclidean: %g\n    Manhattan: %g\n",EuclideanDistance(XP3,YP3,2),ManhattanDistance(XP3,YP3,2));
	printf("P7: Euclidean: %g\n    Manhattan: %g\n",EuclideanDistance(XP7,YP7,3),ManhattanDistance(XP7,YP7,3));
	printf("P8: Euclidean: %g\n    Manhattan: %g\n",EuclideanDistance(XP8,YP8,6),ManhattanDistance(XP8,YP8,6));
	printf("P3P7: Euclidean: %g\n    Manhattan: %g\n",EuclideanDistance(XP3P7,YP3P7,5),ManhattanDistance(XP3P7,YP3P7,5));
	printf("P3P8: Euclidean: %g\n    Manhattan: %g\n",EuclideanDistance(XP3P8,YP3P8,8),ManhattanDistance(XP3P8,YP3P8,8));
	printf("P7P8: Euclidean: %g\n    Manhattan: %g\n",EuclideanDistance(XP7P8,YP7P8,9),ManhattanDistance(XP7P8,YP7P8,9));
	printf("P3P7P8: Euclidean: %g\n    Manhattan: %g\n",EuclideanDistance(XP3P7P8,YP3P7P8,11),ManhattanDistance(XP3P7P8,YP3P7P8,11));
}