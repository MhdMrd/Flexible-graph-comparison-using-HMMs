#include "hmm.h"

#define MaxGraphs 5
#define MaxProperties 3
#define MaxLabels 3
#define MaxSlicesNeighborhood 5


struct node {
  int vertex;
  struct node* next;
};

typedef struct SimpleEdge{
  int src;
  int dest;   
}SimpleEdge;

typedef struct Element{      
	int state;                    	  
	int symbol;                         
	int vertex;                         
} Element;

typedef struct MarkovChain{      
	int NbElements;                  	  
	Element Elements[MaxLength];        
} MC;


struct node* createNode(int v);

struct Graph {
  int numVertices;
  struct node** adjLists;
  int * Vlabels;
  int * VisitedVertices;
};


int SizeAdjLists(struct node* adjLists){
	int N = 0;
    struct node* temp = adjLists;
    while (temp) {
		N++;
		temp = temp->next;
	}  
	return N;
}

void SortAdjLists(struct Graph* graph)
{
	int t, Table[MaxVertices];
	int number,i,j,vertex,temp;
	struct node* tmp;
	
	for(vertex = 0; vertex < (graph)->numVertices; vertex++){
		tmp = (graph)->adjLists[vertex];
		number = 0;
		while (tmp) {
			Table[number++] = tmp->vertex;
			tmp = tmp->next;
		} 
		for(i = 0; i < number; i++)
		{
			temp = i;
			for(j = i + 1; j <number; j++)
			{
				if(Table[j] < Table[temp])
				{
					temp = j;
				}	
			}
			t = Table[i];
			Table[i] = Table[temp];
			Table[temp] = t;
		}
		
		tmp = (graph)->adjLists[vertex];
		for(i = 0; i < number; i++)
		{
			tmp->vertex = Table[i];
			tmp = tmp->next;
		}  
	}
	return;
}


int ExistingLabel(int l, int LabelList[MaxLabels], int NbLabels){
	int i;
	for(i=0;(i < NbLabels);i++){
		if(l == LabelList[i]){
			return i;
		}
	}
	return -1;
}


void GetNextGraph(int idGraph, FILE ** f, int * Nbvertices, SimpleEdge Edges[MaxEdges], int * NbEdges, int LabelList[MaxLabels], int * NbLabels, int Labels[MaxVertices] , FILE ** g){
	int i,j,k,l;
	char c,Ligne[100000], Val[100];
	
	if(idGraph == 0){
		fgets(Ligne,100000,*f);
		i = j = 0;
		do{
			k = 0;
			do{
				Val[k++] = Ligne[i++];
				c = Ligne[i];
			}while((c != ',')&&(c != '\n'));
			Val[k] = 0;
			LabelList[j] = atoi(Val);
			fprintf((*g),"%i",LabelList[j]);
			j++;
			fprintf((*g),"%c",c);
			i++;
		}while(c != '\n');
		(*NbLabels) = j;
	}
	
      (*Nbvertices) = (*NbEdges) = 0;	
	  fgets(Ligne,100000,*f);
	  Ligne[strlen(Ligne)-2] = '\n';
	  Ligne[strlen(Ligne)-1] = 0;

	  if(!(feof(*f))){
		i = j = 0;
		do{
			Val[j++] = Ligne[i++];
			c = Ligne[i];
		}while(c != '[');
		Val[j] = 0;
		(*Nbvertices) = atoi(Val);
		fprintf((*g),"\n_________________________ graph G%i __________________________\n",idGraph + 1); 	
		fprintf((*g),"\n%i",(*Nbvertices));
		
		j = 0;
		i++;
		fprintf((*g),"[");
		do{
			l = 0;
			do{
				Val[l++] = Ligne[i++];
				c = Ligne[i];
			}while((c != ',')&&(c != ']'));
			Val[l] = 0;
			l = atoi(Val);
			k = ExistingLabel(l,LabelList,*NbLabels);
			if(k == -1){
				printf("\n'%i' is not a valid label\n",l);
				return;
			}
			Labels[j++] = k;
			i++;
			if(c == ','){
				fprintf((*g),"%i,",LabelList[Labels[j-1]]);
			}else{
				fprintf((*g),"%i]",LabelList[Labels[j-1]]);
			}
		}while(c != ']');
		c = Ligne[i];
		if(c != '('){
			return;
		}
		
		(*NbEdges) = 0;
		i++;
		while(c != '\n'){
			j = 0;
			do{
				Val[j++] = Ligne[i++];
				c = Ligne[i];
			}while(c != ',');
			Val[j] = 0;
			Edges[(*NbEdges)].src = atoi(Val);
			fprintf((*g),"(%i,",Edges[(*NbEdges)].src);
			
			c = Ligne[++i];
			j = 0;
			do{
				Val[j++] = Ligne[i++];
				c = Ligne[i];
			}while(c != ')');
			Val[j] = 0;
			Edges[(*NbEdges)].dest = atoi(Val);
			fprintf((*g),"%i)",Edges[(*NbEdges)].dest);
			
			c = Ligne[++i];
			if((c != '(')&&(c != '\n')){
				printf("\nErreur format:%c\n",c);
				return;
			}
			(*NbEdges)++;
			i++;
		}
		fprintf((*g),"\n\n");
	  }else{
		  return;
	  }
	return;
}


