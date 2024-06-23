from __future__ import print_function
#print(__doc__)

import numpy as np

from grakel.datasets import fetch_dataset
from grakel.utils import cross_validate_Kfold_SVM

#from grakel.kernels import VertexHistogram
#from grakel.kernels import Propagation
#from grakel.kernels import PyramidMatch
#from grakel.kernels import ShortestPath
#from grakel.kernels import NeighborhoodHash
#from grakel.kernels import OddSth
#from grakel.kernels import NeighborhoodSubgraphPairwiseDistance
#from grakel.kernels import SubgraphMatching

DatasetName = "..."
X = fetch_dataset(DatasetName, verbose=True, download_if_missing=False)
G, y = X.data, X.target
Ks = list()

#gk = VertexHistogram(normalize=True)
#gk = Propagation(normalize=True)
#gk = PyramidMatch(normalize=True)
#gk = ShortestPath(with_labels=False, normalize=True)
#gk = ShortestPath(with_labels=True, normalize=True)
#gk = NeighborhoodHash(normalize=True)
#gk = OddSth(normalize=True)
#gk = NeighborhoodSubgraphPairwiseDistance(normalize=True)
#gk = SubgraphMatching(normalize=True)


K = gk.fit_transform(G)
Ks.append(K)


# Performs 10-fold cross-validation over different kernels and the parameter C of
# SVM and repeats the experiment 10 times with different folds
accs = cross_validate_Kfold_SVM([Ks], y, n_iter=10)
print("Average accuracy:", str(round(np.mean(accs[0])*100, 2)) + "%")
print("Standard deviation:", str(round(np.std(accs[0])*100, 2)) + "%")
