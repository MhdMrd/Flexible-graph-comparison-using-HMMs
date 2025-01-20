In order to run existing Python modules for graph classification using baseline graph kernels
or GIN-epsilon (Graph Isomorphism Networks) on the modified datasets experimented in [1],  each modified dataset
was simply renamed using the name of an original dataset from the TUDdataset repository having indentical 
characteristics (node labels, node attributes, edge labels, edge attributes) as indicated below:		
___________________________________________________________________________________
Original		<--> 		$ModifiedDatasetName$
___________________________________________________________________________________
DD				<--> 		IMDB-BIN-vL, IMDB-MULTI-vL 		
Letter-low  	<--> 		IMDB-BIN-vA, IMDB-MULTI-vA
___________________________________________________________________________________

Each directory "$ModifiedDatasetName$" contains:

1- A file named "$ModifiedDatasetName$_output.txt" which contains statistics related to the modified dataset.

2- A sub-directory named "$ModifiedDatasetName$_OurFormat" which contains the raw text files   
   of the modified dataset in the format taken by method proposed in [1].
   
3- A sub-directory named "$ModifiedDatasetName$_TUDatasetFormat" which contains the raw text files   
   of the modified dataset in the TUDataset format.
   
4- The abovementionned renamed '.zip'  file associated with the modified dataset. 
   This file can directly be used for classification purposes.


[1] Mohammad Mourad Abdoulahi, Sylvain Iloga, "Flexible graph comparison using HMMs",
IEEE Access, vol 12, pp. 92988-93009, DOI 10.1109/ACCESS.2024.3415742, July 2024, IEEE.