void PrintMC(MC Delta){
	int i;
	
	for(i=0;(i<Delta.NbElements);i++){
		printf("(%i,%i)\t",Delta.Elements[i].state,Delta.Elements[i].symbol);
	}
	printf("\n");
	return;
}


void PrintMCfile(MC Delta, FILE ** f){
	int i;
	
	for(i=0;(i<Delta.NbElements);i++){
		fprintf((*f),"(%i,%i)",Delta.Elements[i].state,Delta.Elements[i].symbol);
	}
	fprintf((*f),"\n");
	return;
}


void PrintMCfileVertices(MC Delta, FILE ** f){
	int i;
	
	for(i=0;(i<Delta.NbElements);i++){
		fprintf((*f),"(%i,%i)",Delta.Elements[i].state,Delta.Elements[i].symbol);
	}
	fprintf((*f),"    ****   ");

	for(i=0;(i<Delta.NbElements);i++){
		fprintf((*f),"(%i)",Delta.Elements[i].vertex + 1);
	}
	fprintf((*f),"\n");
	return;
}

// Create a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Create graph
struct Graph* createGraph(int vertices, int Labels[MaxVertices]) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));
  graph->VisitedVertices = (int *)malloc(vertices * sizeof(int));
  graph->Vlabels  = (int *)malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->Vlabels[i] = Labels[i];
  }
  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest) {
  // Add edge from src to dest
  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  // Add edge from dest to src
  if(src != dest){
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
  }
}

// Print the graph
void printGraph(struct Graph* graph, FILE ** f, int LabelList[MaxLabels]) {
  int v;

  for (v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjLists[v];
    fprintf((*f),"vertex %d(%i): [", v,LabelList[graph->Vlabels[v]]);
    while (temp) {
      fprintf((*f),"%d", temp->vertex);
      temp = temp->next;
      if(temp){
         fprintf((*f),",");
      }
    }
    fprintf((*f),"]\n");
  }
  fprintf((*f),"\n");
}

int IndexLabelEqual(struct Graph* graph, int vertex, int NbSlicesNeighborhood, int LabelList[MaxLabels]){
    struct node* temp = graph->adjLists[vertex];
	int x,y,n, m, Index;
	double z, pas;
	
	n = 0;
	x = LabelList[graph->Vlabels[vertex]];
	m = SizeAdjLists(graph->adjLists[vertex]);
    while (temp) {
		y = LabelList[graph->Vlabels[temp->vertex]];
		if(x == y){
			n++;
		}
		temp = temp->next;
	}  
	
	if(n == 0){
		return 0;
	}
	
	z = 100.0*n;
	z /= (m+MinDouble);
	pas = 100.0/NbSlicesNeighborhood;
	Index = (int)(z / pas);
	
	return Index;
}


int Property(struct Graph* graph, int src, int IndexProp, int NbSlicesNeighborhood, int LabelList[MaxLabels]){
	int p,x;
	switch(IndexProp){
		case 0:{
			x = SizeAdjLists(graph->adjLists[src]);
			p = x % 2;
			break;
		}
		case 1:{
			p = graph->Vlabels[src];
			break;
		}
		case 2:{
			p = IndexLabelEqual(graph,src,NbSlicesNeighborhood,LabelList);
			break;
		}
	}
	return p;
}


void BuildMCdfs(struct Graph* graph, int vertex, int * depth, MC MCgraph[MaxProperties], int * Index, int NbProperties, int depthMax, int NbSlicesNeighborhood, int LabelList[MaxLabels]) {
  int IndexProp;
  struct node* temp = graph->adjLists[vertex];

  graph->VisitedVertices[vertex] = 1;
  while (temp != NULL) {
    int connectedVertex = temp->vertex;

    if (graph->VisitedVertices[connectedVertex] == 0) {
      (*depth)++;
	  if(*depth <= depthMax){
		for(IndexProp = 0;(IndexProp < NbProperties);IndexProp++){
			MCgraph[IndexProp].Elements[*Index].state = *depth;
			MCgraph[IndexProp].Elements[*Index].symbol = Property(graph,connectedVertex,IndexProp,NbSlicesNeighborhood,LabelList);
			MCgraph[IndexProp].Elements[*Index].vertex = connectedVertex;
		}	
		(*Index)++;
		BuildMCdfs(graph, connectedVertex, depth,MCgraph,Index,NbProperties,depthMax,NbSlicesNeighborhood,LabelList);
	  }
      (*depth)--;
    }
    temp = temp->next;
  }
  return;
}


