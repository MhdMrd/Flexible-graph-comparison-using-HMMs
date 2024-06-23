from __future__ import print_function
#print(__doc__)

import numpy as np

from grakel.datasets import fetch_dataset
from grakel.utils import cross_validate_Kfold_SVM

#from grakel.kernels import ShortestPathAttr
#from grakel.kernels import MultiscaleLaplacian
#from grakel.kernels import PropagationAttr
#from grakel.kernels import GraphHopper

DatasetName = "..."
X = fetch_dataset(DatasetName, prefer_attr_nodes=True, verbose=True, download_if_missing=False)
G, y = X.data, X.target
Ks = list()


#gk = ShortestPathAttr(normalize=True)
#gk = MultiscaleLaplacian(normalize=True)
#gk = PropagationAttr(normalize=True)
#gk = GraphHopper(normalize=True)

K = gk.fit_transform(G)
Ks.append(K)


# Performs 10-fold cross-validation over different kernels and the parameter C of
# SVM and repeats the experiment 10 times with different folds
accs = cross_validate_Kfold_SVM([Ks], y, n_iter=10)
print("Average accuracy:", str(round(np.mean(accs[0])*100, 2)) + "%")
print("Standard deviation:", str(round(np.std(accs[0])*100, 2)) + "%")
