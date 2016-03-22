# 865datamining

This is the project of CPSC 8650 data mining. The project is implementation of SH algorithm.


Right now: Change LSH from RNN to KNN. Finish compare script. Generated dataset from mnist.

Furture work: Change the main function in LSHmain.cpp. Generate H-R radius search in LSH, then query each points to find the r', which r'-NN > const * K. Then insert all points with their r'. Change the query part in LSHmain.cpp a little to adjust the new data structure. 
nnstruce[i].



After testing, the 6w dataset is not suit larger than 0.62 radius searching. So may use the 1000 dataset. The running time of linear searching for 6w is 60 times by the 1000.  

I will just use the LSH datastructure, with different radius m, l, p. 

Higher P may cause m, L change. Normal they change larger, but they may change smaller rarely.
R must cause k, m, L change larger. The L may change sharply, and that cause the running time slow down sharply.