int ExistingMC(MC Src[MaxProperties], int Taille, MC Liste[MaxVertices][MaxProperties], int NbMCs, int Property){
	int i,j,n;
	
	for(i=0;i<NbMCs;i++){
		if(Src[Property].NbElements == Liste[i][Property].NbElements){
			n = 0;
			for(j=0;j<Src[Property].NbElements;j++){
				if(
				   (Src[Property].Elements[j].state == Liste[i][Property].Elements[j].state)&&
				   (Src[Property].Elements[j].symbol == Liste[i][Property].Elements[j].symbol)
				  ){
					n++;
				}
			}
			if(n == Src[Property].NbElements){
				return 1;
			}
		}
	}
	return 0;
}

void BuildMCs(struct Graph* graph, MC MCgraph[MaxVertices][MaxProperties], int Candidates[MaxProperties][MaxVertices][MaxLength], int NbProperties, int depthMax, int T[MaxVertices], FILE ** f, int NbSlicesNeighborhood, int NbMCs[MaxProperties], int LabelList[MaxLabels]){
	int i,j,depth, Index, vertex, IndexProp, Taille[MaxVertices];
	MC MCgraph1[MaxVertices][MaxProperties];
	
	for(vertex=0;vertex<graph->numVertices;vertex++){
		for(i=0;i<graph->numVertices;i++){
			graph->VisitedVertices[i] = 0;
		}
		depth = 0;
		Index = 1;
		for(IndexProp = 0;(IndexProp < NbProperties);IndexProp++){
			MCgraph1[vertex][IndexProp].Elements[0].state = depth;
			MCgraph1[vertex][IndexProp].Elements[0].symbol = Property(graph,vertex,IndexProp,NbSlicesNeighborhood,LabelList);
			MCgraph1[vertex][IndexProp].Elements[0].vertex = vertex;
		}	
		BuildMCdfs(graph,vertex,&depth,MCgraph1[vertex],&Index,NbProperties,depthMax,NbSlicesNeighborhood,LabelList);
		for(IndexProp = 0;(IndexProp < NbProperties);IndexProp++){
			MCgraph1[vertex][IndexProp].NbElements = Index;
		}
		Taille[vertex] = Index;
	}
	
	for(IndexProp = 0;(IndexProp < NbProperties);IndexProp++){
		NbMCs[IndexProp] = 0;
		for(vertex=0;vertex<graph->numVertices;vertex++){
			if(Taille[vertex] >= 2){
				i = ExistingMC(MCgraph1[vertex],Taille[vertex],MCgraph,NbMCs[IndexProp],IndexProp);
				if(i == 0){
					MCgraph[NbMCs[IndexProp]][IndexProp].NbElements = MCgraph1[vertex][IndexProp].NbElements;
					for(j=0;j<MCgraph[NbMCs[IndexProp]][IndexProp].NbElements;j++){
						MCgraph[NbMCs[IndexProp]][IndexProp].Elements[j].state = MCgraph1[vertex][IndexProp].Elements[j].state;
						MCgraph[NbMCs[IndexProp]][IndexProp].Elements[j].symbol = MCgraph1[vertex][IndexProp].Elements[j].symbol;
						MCgraph[NbMCs[IndexProp]][IndexProp].Elements[j].vertex = MCgraph1[vertex][IndexProp].Elements[j].vertex;
					}
					T[NbMCs[IndexProp]] = Taille[vertex];
					NbMCs[IndexProp]++;
				}
			}
		}
	}
	
	for(IndexProp = 0;(IndexProp < NbProperties);IndexProp++){
		
		fprintf((*f),"MCs for P%i:\n",IndexProp);
		
		for(j=0;j<NbMCs[IndexProp];j++){
			
			fprintf((*f),"%i:\t",j+1);
			PrintMCfileVertices(MCgraph[j][IndexProp],f);
			for(i=0;(i < T[j]);i++){
				Candidates[IndexProp][j][i] = MCgraph[j][IndexProp].Elements[i].symbol;
			}
		}
		fprintf((*f),"\n");
	}
	return;
}

