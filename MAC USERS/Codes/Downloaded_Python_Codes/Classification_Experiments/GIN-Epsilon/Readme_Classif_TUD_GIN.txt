How to perform graph classification following [1] using two implementations of the 
GIN-epsilon (Graph Isomorphism Networks) as classifiers for datasets from the TUDdatasets:

1- Go to https://www.python.org/downloads/windows/ and install Python 
   (I installed Python 3.9 for windows 64 bits).
   Skip this step if Python is already installed on your computer.

2- Go to https://www.scivision.dev/python-windows-visual-c-14-required/ and 
   follow the instructions for installing MS Visual C++ for Python. 
   Skip this step if MS Visual C++ for Python is already installed on your computer.
   The procedure for installing MS Visual C++ for Python is:
      a- Download  the "Build Tools for Visual Studio"
	  b- Select: "Workloads", then "Desktop development with C++"
	  c- For individual C++ components, select only: "Windows SDK" and "C++ x64/x86 build tools"
	  d- Install the two selected items.
	  
3- Install recent versions of the Python libraries listed below.
   Skip this step if Python is already installed on your computer. 
   For each library, the command line is: "pip install $LibraryName$" 
   where $LibraryName$ is:
	- "networkx"
	- "numpy" 
	- "pandas" 
	- "scipy" 
	- "sklearn" 
	- "torch" 
	- "torch-geometric" 

4- Select your experimental dataset. All the experimental datasets used in [1] are available in
   "../../../../Data/Experimental_Databases/Modified_datasets/" and  in   
   "../../../../Data/Experimental_Databases/Original_datasets/". 
   Each experimental dataset is a ".zip" file containing one directory where the dataset raw files are saved. 

5- Assume that the name of your selected dataset is "X", saved in the file "X.zip".
   Unzip the file "X.zip". This will generate a directory named "X" containing many files. 
   Copy all the content of "X" in the directory "./datasets/X/X/raw/" (you must CREATE this path).
   
   The paths "./datasets/IMDB-BINARY/IMDB-BINARY/raw/" and "./datasets/IMDB-MULTI/IMDB-MULTI/raw/" 
   are already created with the corresponding contains (the original datasets).
    
6- In the current directory, open the Python file "./main_gnn.py" using the Python text editor 
   (rigth-click on the file, then select "Edit with IDLE").

7- Insert the list of your selected datasets which HAVE NO EDGE LABELS just below the comment:
   "### Without edge labels". The dataset list is a comma-separated list of items, each item being the pair 
   "[DatasetName , UseNodeLabels]" where  "DatasetName" is the exact name of your dataset and
   "UseNodeLabels" is a boolean constant (True or False) which indicates if vertex labels are used 
   in the dataset. The following list is already inserted by default:

   dataset = [["IMDB-BINARY", False], ["IMDB-MULTI", False]]
   
   This means that the first selected dataset is "IMDB-BINARY" where vertex labels are not used and the 
   second selected dataset is "IMDB-MULTI" where vertex labels are also not used. You must change this line according
   to what you want to do. 

8- Save the file (File --> Save) then run it (Run --> Run the module). 
   The output is displayed on your screen and also saved in the file "Output.txt".
   
   The time cost of the program can sometimes be too long. This duration may be
   reduced/augmented by reducing/augmenting the values of the three following variables
   at the beginning of the program:

   - "num_reps"         : this is the number of folds for the cross-validation. 
                          The actual default value is 2. In [1] the value (num_reps = 10) is used.   

   - "num_epochs"       : this is the maximum number of epochs of the neural network. 
                          The actual default value is 2. In [1] the value (num_epochs = 10) is used.    
					 
   - "learning_rate"    : this is the learning_rate for weights update. 
                          The actual default value is 0.01. This default value is also used in [1].    


[1] Mohammad Mourad Abdoulahi, Sylvain Iloga, "Flexible graph comparison using HMMs" (Under review).