//laberinto.h

#pragma once

#include "tinyxml/tinyxml.h"
#include <iostream>
#include <vector>

#define NORTE 	1
#define SUR		2
#define ESTE	3
#define OESTE	4

using namespace std;

// Los laberintos se componen de nodos
struct nodo{
	int x;
	int y;
	nodo *Norte;
	nodo *Este;
	nodo *Oeste;
	nodo *Sur;
};

// El camino recorrido por el robot es una lista enlazada
struct camino{
	nodo 	*nodo_actual;
	camino 	*siguiente;
	camino 	*anterior;
};
		
class Laberinto {

    private:
    	
		string nombre;
		int dim_x;
    	int dim_y;
    	
	    //struct nodo **matriz;
	    
	    // La posici�n del robot se representa usando un nodo
	    struct robot{
	    	nodo *nodo_actual;
	    	char orientacion;
	    };
	    struct robot iCreate;

	    struct camino *path;
	    struct camino *first; // primer elemento de la lista

		// M�todos de uso interno para cargar el XML y rellenar la matriz de nodos
		void cargarLaberinto(const char* pFilename);
		void procesarNodos( TiXmlHandle * hParent);
		void procesarCaminos( TiXmlHandle *hNodo, int pos_x, int pos_y);

		// Situa el robot en un nodo concreto del laberinto
		void situarRobot(int pos_x, int pos_y, char orientacion);
		
		// Actualiza el recorrido del robot en el laberinto
		void modificarCamino(robot *aux);
		
		bool visitado(nodo *proximo, camino *first_visited);
		
		// A�ade un nodo nuevo a un camino
		void modificarCamino(camino** cam, nodo **aux);

    public:
    	struct nodo **matriz; // Cambiado para que el ejemplo funcione

    	Laberinto(void);
    	Laberinto(const char* pFilename);
    	Laberinto(const char* pFilename, int x, int y, char orientacion);
		~Laberinto(void);

		// Funci�n a completar en la pr�ctica
		camino*  encontrarCamino(int x_orig, int y_orig, int x_dest, int y_dest);

		// Devuelve la posicion del robot y su orientacion
		void getPosRobot(int *pos_x, int *pos_y, char * orientacion);
		
		// M�todos para consultar si el robot puede avanzar en una direcci�n
		bool esSurLibre();
		bool esNorteLibre();
		bool esEsteLibre();
		bool esOesteLibre();

		// M�todos para cambiar la orientaci�n del robot en el laberinto
		void orientarRobotNorte();
		void orientarRobotSur();
		void orientarRobotEste();
		void orientarRobotOeste();

		// M�todos para mover el robot en el laberinto
		int avanzaNorte();
		int avanzaSur();
		int avanzaEste();
		int avanzaOeste();

		// M�todos para visualizar la informaci�n del laberinto
		void imprimirLaberinto();
		void imprimirCamino(camino *first_element);
		void imprimirCaminoRobot();
    
};

