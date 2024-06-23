#define MaxVertices 20
#define MaxLength 20
#define MaxEdges 20
#define MaxSymbols 20     
#define MaxDepth 5
#define MaxStates (MaxDepth + 1) 			
		         
#define MinDouble 1e-80
#define MinFloat 1e-10                
#define Epsi 1                           


typedef struct HMM{
	int N;
	int M;
	double A[MaxStates][MaxStates];
	double B[MaxStates][MaxSymbols];
	double Pi[MaxStates];
	double Phi[MaxStates];				
}HMM;


void AdjustHMM(HMM * Lambda){
	int i,j;

	for(i=0;(i < (*Lambda).N);i++){
		for(j=0;(j < (*Lambda).N);j++){
			if((*Lambda).A[i][j] < MinFloat) (*Lambda).A[i][j] = 0.0;
		}
	}
	for(i=0;(i < (*Lambda).N);i++){
		for(j=0;(j < (*Lambda).M);j++){
			if((*Lambda).B[i][j] < MinFloat) (*Lambda).B[i][j] = 0.0;
		}
	}
	for(i=0;(i < (*Lambda).N);i++){
		if((*Lambda).Pi[i] < MinFloat) (*Lambda).Pi[i] = 0.0;
	}
	for(i=0;(i < (*Lambda).N);i++){
		if((*Lambda).Phi[i] < MinFloat) (*Lambda).Phi[i] = 0.0;
	}
	return;
}


void CopyHMM(HMM * Lambda1, HMM Lambda2){
	int i,j;
	
	(*Lambda1).N = Lambda2.N;
	(*Lambda1).M = Lambda2.M;
	for(i = 0; i < Lambda2.N; i++)
	{
		(*Lambda1).Pi[i] = Lambda2.Pi[i];	
		(*Lambda1).Phi[i] = Lambda2.Phi[i];	
		for(j = 0; j < Lambda2.N; j++)
		{
			(*Lambda1).A[i][j] = Lambda2.A[i][j];
		}
		for(j = 0; j < Lambda2.M; j++)
		{
			(*Lambda1).B[i][j] = Lambda2.B[i][j];
		}
	}
	return;
}

void SaveHMMtxt(HMM Lambda, char * OutputTxtFile){
	int i,j;
	FILE * TxtFile;
	
	TxtFile = fopen(OutputTxtFile, "wt");
	fprintf(TxtFile, "\nHMM parameters: %d states and %d symbols\n\n", Lambda.N, Lambda.M);
	fprintf(TxtFile, "Matrix A :\n\n");

	for(i = 0; i < Lambda.N; i++)
	{
		for(j = 0; j < Lambda.N; j++)
			fprintf(TxtFile, "%g\t", Lambda.A[i][j]);

		fprintf(TxtFile, "\n");
 	}

	fprintf(TxtFile, "\n\nMatrix B :\n\n");

	for(i = 0; i < Lambda.N; i++)
	{
		for(j = 0; j < Lambda.M; j++)
			fprintf(TxtFile, "%g\t", Lambda.B[i][j]);

		fprintf(TxtFile, "\n");
 	}

	fprintf(TxtFile, "\n\nVector Pi :\n\n");

	for(j = 0; j < Lambda.N; j++)
		fprintf(TxtFile, "%g\t", Lambda.Pi[j]);

	fprintf(TxtFile, "\n");

	fprintf(TxtFile, "\n\nVector Phi :\n\n");

	for(j = 0; j < Lambda.N; j++)
		fprintf(TxtFile, "%g\t", Lambda.Phi[j]);

	fprintf(TxtFile, "\n");
	fclose(TxtFile);
	return;
}

void CopyMatrix(double M1[MaxStates][MaxStates], double M2[MaxStates][MaxStates], int NbRow, int NbCol)
{
	int i, j;
	for(i = 0; i < NbRow; i++)
	{
		for(j = 0; j < NbCol; j++)
		{
			M1[i][j] = M2[i][j];
		}
	}
	return;
}

void StationaryDistribution(HMM * Lambda)
{
	int i,j,n, k,nb;
	double A_tem[MaxStates][MaxStates], A_Product[MaxStates][MaxStates];
	
	n = (*Lambda).N;
	CopyMatrix(A_tem, (*Lambda).A,n,n);
	nb = 0;
	do
	{
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				A_Product[i][j] = 0.0;
				for(k = 0; k < n; k++)
				{
					A_Product[i][j] += A_tem[i][k] * (*Lambda).A[k][j];
				}
			}
		}
		CopyMatrix(A_tem, A_Product, n, n);
		nb++;
	}while(nb <= 100);

	for(i = 0; i < n; i++)
	{
		(*Lambda).Phi[i] = (double)A_Product[0][i];
	}
	
	return;
}

