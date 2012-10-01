#include <iostream>
#include <fstream>
using namespace std; 
class nodo{
      //atributos
      int key;
      int ele;
      nodo izquierdo;
      nodo derecho;
      //métodos
      nodo(int K, int E, nodo dere,nodo iz);
      int elemento();
      void setElemento(int elemento);
      int key();
      void setKey( int k);
      nodo izquierdo();
      void setIzqui(nodo I);
      nodo derecho();
      void setDere(nodo D);
      bool isLeaf();}

nodo::nodo(int K, int E, nodo dere, nodo iz){
             key=K;
             ele=E;
             izquierdo=iz;
             derecho=dere;}
int nodo::elemento(){return ele};

void nodo::setElemento(int elemento){ ele=elemento};

int nodo::key(){return key};

void nodo::setKey(int k){key=k};

nodo nodo::izquierdo(){return izquierdo};

void nodo::setIzqui(nodo I){izquierdo=I};

nodo nodo::derecho(){return derecho};

void nodo::setDere(nodo D){derecho=D};

bool nodo::isLeaf(){return(derecho=NULL&& izquierdo=NULL)};


      
