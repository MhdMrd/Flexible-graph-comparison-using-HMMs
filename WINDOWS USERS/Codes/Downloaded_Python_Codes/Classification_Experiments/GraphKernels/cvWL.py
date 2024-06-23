from __future__ import print_function
#print(__doc__)

import numpy as np

from grakel.datasets import fetch_dataset
from grakel.utils import cross_validate_Kfold_SVM

#from grakel.kernels import WeisfeilerLehman, VertexHistogram
#from grakel.kernels import WeisfeilerLehman, Propagation
#from grakel.kernels import WeisfeilerLehman, PyramidMatch
#from grakel.kernels import WeisfeilerLehman, ShortestPath
#from grakel.kernels import WeisfeilerLehman, NeighborhoodHash
#from grakel.kernels import WeisfeilerLehman, OddSth
#from grakel.kernels import WeisfeilerLehman, NeighborhoodSubgraphPairwiseDistance

DatasetName = "..."
X = fetch_dataset(DatasetName, verbose=True, download_if_missing=False)
G, y = X.data, X.target
Ks = list()

for i in range(1, 7):
#    gk = WeisfeilerLehman(n_iter=i, base_graph_kernel=VertexHistogram, normalize=True)
#    gk = WeisfeilerLehman(n_iter=i, base_graph_kernel=Propagation, normalize=True)
#    gk = WeisfeilerLehman(n_iter=i, base_graph_kernel=PyramidMatch, normalize=True)
#    gk = WeisfeilerLehman(n_iter=i, base_graph_kernel= ShortestPath, normalize=True)
#    gk = WeisfeilerLehman(n_iter=i, base_graph_kernel=NeighborhoodHash, normalize=True)
#    gk = WeisfeilerLehman(n_iter=i, base_graph_kernel=OddSth, normalize=True)
#    gk = WeisfeilerLehman(n_iter=i, base_graph_kernel=NeighborhoodSubgraphPairwiseDistance, normalize=True)
    K = gk.fit_transform(G)
    Ks.append(K)


# Performs 10-fold cross-validation over different kernels and the parameter C of
# SVM and repeats the experiment 10 times with different folds
accs = cross_validate_Kfold_SVM([Ks], y, n_iter=10)
print("Average accuracy:", str(round(np.mean(accs[0])*100, 2)) + "%")
print("Standard deviation:", str(round(np.std(accs[0])*100, 2)) + "%")
