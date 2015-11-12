//
//  main.cpp
//  AED_BinaryTree
//
//  Created by Alexander Arturo Baylon Ibanez on 6/10/15.
//  Copyright © 2015 Alexander Arturo Baylon Ibanez. All rights reserved.
//

#include "btree.cpp"

int main(int argc, const char * argv[]) {
    
    CbinTree<CListTrait<int>> arbol;

    cout << arbol.insert(12) << endl;
    cout << arbol.insert(19) << endl;
    cout << arbol.insert(15) << endl;
    cout << arbol.insert(6) << endl;
    cout << arbol.insert(31) << endl;
    cout << arbol.insert(4) << endl;
    cout << arbol.insert(7) << endl;
    cout << arbol.insert(8) << endl;
    cout << arbol.insert(55) << endl;
    cout << arbol.insert(10) << endl;
    cout << arbol.insert(20) << endl;
    cout << arbol.insert(1) << endl;
    
    CbinTree<CListTrait<int>>::iterador i;
    
    for (i=arbol.begin(); i!=arbol.end(); i++) {
        cout << "dato: " << *i << endl;
    }
    cout << "FIN" << endl;
    
    //arbol.printTree(arbol.m_root);
    //cout << endl;
    //cout << endl
    //cout << arbol.remove(15) << endl;
    //arbol.printTree(arbol.m_root);
    //cout << endl;
    //cout << arbol.remove(12) << endl;
    //arbol.printTree(arbol.m_root);
    //arbol.printTreeAmplitud(arbol.m_root);
    cout << endl;
    return 0;
    
}
