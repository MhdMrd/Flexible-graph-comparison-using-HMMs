How to set the parameters, to compile and to test this program ?
_____________________________________________________________________________

The 6 properties are:
p_(0)_(SrcVertex): the value of degree(SrcVertex) 
p_(1)_(SrcVertex): the proportion of immediate neighboring vertices of SrcVertex 
                   whose degree is lower or equal than degree(SrcVertex)
p_(2)_(SrcVertex): the last digit of degree(SrcVertex) 
p_(3)_(SrcVertex): the proportion of immediate neighboring vertices of SrcVertex whose
                   degree has a last digit lower than the last digit of degree(SrcVertex)
p_(4)_(SrcVertex): the parity of degree(SrcVertex) 
p_(5)_(SrcVertex): the proportion of immediate neighboring vertices of SrcVertex whose
                   degree has the same parity as the last digit of degree(SrcVertex)
_____________________________________________________________________________
Command line for compiling the file: arffGraphs.c

gcc -Wall -Wl,--stack,536870912 -o arffGraphs.exe arffGraphs.c
_____________________________________________________________________________
Command line for executing the file: arffGraphs.exe

arffGraphs.exe DirectoryName NbProperties epsilon  MaxIterations Threshold OutputFile SaveInitHMMs SaveFinalHMMs NbSlicesNeighborhood DepthMaxDFS
_____________________________________________________________________________			  
Examples of execution of the program: 

arffGraphs.exe IMDB-MULTI 6 0.0 100 100.0 Output_IMDB-MULTI.txt 0 0 5 1
_____________________________________________________________________________
The program results are in the OutputFile and in the file named BD_DirectoryName_DepthMaxDFS.arff 

Run WEKA using the resulting '.arff' files to perform classification experiments.
   - Download and install WEKA soft (WEKA 3.9 was used in [1])
   - Run WEKA
   - Click the button 'Explorer' to open a new window.
   - In the 'Preprocess' tab, click the button 'Open file...' to select your '.arff' file.
   - In the 'Classify' tab and below the button 'More options...', select the attribute 
     'class' that will be used as class during the classification. 
   - Under the title 'Classifier', click the button 'Choose' to select to select the desired 
     classifier. The classifier used with its default parameters in [1] is called 'SMO',
 	 available in the group named 'functions'.  
   - Under the 'Test options' title, select the radio button 'Cross-validation' 
     then fix your desired number of folds (the value 10 was used in [1]).
   - Click the 'Start' button to perform the classification, the results are displayed
     under the title 'Classifier output'.   
_____________________________________________________________________________
Execute the file "test.bat" to obtain the classification results of the Table 9 in [1]

[1] Mohammad Mourad Abdoulahi, Sylvain Iloga, "Flexible graph comparison using HMMs",
IEEE Access, vol 12, pp. 92988-93009, DOI 10.1109/ACCESS.2024.3415742, July 2024, IEEE.