void Forward(HMM Lambda, int O[MaxLength], int t_bar, long double Alpha[MaxLength][MaxStates])
{
	int i, j, t;
	long double sum_alpha;


	for(j = 0; j < Lambda.N; j++)
	{
		Alpha[0][j] = Lambda.B[j][O[0]] * Lambda.Pi[j];			
	}

	for(t = 0; t < t_bar - 1; t++)
	{

		for(j = 0; j < Lambda.N; j++)
		{

			sum_alpha = 0.0;

			for(i = 0; i < Lambda.N; i++)
			{
				sum_alpha += Alpha[t][i] * Lambda.A[i][j];
			}

			Alpha[t+1][j] = sum_alpha * Lambda.B[j][O[t+1]];		
		}

	}

}

void Backward(HMM Lambda, int O[MaxLength], int t_bar, long double Beta[MaxLength][MaxStates], int T)
{
	int i, j, t;
	long double sum_beta;

	for(i = 0; i < Lambda.N; i++)
	{
		Beta[T-1][i] = 1;				
	}

	for(t = T - 1; t >= t_bar; t--)
	{
		for(i = 0; i < Lambda.N; i++)
		{
			sum_beta = 0.0;
			for(j = 0; j < Lambda.N; j++)
			{
				sum_beta += Lambda.A[i][j] * Lambda.B[j][O[t]] * Beta[t][j];
			}

			Beta[t-1][i] = sum_beta;			

		}
	}
}


double Forward_Backward(HMM Lambda, int O[MaxLength], int t_bar, int T)
{
    int j;
    double Proba_Observ = 0.0;
	long double Alpha[MaxLength][MaxStates], Beta[MaxLength][MaxStates];
	
	Forward(Lambda,O,T,Alpha);
	Backward(Lambda,O,1,Beta,T);
    for(j = 0; j < Lambda.N; j++)
	{

		Proba_Observ += (double)(Alpha[t_bar][j] * Beta[t_bar][j]);
	}

	return Proba_Observ;
}

void CalculXi(HMM Lambda, int O[MaxLength], int T, long double Alpha[MaxLength][MaxStates], long double Beta[MaxLength][MaxStates], double Proba_Observ, long double Xi[MaxLength][MaxStates][MaxStates])
{
	int i, j, t;

	for(t = 0; t < T - 1; t++)
	{
		for(i = 0; i < Lambda.N; i++)
		{
			for(j = 0; j < Lambda.N; j++)
			{
				Xi[t][i][j] = Alpha[t][i] * Lambda.A[i][j] * Lambda.B[j][O[t + 1]] * Beta[t + 1][j];
				Xi[t][i][j] /= (Proba_Observ + MinDouble);
			}
		}
	}
}

void CalculGamma(HMM Lambda, int O[MaxLength], int T, long double Alpha[MaxLength][MaxStates], long double Beta[MaxLength][MaxStates], double Proba_Observ, long double Gamma[MaxLength][MaxStates])
{
	int j, t;

	for(t = 0; t < T; t++)
	{
		for(j = 0; j < Lambda.N; j++)
		{
			Gamma[t][j] = Alpha[t][j] * Beta[t][j];
			Gamma[t][j] /= (Proba_Observ + MinDouble);
		}
	}
}


