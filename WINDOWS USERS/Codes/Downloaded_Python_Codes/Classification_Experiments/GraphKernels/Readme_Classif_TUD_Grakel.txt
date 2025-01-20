How to perform graph classification  following [1] with SVM (Support Vector Machines) 
as classifier and baseline graph kernels using Grakel for datasets from the TUDdatasets:

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
	  
3- Go to https://ysig.github.io/GraKeL/0.1a8/documentation/installation.html and 
   install Grakel (this is a Python library for graph kernels). The command line 
   for the installing Grakel is: "pip install grakel"
   Skip this step if Grakel is already installed on your computer.

 
4- Select your experimental dataset. All the experimental datasets used in [1] are available in 
   "../../../../Data/Experimental_Databases/Modified_datasets/" and  in   
   "../../../../Data/Experimental_Databases/Original_datasets/". 
   Each experimental dataset is a ".zip" file containing one directory where the dataset raw files are saved. 
   
5- Create the directory "$HOME$/grakel_data/" and copy each experimental dataset (in the ".zip" format) in that directory. 
   On my computer, it corresponds to the directory "C:/Users/sylvain/grakel_data".
   
6- In the current directory, open the suitable Python file using the Python text editor 
   (rigth-click on the file, then select "Edit with IDLE").
   If you are using:
     
    a- A baseline graph kernel which ignores node attributes, open the file "./cv.py"
    b- A baseline graph kernel which needs node attributes, open the file "./cvAttr.py"
    c- The Weisfeiler-Lehman framework to carry a baseline graph kernel, open the file "./cvWL.py"
	
	Refer to https://ysig.github.io/GraKeL/0.1a8/graph_kernel.html for details concerning the 
	capabilities of each graph kernel in Grakel.

7- Uncomment (remove the symbol '#') the line which imports your selected APPLICABLE graph kernel. 
   This line starts with:  "from grakel.kernels import ..."
   The use of a graph kernel which is NOT APPLICABLE authomatically generates an error. 
   
   For example, for the original IMDB-BINARY dataset: 
   from grakel.kernels import ShortestPath

8- Assign the exact name of your selected dataset to the variable "DatasetName" in the statement:
   DatasetName = "..."  
   
   Replace the dots by the name of your selected dataset. 
   For example :
   DatasetName = "IMDB-BINARY" 
    
9- Uncomment (remove the symbol '#') the line which assigns your selected baseline graph kernel to the variable "gk". 
   This line starts with:  "gk = ".
   
   The baseline graph kernel selected here must be the same that was selected at step 7.
   For example, for the original IMDB-BINARY dataset:
   gk = ShortestPath(with_labels=False, normalize=True)
   
10- Save the file (File --> Save) then run it (Run --> Run the module).
    The output is displayed on your screen.
	The running time of the program may be very long depending on your selected dataset 
	and the selected baseline graph kernel.


[1] Mohammad Mourad Abdoulahi, Sylvain Iloga, "Flexible graph comparison using HMMs",
IEEE Access, vol 12, pp. 92988-93009, DOI 10.1109/ACCESS.2024.3415742, July 2024, IEEE.
