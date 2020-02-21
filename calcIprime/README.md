# Calc Iprime
Computing imbalance in phylogenetic tree

## description 

To do 

## Need 
gcc

## Compilation 
make clean
make

## what do
computed imbalance in phylogenetics tree using different estimators
## option 
* `-f` : files contains one or more tree in nexus format binaary : no bootstrap value or politonie : ((a:1,b:1):1, c:2);
* optional : 
 * `-p` simulation number to compute pvalue for I prime statistics, default : 1000
 * `-s` output [default : stdout] 
 * `-l` : Computed imbalance considering with limit of depth in tree [default : none]  
 * `-shao`  : computed shao statistics [default : None] 
 * `-mf` minimum of leaf of tree to analyse [default None]

## output :
header :
  * Num : tree position
  * LongeurTotal : length total in tree 
  * LongeurExterne : length of external branchs
  * LongeurInterne : length of internal branchs
  * Echantillon : sample number, or tips in tree 
  * TMRCA : tree height (mean between each tips and highest node) 
  * nbNoeudNonNUll : nombeur of node not null (node is considered null if < TMRCA/10000)
  * IprimeBin,NbNoeudIprimeBin, PVIpPurBin : statistics, node number where computed pvalue  and Pvalue computed with initial Iprime and binary nodes
  * IprimeNonBin2N      NbNoeudIprimeNonBin2N   PVIpPurNonBin2N : statisctics, node number where computed pvalue  and Pvalue computed with definition in (brandeburg et al) limiting to node with less than 2*k polytomie -1
  * IprimeNonBinKp1     NbNoeudIprimeNonBinKp1  PVIpPurNonBinKp1 :      statisctics, node number where computed pvalue  and Pvalue computed with definition in (brandeburg et al)
  * Other definition of Iprime (need to be devlopped) : IprimeNonBinPerm     NbNoeudIprimeNonBinPerm PVIpPurNonBinPerm       IprimePurvis    NbNoeudIprimePurvis     PVIpPurPurvis   IprimePurvisPerm        NbNoeudIprimePurvisPerm PVIpPurPurvisPerm
  * nbRepPvalue : repetition number used to computed of P-Value

## how to cite
*  for IprimeBin : to do do
* for  IprimePurvis : to do 
* for software, IprimeNonBin2N, IprimeNonBinKp1, IprimeNonBinPerm : Brandenburg JT, Austerlitz F, Toupance B. Impact of fertility transmission and other sociodemographic factors on reproductive success and coalescent trees. Genet Res (Camb). 2012;94(3):121–131. doi:10.1017/S0016672312000298
## how to test :
./CalcIPrimeV2.exe -f testdataset/arbre.tree

## what to do :
 * translate header
 * improve manuals
 * other options of compilation exist, of compilation must be explained 

