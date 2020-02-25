import re
import sys


def scale_newick(FileNewick,FileNewickOut ,tmrca):
    Read = open(FileNewick, 'r')
    tree= Read.Readlines()
    Read.close
    Write = open(FileNewickOut, 'w')
    tree_split = []
    nou_tab_tree = []
    for i in tree:
        j=0;
        nouv_tree =""
        while j < len(i):
            if(i[j]==':'):
                j+=1
                nombre = ""
                while(i[j]!=';' and i[j]!=')' and i[j]!=','):
                    nombre+=i[j]
                    j+=1
                nouv_tree+= ':'+ str(float(int(nombre))/float(2*nb_gene))
            nouv_tree+=i[j]
            j+=1
        nou_tab_tree.append(nouv_tree)
    for i in nou_tab_tree:
        Write.write(i)
    Write.close()

if len(sys.argv)!=4 :
   print('Description : read a newick file and rescale length in function of scale\ncommand line exe FileNewickIn FileNewickOut scale')    
   sys.exit(1)

reformat_newick(sys.argv[1],sys.argv[2],tmrca)



