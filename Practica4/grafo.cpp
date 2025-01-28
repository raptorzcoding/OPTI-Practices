 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos   : 2012-2021
 */

#include "grafo.h"
#include <iostream>

void GRAFO::destroy()
{
	for (unsigned i=0; i< n; i++)
    {
		LS[i].clear();
		A[i].clear();
		if (dirigido == 1)
        {
            LP[i].clear();
        };
	}
	LS.clear();
	LP.clear();
	A.clear();

}



void GRAFO::build(char nombrefichero[85], int &errorapertura)
{
  ElementoLista dummy;
  ifstream textfile;
  textfile.open(nombrefichero);
  if(textfile.is_open()) {
    unsigned i, j, k;
    // leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
    textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
    // los nodos internamente se numeran desde 0 a n-1
    // creamos las n listas de sucesores
    A.resize(n);
    LS.resize(n);
    if(dirigido == 1)
      LP.resize(n); // Si tenemos n nodos, la primera dimensión de LS y LP debe tener n espacios
          // leemos los m arcos
    for (k = 0; k < m; k++) {
      textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
      //damos los valores a dummy.j y dummy.c
      //situamos en la posicion del nodo i a dummy mediante push_backM
      //pendiente de hacer un segundo push_back si es no dirigido. O no.
      //pendiente la construccion de LP, si es dirigido
      //pendiente del valor a devolver en errorapertura
      dummy.j = j - 1; // resto a j una unidad, para tener el nodo 1, en la posición cero, el 2 en la 1, etc...

      if(dirigido == 0) // Si es no dirigido, solo tenemos que trabajar con LS
      {
        LS[i-1].push_back(dummy); // Colocamos en la fila del nodo que corresponda en LS, el nodo al que apunta, y el coste del camino
        dummy.j = i - 1; // Asignamos el valor del nodo predecesor
        if((i-1) != (j-1)) {
          LS[j-1].push_back(dummy); // Colocamos en la fila del nodo que corresponda en LS, el nodo que le precede, y el coste del camino
          // Como es un grafo no dirigido, se ponen todos los datos en LS pero reflejados con la diagonal principal
        }
      }
      if(dirigido == 1) // No pongo un else, por si hay acaso, dirigido != 0 y dirigido !=1
      {
        LS[i-1].push_back(dummy); // Colocamos en la fila del nodo que corresponda en LS, el nodo al que apunta, y el coste del camino
        dummy.j = i - 1; // Asignamos el valor del nodo predecesor
        LP[j-1].push_back(dummy); // Colocamos en la fila del nodo que corresponda en LP, el nodo que le precede, y el coste del camino
        // Como es un grafo dirigido, usamos LP para colocar este dato
        
      }
    }
  }
  textfile.close();
}  


GRAFO::~GRAFO()
{
    destroy(); // Llamar al método destroy para liberar memoria, suponiendo que destroy() esté definido correctamente
}



GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
	build (nombrefichero, errorapertura);
}



void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
{
    //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
    destroy();
    //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
    build(nombrefichero, errorapertura);
}



unsigned GRAFO::Es_dirigido()
{
return dirigido;
}



void GRAFO::Info_Grafo()
{
    cout << endl << "El Grafo cargado actualmente tiene las siguiente caracteristicas:" << endl;
    cout << "Numero de Nodos (n): " << n << endl;
    cout << "Numero de Arcos (m): " << m << endl;
    cout << "Es dirigido? " << (dirigido != 1 ? " No" : " Si");
    cout << endl << endl;
}



void Mostrar_Lista(vector<LA_nodo> L)
{
    unsigned nodos = L.size();
    for(int i = 0; i < nodos; i++) {
        cout << "[Nodo: " << i + 1 << "]";
        
        if(L[i].size() == 0) {
            cout << " :  Vacio" << endl;
            continue; // Saltar al siguiente nodo si la lista está vacía
        }
        
        for(int k = 0; k < L[i].size(); k++) {
            cout << " :  " << L[i][k].j + 1 << "(Coste: " << L[i][k].c << ") ";
        }
        cout << endl;
    }
    cout << endl;
}




void GRAFO :: Mostrar_Listas (int l)
{
    if(l == 1 || l == 0)
        Mostrar_Lista(LS); // Para Grafos Dirigidos y No Dirigidos   
    if(l == -1)
        Mostrar_Lista(LP); // Para Grafos Dirigidos
}



void GRAFO::Mostrar_Matriz() 
{
vector<LA_nodo> L; //lista que recorremos, LS o LP; por defecto LS  
cout << L[0][0].j << std::endl;
}


