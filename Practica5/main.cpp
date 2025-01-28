 /*
 *  Programa principal.
 *
 *
 *               Autores : Antonio Sedeno Noda, Sergio Alonso.
 *               Cursos  : 2012-2021
 */

#include <string.h>
#include "grafo.h"
#include <cstdlib> // Para la función system() que permite limpiar la pantalla
#include <conio.h> // Para la función getch() que permite esperar a que el usuario presione una tecla


void clrscr() { 
    system("cls"); // Limpia la pantalla
}



void pressanykey() {
    // Espera a que el usuario presione una tecla
    system("pause");
    std::cout << "Presiona cualquier tecla para continuar...";
    std::cin.get();
}



void menu (unsigned dirigido, char &opcion)
//Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
{
    cout << "Optimizacion en Grafos, 2023-2024 PABLO GARCIA DE LOS REYES" << endl;
    cout << "c. [c]argar grafo desde fichero" << endl;
    if (dirigido == 0) //Grafo no dirigido
            {
            cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
            cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
            cout << "y. Mostrar la matriz de ad[y]acencia del grafo" << endl;
            cout << "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo" << endl;
            cout << "r  Realizar un recorrido en p[r]ofundidad del grafo desde un nodo" << endl;
            cout << "k  Realizar el arbol generador de mínimo coste, [k]ruskal" << endl;
            }
    else // Grafo dirigido
            {
            cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
            cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
            cout << "e. Mostrar la lista de pr[e]decesores del grafo" << endl;
            cout << "y. Mostrar la matriz de ad[y]acencia del grafo" << endl;
            cout << "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo por sucesores" << endl;
            cout << "r. Realizar un recorrido en p[r]ofundidad del grafo desde un nodo por sucesores" << endl;
            cout << "p. Determinar los caminos mínimos de un nodo al resto" << endl;
            };
    cout << "q. Finalizar el programa" << endl;
    cout << "Introduce la letra de la accion a ejecutar  > ";
    cin >> opcion;
};


// El principal es simplemente un gestor de menu, diferenciando acciones para dirigido y para no dirigido, y un men� inicial si no hay un grafo cargado
int main(int argc, char *argv[])
{
    int error_apertura;
    char nombrefichero[85], opcion;

    //Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos cargar, si no, lo pedimos desde teclado
    if (argc > 1)
    {
	cout << "Cargando datos desde el fichero dado como argumento" << endl;
        strcpy(nombrefichero, argv[1]);
    }
    else
    {
        cout << "Introduce el nombre completo del fichero de datos" << endl;
        cin >> nombrefichero;
    };
    GRAFO G(nombrefichero, error_apertura);
    if (error_apertura == 1)
    {
        cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
        pressanykey();
        clrscr();
    }
    else
    {
        cout<< "Grafo cargado desde el fichero " << nombrefichero << endl;
        pressanykey();
        clrscr();
        do
        {
            menu(G.Es_dirigido(), opcion);
            switch (opcion)
            {
                case 'c' :
                    clrscr();
         	        cout << "Introduce el nombre completo del fichero de datos" << endl;
                    cin >> nombrefichero;
                    G.actualizar(nombrefichero, error_apertura);
                    if (error_apertura == 1)
                    {
                        cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
                    }
                    else
                    {
                        cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
                    };
                    pressanykey();
                    clrscr();
                    break;

                case 'i': // i(nformación) básica del grafo
                    clrscr();
                    cout << "Grafo cargado desde " << nombrefichero << endl;
                    G.Info_Grafo();
                    pressanykey();
                    clrscr();
                    break;
                
                case 's': // Mostrar lista de sucesores del grafo
                    clrscr();
                    cout << "La lista de sucesores del grafo " << nombrefichero;
                    cout << " es:" << endl << endl;
                    G.Mostrar_Listas(1);
                    pressanykey();
                    clrscr();
                    break;

                case 'e': // Mostrar lista de predecesores del grafo
                    clrscr();
                    cout << "La lista de predecesores del grafo " << nombrefichero;
                    cout << " es:" << endl << endl;
                    G.Mostrar_Listas(-1);
                    pressanykey();
                    clrscr();
                    break;   

                case 'a': // Mostrar lista de adyacencia del grafo
                    clrscr();
                    cout << "La lista de adyacencia del grafo " << nombrefichero;
                    cout << " es:" << endl << endl;
                    G.Mostrar_Listas(0); // l = 0 para LS de G.D o para LA de G.N
                    pressanykey();
                    clrscr();
                    break;
                
                case 'm': // Recorrido en a(m)plitud
                    clrscr();
                    G.RecorridoAmplitud();
                    pressanykey();
                    clrscr();
                    break;
                
                case 'r': // Recorrido en p[r]ofundidad
                    clrscr();
                    G.RecorridoProfundidad();
                    pressanykey();
                    clrscr();
                    break;
                case 'y': // Matriz adyacencia
                    clrscr();
                    G.Mostrar_Matriz();
                    pressanykey();
                    clrscr();
                    break;
                case 'k': // Kruskal
                    clrscr();
                    G.Kruskal();
                    pressanykey();
                    clrscr();
                    break;
                case 'p': // PDM
                    clrscr();
                    G.PDM();
                    pressanykey();
                    clrscr();
                    break;
                                 


            }
    }
    while (opcion != 'q');
    }
    cout << "Fin del programa" << endl;
	return(0);
};