void InitialHMMs(MC MCgraph[MaxVertices][MaxProperties], HMM Lambda[MaxProperties], int NbMCs[MaxProperties], int depthMax, int NbProperties, int NbSlicesNeighborhood, int NbLabels){
	int i,j,k,IndexProp,State,NextState,Symbol,From[MaxStates],UseOfState[MaxStates];
	double Sum;
	
	for(IndexProp=0;(IndexProp < NbProperties);IndexProp++){
		Lambda[IndexProp].N = depthMax + 1;                 
		switch(IndexProp){
			case 0:{
				Lambda[IndexProp].M = 2;                                
				break;
			}
			case 1:{
				Lambda[IndexProp].M = NbLabels;                                
				break;
			}
			case 2:{
				Lambda[IndexProp].M = NbSlicesNeighborhood + 1;                                
				break;
			}
		}		
	}
	
	for(IndexProp=0;(IndexProp < NbProperties);IndexProp++){
		for(i=0;(i < Lambda[IndexProp].N);i++){
			Lambda[IndexProp].Pi[i] = 0.0;
			From[i] = 0;
			UseOfState[i] = 0;
			for(j=0;(j < Lambda[IndexProp].N);j++){
				Lambda[IndexProp].A[i][j] = 0.0;
			}
			for(j=0;(j < Lambda[IndexProp].M);j++){
				Lambda[IndexProp].B[i][j] = 0.0;
			}
		}

		for(i=0;(i < NbMCs[IndexProp]);i++){
			for(j=0;(j < MCgraph[i][IndexProp].NbElements);j++){
				if(j != MCgraph[i][IndexProp].NbElements -1){
					State = MCgraph[i][IndexProp].Elements[j].state;
					NextState = MCgraph[i][IndexProp].Elements[j+1].state;
					Symbol = MCgraph[i][IndexProp].Elements[j].symbol;

					From[State] += 1;
					UseOfState[State] += 1;
					Lambda[IndexProp].A[State][NextState] += 1.0;
					Lambda[IndexProp].B[State][Symbol] += 1.0;
					
					if(j == 0){
						Lambda[IndexProp].Pi[State] += 1.0;
					}
				}else{
					State = MCgraph[i][IndexProp].Elements[j].state;
					Symbol = MCgraph[i][IndexProp].Elements[j].symbol;

					UseOfState[State] += 1;
					Lambda[IndexProp].B[State][Symbol] += 1.0;
				}
				
			}	
		}	
	
		for(i=0;(i < Lambda[IndexProp].N);i++){
			Lambda[IndexProp].Pi[i] /= (NbMCs[IndexProp]+Epsi);
			for(j=0;(j < Lambda[IndexProp].N);j++){
				Lambda[IndexProp].A[i][j] /= (From[i]+Epsi);
			}
		}
		for(j=0;(j < Lambda[IndexProp].N);j++){
			for(k=0;(k < Lambda[IndexProp].M);k++){
				Lambda[IndexProp].B[j][k] /= (UseOfState[j]+Epsi);
			}
		}

		Sum = 0.0;
		for(i=0;(i < Lambda[IndexProp].N);i++){
			Sum += Lambda[IndexProp].Pi[i];
		}	
		Sum = fabs(1.0 - Sum)/Lambda[IndexProp].N;
		for(i=0;(i < Lambda[IndexProp].N);i++){
			Lambda[IndexProp].Pi[i] += Sum;
		}	
		for(i=0;(i < Lambda[IndexProp].N);i++){
			Sum = 0.0;
			for(j=0;(j < Lambda[IndexProp].N);j++){
				Sum += Lambda[IndexProp].A[i][j];
			}
			Sum = fabs(1.0 - Sum)/Lambda[IndexProp].N;
			for(j=0;(j < Lambda[IndexProp].N);j++){
				Lambda[IndexProp].A[i][j] += Sum;
			}	
		}	
		
		for(j=0;(j < Lambda[IndexProp].N);j++){
			Sum = 0.0;
			for(k=0;(k < Lambda[IndexProp].M);k++){
				Sum += Lambda[IndexProp].B[j][k];
			}
			Sum = fabs(1.0 - Sum)/Lambda[IndexProp].M;
			for(k=0;(k < Lambda[IndexProp].M);k++){
				Lambda[IndexProp].B[j][k] += Sum;
			}	
		}
		
		StationaryDistribution(&Lambda[IndexProp]);
	}
	
	return;
}	

double EuclideanDistance(double X[MaxProperties*MaxSymbols], double Y[MaxProperties*MaxSymbols], int N){
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

double ManhattanDistance(double X[MaxProperties*MaxSymbols], double Y[MaxProperties*MaxSymbols], int N){
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