void GRAFO::dfs_num(unsigned i, //nodo desde el que realizamos el recorrido en profundidad
 vector<LA_nodo> L, //lista que recorremos, LS o LP; por defecto LS
 vector<bool> &visitado, //vector que informa de si un nodo ha sido visitado
 vector<unsigned> &prenum, //almacenamos en la posición i el preorden del nodo i+1
 unsigned &prenum_ind, //contador del preorden
 vector<unsigned> &postnum, //almacenamos en la posición i el postorden del nodo i+1
 unsigned &postnum_ind) //contador del postorden
 //Recorrido en profundidad recursivo con recorridos enum y postnum
{
visitado[i] = true; //visitamos el nodo i+1
prenum[prenum_ind++]=i;//asignamos el orden de visita prenum que corresponde el nodo i+1
 for (unsigned j=0;j<L[i].size();j++) //recorremos la adyacencia del nodo visitado, esto es, i+1
 if (!visitado[L[i][j].j])
 {
 dfs_num(L[i][j].j, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
 };
postnum[postnum_ind++]=i;//asignamos el postorden de visita que corresponde al nodo i+1 al regreso
}

void GRAFO::RecorridoProfundidad()
{
    // Creación e inicialización de variables y vectores
    unsigned prenum_ind = 0;
    unsigned postnum_ind = 0;
    vector<unsigned> prenum(n, 0);
    vector<unsigned> postnum(n, 0);
    vector<bool> visitado(n, false);

    // Solicitud al usuario del nodo inicial del recorrido en profundidad
    unsigned i;
    cout << "Elije nodo de partida? [1-" << n << "]: ";
    cin >> i;
    i--; // Restamos 1 porque los índices en C++ comienzan en 0

    // Realizamos el recorrido en profundidad
    if (!visitado[i]) {
        dfs_num(i, LS, visitado, prenum, prenum_ind, postnum, postnum_ind);
    }

    // Mostrar en pantalla el preorden
    cout << "Orden de visita de los nodos en preorden\n";
    for (unsigned i = 0; i < prenum_ind; i++) {
      cout << "[" << prenum[i] + 1 << "]";
      if (i < prenum_ind - 1) {
        cout << " -> ";
      }
    }
    cout << "\n";

    // Mostrar en pantalla el postorden
    cout << "Orden de visita de los nodos en postorden\n";
    for (unsigned i = 0; i < postnum_ind; i++) {
      cout << "[" << postnum[i] + 1 << "]";
      if (i < postnum_ind - 1) {
        cout << " -> ";
      }
    }
    cout << "\n";
}



 void GRAFO::bfs_num(	unsigned i, //nodo desde el que realizamos el recorrido en amplitud
				vector<LA_nodo>  L, //lista que recorremos, LS o LP; por defecto LS
				vector<unsigned> &pred, //vector de predecesores en el recorrido
				vector<unsigned> &d) //vector de distancias a nodo i+1
//Recorrido en amplitud con la construccion de pred y d: usamos la cola
{
  vector<bool> visitado; //creamos e iniciamos el vector visitado
  visitado.resize(n, false);
  visitado[i] = true;

  pred.resize(n, 0); //creamos e inicializamos pred y d
  d.resize(n, 0);
  pred[i] = i;
  d[i] = 0;

  queue<unsigned> cola; //creamos e inicializamos la cola
  cola.push(i);//iniciamos el recorrido desde el nodo i+1

  while (!cola.empty()) { //al menos entra una vez al visitar el nodo i+1 y continua hasta que la cola se vacie
   unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
    cola.pop(); //lo sacamos de la cola
    //Hacemos el recorrido sobre L desde el nodo k+1
      for (unsigned j = 0; j < L[k].size(); j++) {
      //Recorremos todos los nodos u adyacentes al nodo k+1
      //Si el nodo u no esta visitado
				if (!visitado[L[k][j].j]) {
					//Lo visitamos
					visitado[L[k][j].j] = true;
					//Lo metemos en la cola
					cola.push(L[k][j].j);
					//le asignamos el predecesor
					pred[L[k][j].j] = k;
					//le calculamos su etiqueta distancia
					d[L[k][j].j] = d[k] + 1;
      	} 
      }
        //Hemos terminado pues la cola esta vacia
    }
}

void GRAFO::RecorridoAmplitud() { //Construye un recorrido en amplitud desde un nodo inicial 

  unsigned i = 0;
	vector<unsigned> pred(n, UERROR);
	vector<unsigned> d(n, maxint);

  cout << "\nElige el nodo inicial en el rango (1, " << n << ")" << endl;
  cin >> (unsigned &) i;

	while (i < 1 || i > n) {
		cout << "El nodo introducido no es valido. Introduzca un nodo en el rango (1, " << n << ")" << endl;
		cin >> (unsigned &) i;
	}
    
  bfs_num(i - 1, LS, pred, d);
	cout << "Nodos segun distancia al nodo inicial en numero de aristas" << endl;
	for (unsigned dist = 0; dist < n ; dist++) {
		bool distanciaVacia = true; // Variable para verificar si la distancia está vacía
		for (unsigned nodo = 0; nodo < n; nodo++) {
			if (d[nodo] == dist) {
				if (distanciaVacia) {
					cout << "Distancia de " << dist << " aristas: ";
					distanciaVacia = false; // La distancia no está vacía
				}
				cout << nodo + 1 << " ";
			}
		}
		if (!distanciaVacia) {
			cout << endl;
		}
	}

	cout << "Ramas de conexiones:" << endl;
	for (unsigned i = 1; i < pred.size(); i++) {
		if (pred[i] != UERROR) {
			vector<unsigned> ramas;
			unsigned nodo_actual = i;
			while (nodo_actual != pred[nodo_actual]) {
				ramas.push_back(nodo_actual + 1);
				nodo_actual = pred[nodo_actual];
			}
			ramas.push_back(nodo_actual + 1);
			for (int j = ramas.size() - 1; j >= 0; j--) {
				cout << ramas[j];
				if (j != 0) {
					cout << " -> ";
				}
			}
			cout << endl;
		}
	}
	cout << endl;
}

void GRAFO::Kruskal() {
  vector <AristaPesada> Aristas;
  //Cargamos todas las aristas de la lista de adyacencia en el vector Aristas
  Aristas.resize(m);
  unsigned k = 0;
  for (unsigned i = 0; i < n; i++) // n es el número de nodos
  {
    for (unsigned j=0; j<LS[i].size();j++) // LS[i].size() es el número de aristas que salen del nodo i
    {
      if (i < LS[i][j].j) // Si el nodo origen es menor que el nodo destino, entonces metemos la arista en el vector Aristas 
      {
        Aristas[k].extremo1 = i; 
        Aristas[k].extremo2 = LS[i][j].j; 
        Aristas[k++].peso = LS[i][j].c; 
      }
    }
  };

  unsigned head = 0;
  unsigned cont = 0;
  int pesoMST = 0;
  
  vector <unsigned> Raiz;
  Raiz.resize(n);
  for (unsigned f = 0; f < n; f++) {
    Raiz[f] = f;
  };

  AristaPesada AristaTemp; // La usamos para hacer los intercambios de aristas en el vector Aristas.

do {
        // Ponemos en la posición del vector Aristas head la arista con menor peso
        // Para ello recorremos las aristas desde la posición head+1 hasta la m-1 intercambiando la de menor coste
        // con la que está en la posición head, salvo que head ya apunte a la última arista (la de la posición m-1)
        if (head < n - 1) {
          for (unsigned i = head + 1; i < m; i++) {
            // Si el peso de la arista en la posición head es > que el peso de la arista en la posición i, entonces
            // intercambiamos Aristas[i] con Aristas[head]
            if (Aristas[i].peso > Aristas[head].peso) {
            AristaTemp = Aristas[head];
            Aristas[head] = Aristas[i];
            Aristas[i] = AristaTemp;
            };
          };
        };
        // Miramos si los extremos de la arista en la posición head están en componentes conexas distintas, y si es así, metemos esa arista en el
        // MST y unimos las componentes conexas, es decir, unificando etiquetas
        if (Raiz[Aristas[head].extremo1] != Raiz[Aristas[head].extremo2]) {
          unsigned kill = Raiz[Aristas[head].extremo1]; // kill = Raiz[Aristas[head].extremo1];
          for (unsigned k = 0; k < n-1; k++) { // para todo nodo k desde 0 hasta n-1, hacer
            if (Raiz[k] == kill) { //    si raiz[k] == kill entonces raiz[k] = Raiz[Aristas[head].extremo2];
              Raiz[k] = Raiz[Aristas[head].extremo2];
            };
          };
          // Incrementar el contador de aristas en el MST
          cont++;
          // Mostramos la arista incorporada al MST
          cout << "Arista numero " << cont << " incorporada (" << (Aristas[head].extremo1) + 1 << ", " << (Aristas[head].extremo2) + 1 << "), con coste " << Aristas[head].peso << endl;
          // Actualizamos el peso del MST
          pesoMST = pesoMST + Aristas[head].peso;
        };

        // Pasamos a la siguiente arista
        head++; 

        } while ((cont < (n - 1)) && (head < m));

        if (cont == (n - 1)){
            cout << "El coste del arbol generador de minimo coste es " << pesoMST << endl; 
            cout << endl;
        }
        else {
            cout << "El grafo no es conexo, por lo tanto no hay arbol generador de minimo coste" << endl;
            cout << endl;
        };
}










