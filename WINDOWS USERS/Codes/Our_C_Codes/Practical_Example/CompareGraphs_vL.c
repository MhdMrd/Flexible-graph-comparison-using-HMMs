#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "dfsgraphs_vL.h"

/*
	CompareGraphs_vL.exe graphFile(Graphs_vL.txt) NbProperties(3) epsilon(0.0) 
	              MaxIterations(100) Threshold(100.0) OutputFile(Output.txt)
				  SaveInitHMMs(0) SaveFinalHMMs(0) NbSlicesNeighborhood(10) DepthMaxDFS (1)
*/
int main(int NbArg, char ** MesArg) {
  int i,j,vertex,idGraph,NbGraphs,IndexProp,T[MaxVertices],NbSlicesNeighborhood;
  int NbVertices,NbEdges,NbProperties,Iterations,MaxIterations,DepthMaxDFS, NbMCs[MaxProperties];
  int LabelList[MaxLabels], NbLabels, Labels[MaxVertices];
  int SaveInitHMMs,SaveFinalHMMs,NbComponents,Candidates[MaxProperties][MaxVertices][MaxLength];
  double epsilon,Threshold,Duration, EucliDist[MaxGraphs][MaxGraphs], ManhatDist[MaxGraphs][MaxGraphs];
  double Vectors[MaxGraphs][MaxProperties][MaxSymbols], Vector[MaxGraphs][MaxProperties*MaxSymbols];
  char HMMfile[30], IndexP[5], IndexGraph[5];
  clock_t t;
  struct Graph* graph;
  FILE * f, *g;
  SimpleEdge Edges[MaxEdges];
  MC MCgraph[MaxVertices][MaxProperties];
  HMM LambdaInit[MaxProperties], Lambda[MaxProperties];
  
  NbProperties = atoi(MesArg[2]);
  epsilon = atof(MesArg[3]);
  MaxIterations = atoi(MesArg[4]);
  Threshold = atof(MesArg[5]);
  SaveInitHMMs = atoi(MesArg[7]);
  SaveFinalHMMs = atoi(MesArg[8]);
  
  NbSlicesNeighborhood = atoi(MesArg[9]);
  if((NbSlicesNeighborhood < 2)||(NbSlicesNeighborhood > MaxSlicesNeighborhood)){
	  NbSlicesNeighborhood = MaxSlicesNeighborhood;
  }

  DepthMaxDFS = atoi(MesArg[10]);
  if((DepthMaxDFS < 0)||(DepthMaxDFS > MaxDepth)){
	  DepthMaxDFS = MaxDepth;
  }
 
  srand(time(NULL));
  
  f = fopen(MesArg[6],"wt");
  if(!f){
	printf("error(%s)\n",MesArg[6]);
	return -1;
  }
  
  g = fopen(MesArg[1],"rt");
  if(!g){
	printf("error(%s)\n",MesArg[1]);
	return -1;
  }
 
  idGraph = 0;
  GetNextGraph(idGraph,&g,&NbVertices,Edges,&NbEdges,LabelList,&NbLabels,Labels,&f);
  
  while(NbVertices != 0){
	graph = createGraph(NbVertices,Labels);
	
	for(j=0;(j<NbEdges);j++){
		addEdge(graph,Edges[j].src,Edges[j].dest);
	}
	
	SortAdjLists(graph);
	printGraph(graph,&f,LabelList);
	
	BuildMCs(graph,MCgraph,Candidates,NbProperties,DepthMaxDFS,T,&f,NbSlicesNeighborhood,NbMCs,LabelList);

	InitialHMMs(MCgraph,LambdaInit,NbMCs,DepthMaxDFS,NbProperties,NbSlicesNeighborhood,NbLabels);

	NbComponents = 0;
   	itoa(idGraph+1,IndexGraph,10);
	
	for(IndexProp=0;(IndexProp < NbProperties);IndexProp++){
		
		if(SaveInitHMMs != 0){
			itoa(IndexProp,IndexP,10);
			strcpy(HMMfile,"HmmInit_P");
			strcat(HMMfile,IndexP);
			strcat(HMMfile,"_g");
			strcat(HMMfile,IndexGraph);
			strcat(HMMfile,".txt");
			SaveHMMtxt(LambdaInit[IndexProp],HMMfile);
		}
		
		fprintf(f,"Training (P%i) ... ",IndexProp);
		t = clock(); 
		Iterations = Baum_Welch(LambdaInit[IndexProp],Candidates[IndexProp],T,epsilon,MaxIterations,&(Lambda[IndexProp]),NbMCs[IndexProp],Threshold);
		t = clock() - t;
		Duration = ((double)t)*1000.0/CLOCKS_PER_SEC;
		fprintf(f,": %i iterations\t Time = %g ms\n",Iterations,Duration);
		
		if(SaveFinalHMMs != 0){
			itoa(IndexProp,IndexP,10);
			strcpy(HMMfile,"Hmm_P");
			strcat(HMMfile,IndexP);
			strcat(HMMfile,"_g");
			strcat(HMMfile,IndexGraph);
			strcat(HMMfile,".txt");
			SaveHMMtxt(Lambda[IndexProp],HMMfile);
		}

		VectorHMM(Lambda[IndexProp],Vectors[idGraph][IndexProp]);
		fprintf(f,"Vector(P%i): [",IndexProp);
		for(j=0;(j<Lambda[IndexProp].M);j++){
			Vector[idGraph][NbComponents++] = Vectors[idGraph][IndexProp][j];
			fprintf(f,"%g",Vectors[idGraph][IndexProp][j]);
			if(j != Lambda[IndexProp].M - 1){
				fprintf(f,",");
			}else{
				fprintf(f,"]");
			}
		}	
		fprintf(f,"\n");
	} 
	idGraph++;
	GetNextGraph(idGraph,&g,&NbVertices,Edges,&NbEdges,LabelList,&NbLabels,Labels,&f);
	if(graph){
		for(vertex=0;vertex<graph->numVertices;vertex++){
			struct node* p = graph->adjLists[vertex];

			while (p) {
				struct node* q = p;
				p = p->next;
				free(q);
			}
			if(p) free(p);
		}
		free(graph->VisitedVertices);
		free(graph->Vlabels);
		free(graph);
     }
  }
  fclose(g);
  NbGraphs = idGraph;

	fprintf(f,"\n_________________________ Vectors (%i components) __________________________\n\n",NbComponents); 	
	for(i=0;(i<NbGraphs);i++){
		fprintf(f,"G%i:[",i+1);
		for(j=0;(j<NbComponents);j++){
			if(j != NbComponents-1){
				fprintf(f,"%g,",Vector[i][j]);
			}else{
				fprintf(f,"%g]\n",Vector[i][j]);
			}
		}	
	}	

	for(i=0;(i<NbGraphs);i++){
		for(j=0;(j<=i);j++){
			if(i != j){
				EucliDist[i][j] = EuclideanDistance(Vector[i],Vector[j],NbComponents);
				ManhatDist[i][j] = ManhattanDistance(Vector[i],Vector[j],NbComponents);
			}else{
				EucliDist[i][j] = 0.0;
				ManhatDist[i][j] = 0.0;
			}
		}	
	}	
	   
	fprintf(f,"\n_________________________ Euclidean dist. __________________________\n\n"); 	
	fprintf(f,"    \t");
	for(i=0;(i<NbGraphs);i++){
		fprintf(f,"[G%i]\t",i+1);
	}	
	fprintf(f,"\n");
	for(i=0;(i<NbGraphs);i++){
		fprintf(f,"[G%i]\t",i+1);
		for(j=0;(j<=i);j++){
			fprintf(f,"%g\t",EucliDist[i][j]);
		}
		fprintf(f,"\n");
	}	
	fprintf(f,"\n_________________________ Manhattan dist. __________________________\n\n"); 	
	fprintf(f,"    \t");
	for(i=0;(i<NbGraphs);i++){
		fprintf(f,"[G%i]\t",i+1);
	}	
	fprintf(f,"\n");
	for(i=0;(i<NbGraphs);i++){
		fprintf(f,"[G%i]\t",i+1);
		for(j=0;(j<=i);j++){
			fprintf(f,"%g\t",ManhatDist[i][j]);
		}
		fprintf(f,"\n");
	}	
    fclose(f);
		
	return 0;
}