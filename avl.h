#pragma once
#include <iostream>
#ifndef AVL_tree
#define AVL_tree
using namespace std;
class AVL;

class Nodo {
public:
    Nodo(const int dat, Nodo* pad = NULL, Nodo* izq = NULL, Nodo* der = NULL) :
        dato(dat), padre(pad), izquierdo(izq), derecho(der), FE(0) {}
    int dato;
    int FE;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo* padre;
    friend class AVL;
};

class AVL {
private:
    enum { IZQUIERDO, DERECHO };
    Nodo* raiz;
    Nodo* actual;
    int contador;
    int altura;

public:
    AVL() : raiz(NULL), actual(NULL) {}
    ~AVL() { Podar(raiz); }
    void Insert(const int dat);
    void Delete(const int dat);
    bool Search(const int dat);
    bool Vacio(Nodo* r) { return r == NULL; }
    bool EsHoja(Nodo* r) { return !r->derecho && !r->izquierdo; }
    const int NumeroNodos();
    const int AlturaArbol();
    int Altura(const int dat);
    int& ValorActual() { return actual->dato; }
    void Raiz() { actual = raiz; }
    int Minimum();

private:
    void Equilibrar(Nodo* nodo, int, bool);
    void leftRotate(Nodo* nodo);
    void rightRotate(Nodo* nodo);
    void leftRotateDouble(Nodo* nodo);
    void rightRotateDouble(Nodo* nodo);
    void Podar(Nodo*&);
    void auxContador(Nodo*);
    void auxAltura(Nodo*, int);
 
};

void AVL::Podar(Nodo*& nodo)
{
    if (nodo) {
        Podar(nodo->izquierdo); 
        Podar(nodo->derecho);   
        delete nodo;            
        nodo = NULL;
    }
}

void AVL::Insert(const int dat)
{
    Nodo* padre = NULL;

    cout << "Insert: " << dat << endl;
    actual = raiz;
    while (!Vacio(actual) && dat != actual->dato) {
        padre = actual;
        if (dat > actual->dato) actual = actual->derecho;
        else if (dat < actual->dato) actual = actual->izquierdo;
    }
    if (!Vacio(actual)) return;
    if (Vacio(padre)) raiz = new Nodo(dat);
    else if (dat < padre->dato) {
        padre->izquierdo = new Nodo(dat, padre);
        Equilibrar(padre, IZQUIERDO, true);
    }
    else if (dat > padre->dato) {
        padre->derecho = new Nodo(dat, padre);
        Equilibrar(padre, DERECHO, true);
    }
}

void AVL::Equilibrar(Nodo* nodo, int rama, bool nuevo)
{
    bool salir = false;

    while (nodo && !salir) {
        if (nuevo)
            if (rama == IZQUIERDO) nodo->FE--; 
            else                  nodo->FE++;
        else
            if (rama == IZQUIERDO) nodo->FE++;
            else                  nodo->FE--;
        if (nodo->FE == 0) salir = true;

        else if (nodo->FE == -2) { 
            if (nodo->izquierdo->FE == 1) rightRotateDouble(nodo); 
            else rightRotate(nodo);                        
            salir = true;
        }
        else if (nodo->FE == 2) {  
            if (nodo->derecho->FE == -1) leftRotateDouble(nodo); 
            else leftRotate(nodo);                      
            salir = true;
        }
        if (nodo->padre)
            if (nodo->padre->derecho == nodo) rama = DERECHO; else rama = IZQUIERDO;
        nodo = nodo->padre; 
    }
}

void AVL::rightRotateDouble(Nodo* nodo)
{
    cout << "rightRotateDouble" << endl;
    Nodo* Padre = nodo->padre;
    Nodo* P = nodo;
    Nodo* Q = P->izquierdo;
    Nodo* R = Q->derecho;
    Nodo* B = R->izquierdo;
    Nodo* C = R->derecho;

    if (Padre)
        if (Padre->derecho == nodo) Padre->derecho = R;
        else Padre->izquierdo = R;
    else raiz = R;

    Q->derecho = B;
    P->izquierdo = C;
    R->izquierdo = Q;
    R->derecho = P;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = Q;
    if (C) C->padre = P;

    switch (R->FE) {
    case -1: Q->FE = 0; P->FE = 1; break;
    case 0:  Q->FE = 0; P->FE = 0; break;
    case 1:  Q->FE = -1; P->FE = 0; break;
    }
    R->FE = 0;
}

