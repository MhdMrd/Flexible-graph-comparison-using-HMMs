#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "arff_binary_vA.h"

/*
	arffGraphs_binary_vA.exe   DirectoryName(IMDB-BINARY-vA) NbProperties(1) epsilon(0.0) 
	              MaxIterations(100) Threshold(100.0) OutputFile(Output.txt)
				  SaveInitHMMs(0) SaveFinalHMMs(0) DepthMaxDFS(1) NbVW(1)
*/
int main(int NbArg, char ** MesArg) {
  int Class,j,vertex,idGraph,NbGraphs[MaxClasses],IndexProp,T[MaxVertices],NbVW;
  int NbVertices,NbEdges,NbProperties,Iterations,MaxIterations,DepthMaxDFS, NbMCs[MaxProperties];
  int SaveInitHMMs,SaveFinalHMMs,NbComponents,Candidates[MaxProperties][MaxVertices][MaxLength],NbComponentsPerProperty[MaxProperties];
  double epsilon,Threshold,Duration,OverallDuration,TotalTrainingDuration,TotalVectorDuration;
  double VwMax, vWeight[MaxVertices][MaxVW];
  double Vectors[MaxSizeClass][MaxProperties][MaxSymbols],Vector[MaxClasses][MaxSizeClass][MaxProperties*MaxSymbols];
  char HMMfile[30], IndexP[5], IndexGraph[5], IndexClass[5], DirectoryName[100];
  char ClassFileNames[MaxClasses][100], ClassNames[MaxClasses][100];
  clock_t t,overall_t;
  int NbClasses;
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
  
  DepthMaxDFS = atoi(MesArg[9]);
  if((DepthMaxDFS < 0)||(DepthMaxDFS > MaxDepth)){
	  DepthMaxDFS = MaxDepth;
  }
 
  NbVW = atoi(MesArg[10]);
  
  strcpy(DirectoryName,MesArg[1]);
	
  srand(time(NULL));
  
  f = fopen(MesArg[6],"wt");
  if(!f){
	printf("error(%s)\n",MesArg[6]);
	return -1;
  }
  
  OverallDuration = 0.0;
  TotalTrainingDuration = 0.0;
  TotalVectorDuration = 0.0;

  overall_t = clock(); 

  NbClasses = DirectoryContent(DirectoryName,ClassFileNames,ClassNames);

  for(Class = 0; (Class < NbClasses); Class++ ){	

  fprintf(f,"\n**************************** class c%i *****************************\n",Class + 1); 	
  printf("__________________ class c%i __________________\n\n",Class+1);
  
  g = fopen(ClassFileNames[Class],"rt");
  if(!g){
	printf("error(%s)\n",ClassFileNames[Class]);
	return -1;
  }

  idGraph = 0;
  VwMax = 0.0;
  GetNextGraph(idGraph,&g,&NbVertices,Edges,&NbEdges,vWeight,&VwMax,&f);
  
  while(NbVertices != 0){
	graph = createGraph(NbVertices,vWeight,NbVW);
	
	for(j=0;(j<NbEdges);j++){
		addEdge(graph,Edges[j].src,Edges[j].dest);
	}
	
	SortAdjLists(graph);
	printGraph(graph,&f,NbVW);
	
	BuildMCs(graph,MCgraph,Candidates,NbProperties,DepthMaxDFS,T,&f,NbMCs);

	InitialHMMs(MCgraph,LambdaInit,NbMCs,DepthMaxDFS,NbProperties);

	NbComponents = 0;
   	//itoa(Class+1,IndexClass,10);
	snprintf(IndexClass, sizeof(IndexClass), "%d", Class+1);

   	//itoa(idGraph+1,IndexGraph,10);
	snprintf(IndexGraph, sizeof(IndexGraph), "%d", idGraph+1);
	
	for(IndexProp=0;(IndexProp < NbProperties);IndexProp++){
		
		if(SaveInitHMMs != 0){
			//itoa(IndexProp,IndexP,10);
			snprintf(IndexP, sizeof(IndexP), "%d", IndexProp);

			strcpy(HMMfile,"HmmInit_P");
			strcat(HMMfile,IndexP);
			strcat(HMMfile,"_c");
			strcat(HMMfile,IndexClass);
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
		TotalTrainingDuration += Duration;
		
		if(SaveFinalHMMs != 0){
			//itoa(IndexProp,IndexP,10);
			snprintf(IndexP, sizeof(IndexP), "%d", IndexProp);
			strcpy(HMMfile,"Hmm_P");
			strcat(HMMfile,IndexP);
			strcat(HMMfile,"_c");
			strcat(HMMfile,IndexClass);
			strcat(HMMfile,"_g");
			strcat(HMMfile,IndexGraph);
			strcat(HMMfile,".txt");
			SaveHMMtxt(Lambda[IndexProp],HMMfile);
		}

		t = clock(); 

		VectorHMM(Lambda[IndexProp],Vectors[idGraph][IndexProp]);

		t = clock() - t;
		Duration = ((double)t)*1000.0/CLOCKS_PER_SEC;
		TotalVectorDuration += Duration;

		fprintf(f,"Vector(P%i): [",IndexProp);

		
		if((Class == 0)&&(idGraph == 0)){
			NbComponentsPerProperty[IndexProp] = Lambda[IndexProp].M;
		}
		
		for(j=0;(j<Lambda[IndexProp].M);j++){
			Vector[Class][idGraph][NbComponents++] = Vectors[idGraph][IndexProp][j];
			fprintf(f,"%g",Vectors[idGraph][IndexProp][j]);
			if(j != Lambda[IndexProp].M - 1){
				fprintf(f,",");
			}else{
				fprintf(f,"]");
			}
		}	
		fprintf(f,"\n");
	} 
	printf(".");
	idGraph++;
    VwMax = 0.0;
    GetNextGraph(idGraph,&g,&NbVertices,Edges,&NbEdges,vWeight,&VwMax,&f);
	if(graph){
		for(vertex=0;vertex<graph->numVertices;vertex++){
			struct node* p = graph->adjLists[vertex];

			while (p) {
				struct node* q = p;
				p = p->next;
				free(q);
			}
			if(p) free(p);
			free(graph->Vweights[vertex]);
		}
		free(graph->VisitedVertices);
		free(graph->Vweights);
		free(graph);
    }
  }   
  printf("\n\n");
  fclose(g);
  NbGraphs[Class] = idGraph;
  }
	Arff(DirectoryName,Vector,NbGraphs,NbClasses,NbComponents,ClassNames,DepthMaxDFS,NbComponentsPerProperty,NbProperties);

	overall_t = clock() - overall_t;
	OverallDuration = ((double)overall_t)*1000.0/CLOCKS_PER_SEC;
	fprintf(f,"\n____________________________________________________________________________________\n\n");
	fprintf(f,"Overall program execution time = %g ms\n",OverallDuration);
	fprintf(f,"Total HMMs training time = %g ms ,  (%g%%) of the overall execution time\n",TotalTrainingDuration,100.0*(TotalTrainingDuration/OverallDuration));
	fprintf(f,"Total vectors computation time = %g ms ,  (%g%%) of the overall execution time\n\n",TotalVectorDuration,100.0*(TotalVectorDuration/OverallDuration));
    fclose(f);

	return 0;
}
