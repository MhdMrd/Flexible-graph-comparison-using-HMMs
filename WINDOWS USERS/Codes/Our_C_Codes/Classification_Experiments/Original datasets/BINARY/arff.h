#include "dfsgraphs.h"

#define MaxClasses 3
#define MaxSizeClass 500


int DirectoryContent(char * DirectoryName, char ClassFileNames[MaxClasses][100], char ClassNames[MaxClasses][100]) 
{ 
    struct dirent *de; 
	int i,j,k;
	char FileName[100];
  
    DIR *dr = opendir(DirectoryName); 
    if(!dr) return -1; 
	
	k = 0;
    for(i=0;((de = readdir(dr)) != NULL);i++){ 
        strcpy(FileName,DirectoryName); 
        strcat(FileName,"\\"); 
		if(de->d_name[0] != '.'){
			strcat(FileName,de->d_name); 
			strcpy(ClassFileNames[k],FileName);
			for(j=0;(de->d_name[j] != '.');j++){
				ClassNames[k][j] = de->d_name[j];
			}
			ClassNames[k][j] = 0;
			k++;
		}
	}
    closedir(dr);     
    return k; 
}

int Arff(char * DirectoryName, double Vectors[MaxClasses][MaxSizeClass][MaxProperties*MaxSymbols], int ClassSize[MaxClasses], int NbClasses, int NbComponents, char ClassNames[MaxClasses][100], int DepthMaxDFS, int NbComponentsPerProperty[MaxProperties], int NbProperties){
	FILE * f;
	int Class,IndexProp,Component,idGraph;
	char BDname[100], Depth[5];
	
	itoa(DepthMaxDFS,Depth,10);

	strcpy(BDname,"BD_");
	strcat(BDname,DirectoryName);
	strcat(BDname,"_");
	strcat(BDname,Depth);
	strcat(BDname,".arff");
	f = fopen(BDname, "w");
	if(!f) return -1;
	
	fprintf(f,"@RELATION BD_%s_%s\n",DirectoryName,Depth);

	fprintf(f,"@ATTRIBUTE class {");
	for(Class = 0; (Class < NbClasses); Class++ ){	
		if(Class != NbClasses-1){
			fprintf(f,"%s,",ClassNames[Class]);
		}else{
		fprintf(f,"%s}\n",ClassNames[Class]);
		}	
	}
	
	for(IndexProp = 0; IndexProp < NbProperties; IndexProp++){
		for(Component = 0; Component < NbComponentsPerProperty[IndexProp]; Component++){
			fprintf(f,"@ATTRIBUTE p_%i_x_%i NUMERIC\n",IndexProp,Component+1);
		}	
	}
	
	fprintf(f,"@DATA\n");
	
	for(Class = 0; (Class < NbClasses); Class++ ){	
		for(idGraph = 0; (idGraph < ClassSize[Class]); idGraph++){	
			fprintf(f,"%s,",ClassNames[Class]);
			for(Component = 0; Component < NbComponents; Component++){
				if(Component != NbComponents-1){
					if(Vectors[Class][idGraph][Component] == 0){
						fprintf(f,"0,");
					}else{
						fprintf(f,"%g,",Vectors[Class][idGraph][Component]);
					}	
				}else{
					if(Vectors[Class][idGraph][Component] == 0){
						fprintf(f,"0\n");
					}else{
						fprintf(f,"%g\n",Vectors[Class][idGraph][Component]);
					}	
				}	
			}	
		}
	}	
	fclose(f);
	return 0;
}	

