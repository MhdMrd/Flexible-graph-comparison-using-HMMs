How to set the parameters, to compile and to test this program ?
_____________________________________________________________________________

The 3 properties are:
p_(0)_(SrcVertex): the parity of degree(SrcVertex) 
p_(1)_(SrcVertex): the value of label(SrcVertex) 
p_(2)_(SrcVertex): the proportion of immediate neighboring vertices of SrcVertex 
                   whose label is equal to label(SrcVertex)
_____________________________________________________________________________
Command line for compiling the file: CompareGraphs_vL.c

gcc -Wall -Wl,--stack,536870912 -o CompareGraphs_vL.exe CompareGraphs_vL.c
_____________________________________________________________________________
Command line for executing the file: CompareGraphs_vL.exe

CompareGraphs_vL.exe graphFile NbProperties epsilon  MaxIterations Threshold OutputFile SaveInitHMMs SaveFinalHMMs NbSlicesNeighborhood DepthMaxDFS
_____________________________________________________________________________			  
Examples of execution of the program: 

CompareGraphs_vL.exe Graphs_vL.txt 3 0.0 100 100.0 Output_Graphs_vL.txt 0 0 5 1
CompareGraphs_vL.exe Graphs_vL.txt 3 0.0 100 100.0 Output_Graphs_vL.txt 1 1 5 1
_____________________________________________________________________________

The program results are in the OutputFile. 
The distances are available at the bottom of the OutputFile.
__________________________________________________________________________________
Execute the file "test.bat" to obtain the vectors of the Table 4 in [1]

[1] Mohammad Mourad Abdoulahi, Sylvain Iloga, "Flexible graph comparison using HMMs",
IEEE Access, vol 12, pp. 92988-93009, DOI 10.1109/ACCESS.2024.3415742, July 2024, IEEE.