void AVL::leftRotateDouble(Nodo* nodo)
{
    cout << "leftRotateDouble" << endl;
    Nodo* Padre = nodo->padre;
    Nodo* P = nodo;
    Nodo* Q = P->derecho;
    Nodo* R = Q->izquierdo;
    Nodo* B = R->izquierdo;
    Nodo* C = R->derecho;

    if (Padre)
        if (Padre->derecho == nodo) Padre->derecho = R;
        else Padre->izquierdo = R;
    else raiz = R;

    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;
    if (C) C->padre = Q;

    switch (R->FE) {
    case -1: P->FE = 0; Q->FE = 1; break;
    case 0:  P->FE = 0; Q->FE = 0; break;
    case 1:  P->FE = -1; Q->FE = 0; break;
    }
    R->FE = 0;
}

void AVL::rightRotate(Nodo* nodo)
{
    cout << "rightRotate" << endl;
    Nodo* Padre = nodo->padre;
    Nodo* P = nodo;
    Nodo* Q = P->izquierdo;
    Nodo* B = Q->derecho;

    if (Padre)
        if (Padre->derecho == P) Padre->derecho = Q;
        else Padre->izquierdo = Q;
    else raiz = Q;

    P->izquierdo = B;
    Q->derecho = P;

    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void AVL::leftRotate(Nodo* nodo)
{
    cout << "leftRotate" << endl;
    Nodo* Padre = nodo->padre;
    Nodo* P = nodo;
    Nodo* Q = P->derecho;
    Nodo* B = Q->izquierdo;

    if (Padre)
        if (Padre->derecho == P) Padre->derecho = Q;
        else Padre->izquierdo = Q;
    else raiz = Q;

    P->derecho = B;
    Q->izquierdo = P;

    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void AVL::Delete(const int dat)
{
    Nodo* padre = NULL;
    Nodo* nodo;
    int aux;

    actual = raiz;
    while (!Vacio(actual)) {
        if (dat == actual->dato) { 
            if (EsHoja(actual)) { 
                if (padre) 
                    if (padre->derecho == actual) padre->derecho = NULL;
                    else if (padre->izquierdo == actual) padre->izquierdo = NULL;
                delete actual; 
                actual = NULL;
            
                if ((padre->derecho == actual && padre->FE == 1) ||
                    (padre->izquierdo == actual && padre->FE == -1)) {
                    padre->FE = 0;
                    actual = padre;
                    padre = actual->padre;
                }
                if (padre)
                    if (padre->derecho == actual) Equilibrar(padre, DERECHO, false);
                    else                         Equilibrar(padre, IZQUIERDO, false);
                return;
            }
            else { 
                padre = actual;
        
                if (actual->derecho) {
                    nodo = actual->derecho;
                    while (nodo->izquierdo) {
                        padre = nodo;
                        nodo = nodo->izquierdo;
                    }
                }
                else {
                    nodo = actual->izquierdo;
                    while (nodo->derecho) {
                        padre = nodo;
                        nodo = nodo->derecho;
                    }
                }
                aux = actual->dato;
                actual->dato = nodo->dato;
                nodo->dato = aux;
                actual = nodo;
            }
        }
        else { 
            padre = actual;
            if (dat > actual->dato) actual = actual->derecho;
            else if (dat < actual->dato) actual = actual->izquierdo;
        }
    }
}

bool AVL::Search(const int dat)
{
    actual = raiz;

    while (!Vacio(actual)) {
        if (dat == actual->dato) return true;
        else if (dat > actual->dato) actual = actual->derecho;
        else if (dat < actual->dato) actual = actual->izquierdo;
    }
    return false; 
}

int AVL::Minimum() {
    actual = raiz;
    int tmp;
    while (!Vacio(actual)) {
        actual = actual->izquierdo;
        tmp = actual->dato;
        return tmp;
    }
}

int AVL::Altura(const int dat)
{
    int altura = 0;
    actual = raiz;

    while (!Vacio(actual)) {
        if (dat == actual->dato) return altura; 
        else {
            altura++; 
            if (dat > actual->dato) actual = actual->derecho;
            else if (dat < actual->dato) actual = actual->izquierdo;
        }
    }
    return -1; 
}

const int AVL::NumeroNodos()
{
    contador = 0;

    auxContador(raiz); 
    return contador;
}
void AVL::auxContador(Nodo* nodo)
{
    contador++;  
    if (nodo->izquierdo) auxContador(nodo->izquierdo);
    if (nodo->derecho)   auxContador(nodo->derecho);
}


const int AVL::AlturaArbol()
{
    altura = 0;
    auxAltura(raiz, 0); 
    return altura;
}

void AVL::auxAltura(Nodo* nodo, int a)
{

    if (nodo->izquierdo) auxAltura(nodo->izquierdo, a + 1);
    if (nodo->derecho)   auxAltura(nodo->derecho, a + 1);
    if (EsHoja(nodo) && a > altura) altura = a;
}

void Mostrar(int& d, int FE)
{
    cout << d << "(" << FE << "),";
}

#endif