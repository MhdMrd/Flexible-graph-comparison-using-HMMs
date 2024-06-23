Our codes are written in C language and are tested in the MS Windows 10 environment.

The execution of these C codes produces several text files named "Output..." containing relevant 
information, including the Markov chains (MCs) derived by the method proposed in [1]. 
In these text files:

1- The Markov chains are represented as ORDERED sequences of pairs (e,s) such that each pair (e,s) 
   materializes the fact that the symbol (s) is observed from the state (e). These Markov chains are
   generated during the traversal of a graph by the Depth-First-Search algorithm. Each state is the
   depth of the currently visited vertex and each symbol is the value of a user-defined property for
   the visited vertex/edge. 

   The two lines below show examples of such Markov chains. Each line starts by the indentifier of 
   the vertex from which the Depth-First-Search algorithm started in order to generate the Markov chain.

   1:	(0,0)(1,1)(2,1)(2,0)
   2:	(0,1)(1,1)(2,0)(2,1)


2- Each Markov chain can be followed by an ORDERED list of vertex identifiers, each identifier
   being enclosed into brackets. These are the vertices visited by the Depth-First-Search algorithm 
   in order to derive the corresponding Markov chain.

   The two lines below show examples of such Markov chains. Each line starts by the indentifier of the vertex from which the
   Depth-First-Search algorithm started in order to generate the Markov chain. The ordered list of vertices
   visited by the Depth-First-Search algorithm in order to derive the corresponding Markov chain 
   appears after "****".

   1:	(0,0)(1,1)(2,1)(2,0)    ****   (1)(5)(3)(4)
   2:	(0,1)(1,1)(2,0)(2,1)    ****   (2)(3)(4)(5)
_________________________________________________________________________________________

[1] Mohammad Mourad Abdoulahi, Sylvain Iloga, "Flexible graph comparison using HMMs" (Under review).