int Baum_Welch(HMM Lambda_Init, int O[MaxVertices][MaxLength], int T[MaxVertices], double epsilon, int MaxIterations, HMM * Lambda, int NbMCs, double Threshold)
{
    HMM Lambda_Old, Lambda_New;
   int i, j, k, t, t_bar,l, iterations;
	double Rate, Proba_Old[MaxVertices], Proba_New[MaxVertices];
	long double Alpha[MaxVertices][MaxLength][MaxStates], Beta[MaxVertices][MaxLength][MaxStates];
	long double Alpha_bar[MaxVertices][MaxLength][MaxStates], Beta_bar[MaxVertices][MaxLength][MaxStates];
	long double Gamma[MaxVertices][MaxLength][MaxStates], Xi[MaxVertices][MaxLength][MaxStates][MaxStates];
	long double sum_xi, sum_gamma, s;
	
	CopyHMM(&Lambda_Old,Lambda_Init);

	
	for(k = 0; k < NbMCs; k++)
	{
		Forward(Lambda_Old,O[k],T[k],Alpha[k]);
		Backward(Lambda_Old,O[k],1,Beta[k],T[k]);
	}	
	
	iterations = 0;					
	do
	{
		iterations++;

		for(k = 0; k < NbMCs; k++)
		{
			t_bar = rand()%(T[k]);
			Proba_Old[k] = 0.0;
			for(j = 0; j < Lambda_Old.N; j++)
			{
				Proba_Old[k] += (double)(Alpha[k][t_bar][j] * Beta[k][t_bar][j]);
			}
			
			CalculGamma(Lambda_Old, O[k], T[k], Alpha[k], Beta[k], Proba_Old[k], Gamma[k]);	
			
			CalculXi(Lambda_Old, O[k], T[k], Alpha[k], Beta[k], Proba_Old[k], Xi[k]);						
		}

		Lambda_New.N = Lambda_Old.N;
		Lambda_New.M = Lambda_Old.M;
		
        for(i = 0; i < Lambda_Old.N; i++)			
		{
			Lambda_New.Pi[i] = 0.0;	
			for(k = 0; k < NbMCs; k++)
			{
				Lambda_New.Pi[i] += (double)Gamma[k][0][i];
			}	
			Lambda_New.Pi[i] /= NbMCs;
		}

		for(i = 0; i < Lambda_Old.N; i++)			
		{

			for(j = 0; j < Lambda_Old.N; j++)
			{
				sum_xi = 0.0;
				sum_gamma = 0.0;

				for(k = 0; k < NbMCs; k++)
				{
					for(t = 0; t < T[k] - 1; t++)
					{
						sum_xi += Xi[k][t][i][j];
						sum_gamma += Gamma[k][t][i];

					}
				}
				Lambda_New.A[i][j] = (double)(sum_xi / (sum_gamma + MinDouble));
			}

		}
	
		for(j = 0; j < Lambda_Old.N; j++)				
		{

			for(l = 0; l < Lambda_Old.M; l++)
			{
				s = 0.0;
				sum_gamma = 0.0;
				
				for(k = 0; k < NbMCs; k++)
				{
					for(t = 0; t < T[k]; t++)
					{
						if(O[k][t] == l)
						{
							s += Gamma[k][t][j];
						}
					}


					for(t = 0; t < T[k]; t++)
					{
						sum_gamma += Gamma[k][t][j];
					}
				}
				Lambda_New.B[j][l] = (double)(s / (sum_gamma + MinDouble));
			}
		}

		for(k = 0; k < NbMCs; k++)
		{
			Forward(Lambda_New,O[k],T[k],Alpha_bar[k]);
			Backward(Lambda_New,O[k],1,Beta_bar[k],T[k]);
		}
		
		Rate = 0.0;
		for(k = 0; k < NbMCs; k++)
		{
			Proba_New[k] = 0.0;
			for(j = 0; j < Lambda_New.N; j++)
			{
				Proba_New[k] += (double)(Alpha_bar[k][t_bar][j] * Beta_bar[k][t_bar][j]);
			}
			if(fabs(Proba_New[k] - Proba_Old[k]) <= epsilon){
				Rate += 1.0;
			}
        }
		Rate = (Rate/NbMCs)*100;
		if(Rate < Threshold)
		{
			CopyHMM(&Lambda_Old,Lambda_New);
			for(k = 0; k < NbMCs; k++)
			{
				for(t = 0; t < T[k]; t++)
				{
					for(i = 0; i < Lambda_New.N; i++)
					{
						Alpha[k][t][i] = Alpha_bar[k][t][i]; 
						Beta[k][t][i] = Beta_bar[k][t][i];
					}
				}
			}

		}
	}while((Rate < Threshold) && (iterations <= MaxIterations));
	
	StationaryDistribution(&Lambda_New);
	
	AdjustHMM(&Lambda_New);
	
	CopyHMM(Lambda,Lambda_New);
	
	return iterations;

}


double ProbaSymbolLongPeriod(int k, HMM Lambda){
	double E;
	int i;
	
	E = 0.0;
	for(i=0;(i < Lambda.N);i++){
		E += Lambda.Phi[i]*Lambda.B[i][k];
	}
	return E;
}

void VectorHMM(HMM Lambda, double V[MaxSymbols]){
	int k;
	
	for(k=0;(k < MaxSymbols);k++){
		V[k] = 0.0;
	}
	
	for(k=0;(k < Lambda.M);k++){
		V[k] = ProbaSymbolLongPeriod(k,Lambda);
	}
	return;
}

