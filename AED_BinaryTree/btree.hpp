//
//  btree.hpp
//  AED_BinaryTree
//
//  Created by Alexander Arturo Baylon Ibanez on 6/10/15.
//  Copyright © 2015 Alexander Arturo Baylon Ibanez. All rights reserved.
//

#ifndef btree_hpp
#define btree_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//Trait
template <class T>
struct CListTrait{
    typedef  T U;
    typedef  less<T> C;
    typedef  greater<T> D;
};


// Nodo
template<class T>
class cNode{
public:
    T m_data;
    cNode<T> * m_child[2];
    cNode(){};
    cNode(T x){
        m_data = x;
        m_child[0] = m_child[1] = nullptr;
    }
    ~cNode(){};
};
//

template <class Tr>
class  CtreeIterator{
public:
    //el elemento principal es un stack
    //lleno de pares(nodo,estado)
    typedef pair<cNode<Tr>*,Tr> par;
    typedef stack<par>          pila;
    pila m_p;
    //constructor
    CtreeIterator(par p)
    {m_p = p;}
    CtreeIterator(){};
    
    //operaciones
    CtreeIterator<Tr> operator =(CtreeIterator<Tr> x)
    {
        m_p = x.m_p;
        return *this;}
    //operador !=
    bool operator != (CtreeIterator<Tr> x)
        {return m_p != x.m_p;}
    //Operador ++
    CtreeIterator<Tr> operator ++ (int){
        par * t = &m_p.top();
        //Mientras que no tengamos el siguiente elemento a mostrar
        while (t->second!=1) {
            switch (t->second) {
            //Caso 0: se va al hijo izquierdo
                case 0:
                    //ponemos el hijo izquierdo en la pila
                    //si es que hay uno
                    if (t->first->m_child[0]){
                        m_p.push(par(t->first->m_child[0],0));
                        t->second++; //cambiamos el estado
                        t = &m_p.top();} //actualizamos el temporal
                    else{//si no hay hijo izquierdo
                        t->second=1; //cambiamos el estado
                        t = &m_p.top(); //actualizamos el temporal
                    }
                    break;
            //Caso 2: se va al hijo derecho
                case 2:
                    if (t->first->m_child[1]) {
                        //ponemos el hijo derecho en la pila
                        m_p.push(par(t->first->m_child[1],0));
                        t->second=2; //cambiamos el estado
                        t = &m_p.top();} //actualizamos el temporal
                    else{//si no hay hijo derecho
                        t->second=3; //cambiamos el estado
                    }
                    break;
            //Caso 3: regresa al padre
                case 3:
                    //Si hay elementos en la pila
                    if (!m_p.empty()) {
                        m_p.pop(); //quitamos el elemento de la pila
                        if  (!m_p.empty()) {
                            t = &m_p.top();
                            if (t->second==0) m_p.top().second = 1;
                            if (t->second==2) m_p.top().second = 3;
                        }
                        break;
                    }
                    //Si la pila queda vacia
                    return *this;
                    break;
                default:
                    break;
            }
        }
        //Si tiene que irse al hijo derecho pero ya se imprimio
        if(t->first->m_child[1]) t->second=2;
        else t->second = 3;
        return *this;
    }
    Tr operator *(){
        //int temp = m_p.top().first->m_data;
        return m_p.top().first->m_data;
    }
    
    void print_stack()
    {
        cout << "m_p" << endl;
        pila temp = m_p;
        while (!temp.empty()) {
            cout << temp.top().first->m_data << " " << temp.top().second << endl;
            temp.pop();}
    }
};



//
template<class T>
cNode<T> ** rep(cNode<T> ** p)
{
    p = &((*p)->m_child[0]);
    while ((*p)->m_child[1])
        p = &((*p)->m_child[1]);
    cout << "contenido: " << (*p)->m_data << endl;
    return p;
}

//Arbol Binario
template <class Tr>
class CbinTree {
private:
    typedef typename Tr::U T;//tipo de dato
    //comparaciones
    typedef typename Tr::C C;
    typedef typename Tr::D D;
    
public:
    //iterador y stack
    typedef pair<cNode<T>*,T> par;
    typedef stack<par> pila;
    typedef CtreeIterator<T> iterador;
    cNode<T> *  m_root;
    //instanciamos una funcion less
    less<T>     m_cmp;
    //instanciamos un iterador
    iterador i;
    iterador j;
    CbinTree(){m_root=nullptr;}
    bool find(T,cNode<T>**&);
    bool insert(T);
    bool remove(T);
    void printTree(cNode<T>*);
    void printTreeAmplitud(cNode<T>*);
    void printTreeProfunidad(cNode<T>*);
    //nos retorna un stack con el camino hacia el primer nodo
    iterador begin()
    {
        pila first;
        cNode<T> * p;
        for (p = m_root; p->m_child[0]!=nullptr; p=p->m_child[0]){
            first.push(par(p,0));}
        //como el ultimo elemento se va a imprimir sin condiciones, entonces
        //es estado 3
        first.push(par(p,3));
        i.m_p=first;
        return i;
    }
    //nos retorna un iterador vacio
    iterador end() {return j;}
    ~CbinTree(){};
};


//
template<class Tr>
bool CbinTree<Tr>::find(T x, cNode<T> **& p){
    for (p=&m_root; (*p) && (*p)->m_data!=x; p=&( (*p)->m_child[m_cmp((*p)->m_data,x)]));
    return (*p);
}

//
template<class Tr>
bool CbinTree<Tr>::insert(T x){
    cNode<T> ** p;
    if (find(x, p)) return 0;
    *p = new cNode<T>(x);
    return 1;
}

//
template<class Tr>
bool CbinTree<Tr>::remove(T x){
    cNode<T> ** p;
    if (!find(x, p)) return 0;
    // Caso 2:tiene 2 hijos
    if ((*p)->m_child[0] && (*p)->m_child[1]) {
        cNode<T> ** q = rep<T>(p);
        (*p)->m_data = (*q)->m_data;
        p = q;
    }
    cNode<T> * t = *p;
    // Caso 1:tiene 1 hijo
    *p = (*p)->m_child[(*p)->m_child[1]!=0];
    delete t;
    return 1;
}

//imprimir arbol en inorden
template<class Tr>
void CbinTree<Tr>::printTree(cNode<T> * p)
{
    if (p != nullptr) {
        printTree(p->m_child[0]);
        cout << p->m_data << " ";
        printTree(p->m_child[1]);
    }
}

//imprimir arbol por amplitud
template<class Tr>
void CbinTree<Tr>::printTreeAmplitud(cNode<T> * p)
{
    //vector se asemeja a una cola
    vector<cNode<T>*> l;
    l.push_back(p);
    while (!l.empty()) {
        cNode<T> * t = l.front();
        l.erase(l.begin());
        cout << t->m_data <<" ";
        if(t->m_child[0]) l.push_back(t->m_child[0]);
        if(t->m_child[1]) l.push_back(t->m_child[1]);
    }
    
}

//imprimir arbol por profundidad
//NO FUNCIONA
template<class Tr>
void CbinTree<Tr>::printTreeProfunidad(cNode<T> * r)
{
    cNode<T> * t = r;
    vector<cNode<T>*> l;
    while (t->m_child[0]) {
        l.push_back(t->m_child[0]);
        t = t->m_child[0];
    }
    while (!l.empty()) {
        t = l.front();
    }
}

#endif /* btree_hpp */
