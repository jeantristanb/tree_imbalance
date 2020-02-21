# Calc Iprime
Computing imbalance in phylogenetic tree

## Need 
gcc

## Compilation 
make clean
make

## what do
computed imbalance in phylogenetics tree using different estimators
## option 
* `-f` : files contains one or more tree in nexus format 
* optional : 
 * `-p` simulation number to compute pvalue for I prime statistics, default : 1000
 * `-s` output [default : stdout] 
 * `-l` : limits of node number in tree to computed values default : none]  
 * `-shao`  : computed shao statistics [default : None] 
 * ` -mf` minimum of leaf of tree to analyse [default None]
`
## output :
header :
 * To do
## how to cited

TODO

## how to test :
./CalcIPrimeV2.exe -f testdataset/arbre.tree

## what to do :
 * translate header
 * improve manuals
 * other options of compilation exist, of compilation must be explained 

