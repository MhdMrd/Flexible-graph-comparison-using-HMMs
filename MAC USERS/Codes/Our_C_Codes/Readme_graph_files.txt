The graphs used in [1] are stored in text files and each file contains UNDIRECTED 
graphs having the same characteristics (unlabeled, vertex-labeled or vertex-attributed).

1-When the graphs are unlabeled, from line 1 until the end of the file, each line 
  describes a graph and be decomposed as follows from the left to the rigth:
  
  a- The line starts with the number of vertices of the graph.
  b- Followed by a list of pairs (x,y) corresponding to the edges, where x and y refer 
     to two vertex identifiers of the graph. The vertex identifiers always start from 0. 
	 There is no separator between the number of vertices and the first edge. Similarly,
     there is  no separator between two edges. The last edge is immediately followed by '\n'.	 
	 The order of appearence of the edges is not important.
	
	As an example, the line below describes a graph composed of 4 vertices numbered from 0 to 3
	such that the vertex 0 is directly connected to the three other vertices and the vertex 1 is 
	also connected to the vertex 2.	
 
    4(0,1)(0,2)(0,3)(1,2)

2- When the graphs are vertex-attributed, the first line of the file is the coma-separated
   list of possible vertex labels. The labels are positive integers and the last label 
   is immediately followed by '\n'. From line 2 until the end of the file, each line describes 
   a graph and be decomposed as follows from the left to the rigth: 
  
  a- The line starts with the number of vertices of the graph.
  b- Followed by the ORDERED coma-separated list of vertex labels into square brackets,
     starting from the label of the vertex 0, until the label of the last vertex. 
  c- Followed by a list of pairs (x,y) corresponding to the edges, where x and y refer 
     to two vertex identifiers of the graph. The vertex identifiers always start from 0. 
	 There is no separator between the number of vertices and the first edge. Similarly,
     there is  no separator between two edges. The last edge is immediately followed by '\n'.	 
	 The order of appearence of the edges is not important.
	
	As an example, the line below describes a graph composed of 4 vertices numbered from 0 to 3
	such that the vertex 0 is directly connected to the three other vertices and the vertex 1 is 
	also connected to the vertex 2. The labels of the vertices 0 to 3 are respectively
    7,4,3 and 4.   	
 
    4[7,4,3,4](0,1)(0,2)(0,3)(1,2)


3- When the graphs are vertex-labeled, from line 1 until the end of the file, each line 
  describes a graph and be decomposed as follows from the left to the rigth:
  
  a- The line starts with the number of vertices of the graph.
  b- Followed by the ORDERED list of vertex attributes into curly braces, with each 
     attribute enclosed into brackets, starting from the attribute of the vertex 0, 
	 until the attribute of the last vertex.  When each vertex has many attributes, 
	 they appear in an ORDERED coma-separated list into curly braces. Attributes are 
	 floating point numbers which can be signed or unsigned. 
  c- Followed by a list of pairs (x,y) corresponding to the edges, where x and y refer 
     to two vertex identifiers of the graph. The vertex identifiers always start from 0. 
	 There is no separator between the number of vertices and the first edge. Similarly,
     there is  no separator between two edges. The last edge is immediately followed by '\n'.	 
	 The order of appearence of the edges is not important.
	
	As an example, the line below describes a graph composed of 4 vertices numbered from 0 to 3
	such that the vertex 0 is directly connected to the three other vertices and the vertex 1 is 
	also connected to the vertex 2. The attributes of the vertices 0 to 3 are respectively
    2.75, -8.0, 4.2 and -1.6.   	
 
    4{(2.75)(-8.0)(4.23)(-1.6)}(0,1)(0,2)(0,3)(1,2)

	
	The other example presented in the line below describes a graph composed of 4 vertices numbered 
	from 0 to 3 such that the vertex 0 is directly connected to the three other vertices and the 
	vertex 1 is also connected to the vertex 2. Each vertex has two attributes and the attributes of 
	the vertices 0 to 3 are respectively the pairs (2.75,-1.0)(-8.0,4.0)(4.23,-0.5) and (-1.6,2.5).
       	
 
    4{(2.75,-1.0)(-8.0,4.0)(4.23,-0.5)(-1.6,2.5)}(0,1)(0,2)(0,3)(1,2)

_________________________________________________________________________________________

[1] Mohammad Mourad Abdoulahi, Sylvain Iloga, "Flexible graph comparison using HMMs" (Under review).
