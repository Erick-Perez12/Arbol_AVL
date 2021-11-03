#include <iostream>
#include "avl.h"
using namespace std;

int main()
{
	AVL Arbol;
	Arbol.Insert(7);
	Arbol.Insert(3);
	Arbol.Insert(2);
	Arbol.Insert(10);
	Arbol.Insert(9);
	Arbol.Insert(6);
	Arbol.Insert(8);

	cout << "Altura de arbol " << Arbol.AlturaArbol() << endl;

	Arbol.Delete(8);
	Arbol.Delete(6);

	cout << "Altura de arbol " << Arbol.AlturaArbol() << endl;

	cout << "Valor menor: " << Arbol.Minimum();
	
	cin.get();
	return 0;
}