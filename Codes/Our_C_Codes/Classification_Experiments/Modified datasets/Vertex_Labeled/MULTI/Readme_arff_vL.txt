How to set the parameters, to compile and to test this program ?
_____________________________________________________________________________

The unique property for the database "IMDB-MULTI-vL" is:

p_(0)_(SrcVertex): (degree(SrcVertex) + label(SrcVertex)) % 3  
_____________________________________________________________________________
Command line for compiling the file: arffGraphs_multi_vL.c

gcc -Wall -o arffGraphs_multi_vL.out arffGraphs_multi_vL.c
_____________________________________________________________________________
Command line for executing the file: arffGraphs_multi_vL.out

./arffGraphs_multi_vL.out DirectoryName NbProperties epsilon  MaxIterations Threshold OutputFile SaveInitHMMs SaveFinalHMMs DepthMaxDFS
_____________________________________________________________________________			  
Exemples of execution of the program: 

./arffGraphs_multi_vL.out IMDB-MULTI-vL 1 0.0 100 100.0 Output_IMDB-MULTI-vL.txt 0 0 1
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
Execute the file "test.sh" in terminal to obtain the perfect classification results of [1]

[1] Mohammad Mourad Abdoulahi, Sylvain Iloga, "Flexible graph comparison using HMMs" (Under review).

