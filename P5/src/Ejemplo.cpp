/*
 * Ejemplos para aprender a usar correctamente la clase Laberinto y sus estructuras
 */

#include "Laberinto.h"
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <poll.h>

using namespace std;

void ejemplo1();
void ejemplo2();
void ejemplo3(const char * path);
int getch(int ms);

int main(int argc, char * argv[]){
    char ejemplo;
    cout << "Escribe un número del 1 al 4 para ejecutar un ejemplo:\n\r" 
         << "\t 1 - Ejemplo 1\n\r"
         << "\t 2 - Ejemplo 2\n\r"
         << "\t 3 - Ejemplo 3 usando Rejilla.xml\n\r"
         << "\t 4 - Ejemplo 3 usando Laberinto.xml\n\r" 
         << endl; 
    while(!(ejemplo = getch(500))); //espera a que se pulse una tecla
    switch(ejemplo){
        case '1': ejemplo1();break;
        case '2': ejemplo2();break;
        case '3': ejemplo3("xml/Rejilla.xml");break;
        case '4': ejemplo3("xml/Laberinto.xml");break;
        default: cout << "número no reconocido\r" << endl; break;
    }
    
  return EXIT_SUCCESS;
}

/*
 * El primer ejemplo consiste en la creación de una lista enlazada de nodos camino
 * que sigue la siguiente secuencia: [0,0] - [4,3] - [5,1]
 */
void ejemplo1(){
  cout << "Ejemplo1:\r"  <<endl;
  nodo * nodo_A = new nodo();
  nodo_A -> x = 0;
  nodo_A -> y = 0;

  // cout << nodo_A->x << " - " << nodo_A->y << endl;

  // Creamos un nuevo camino que contiene el nodo [2,1]
  camino * aux = new camino();
  aux->nodo_actual = nodo_A;
  aux->anterior = NULL;
  aux->siguiente = NULL;

  nodo * nodo_B = new nodo();
  nodo_B ->x = 4;
  nodo_B ->y = 3;

  aux->siguiente = new camino();
  aux->siguiente->nodo_actual = nodo_B; // Asignamos al nuevo camino el nodo [4,3]
  aux->siguiente->siguiente = NULL;
  aux->siguiente->anterior = aux;

  nodo * nodo_C = new nodo();
  nodo_C -> x = 5;
  nodo_C -> y = 1;

  camino * camino_C = new camino();
  aux -> siguiente -> siguiente = camino_C;
  camino_C ->nodo_actual = nodo_C;
  camino_C ->anterior = aux->siguiente;
  camino_C ->siguiente = NULL;
  
  cout << "Camino creado: ";
  do{
      cout << "[" << aux->nodo_actual->x << "," << aux->nodo_actual->y <<"] ";
      aux = aux->siguiente; // Actualizamos el valor del nodo auxiliar    
  }while(aux!=NULL);
  cout << "\n\r" << endl;

}

/*
 * El segundo ejemplo repite lista enlazada de nodos camino [0,0] - [4,3] - [5,1]
 * usando "laberinto.xml" como Mapa
 */
void ejemplo2(){
  cout << "Ejemplo2: \r" << endl;
    
  Laberinto *maze;
  maze = new Laberinto("xml/Laberinto.xml");  
  maze->imprimirLaberinto();

  // Para usar maze->matriz fuera de la clase Laberinto hay que cambiar en
  // Laberinto.h su visibilidad de private a public.
  nodo nodo_matriz = maze->matriz[0][0];

  // Comprobamos que hemos copiado bien el nodo matriz[0][0] a nodo_matriz
  //cout << nodo_matriz.Este->x << " - " << nodo_matriz.Este->y << endl;

  camino * mi_camino = new camino();
  mi_camino->nodo_actual = &nodo_matriz;

  camino * mi_camino2 = new camino();
  mi_camino2->nodo_actual = &maze->matriz[4][3];
  mi_camino->siguiente = mi_camino2;

  camino * mi_camino3 = new camino();
  mi_camino3->nodo_actual = &maze->matriz[5][1];
  mi_camino->siguiente->siguiente = mi_camino3;

  // Imprimimos los nodos que contienen los caminos de la lista mi_camino junto
  // con el nodo que se encuentra enlazado al Este
  cout << "Camino creado: \r" <<endl;
  do{
      cout << "[" << mi_camino->nodo_actual->x << "," << mi_camino->nodo_actual->y <<"] ";
      if(mi_camino->nodo_actual->Este==NULL){
        cout << ": no existe nodo al Este\r" <<endl;
      }   else{
        cout << ": nodo al Este ["<< mi_camino->nodo_actual->Este->x << "," <<mi_camino->nodo_actual->Este->y << "]\r" << endl;
      }
      mi_camino = mi_camino->siguiente; // Actualizamos el valor del nodo auxiliar    
  }while(mi_camino!=NULL);
  cout << "\n\r" << endl;

 }

/*
 * El tercer ejemplo carga un laberinto y permite recorrerlo usando el teclado: 
 * - Flechas del teclado: Cambia la orientación del robot
 * - Barra espaciadora: Avanza una posición si puede
 * - Backspace, Enter y Tab: Imprime los nodos del camino por los que ha pasado el robot
 * - q : Termina de recorrer el laberinto
 */
void ejemplo3(const char *path){

	bool fin = false;
        bool mapa_modificado = false;
	char tecla, orientacion;
        int x,y;
	
        Laberinto *maze;
	maze = new Laberinto(path);
        maze->imprimirLaberinto();

        do{
            
            if(tecla = getch(300)){
                switch(tecla){
                    
                    case 8: // Backspace
                    case 9: // Tab
                    case 10:// Enter
                        maze->imprimirCaminoRobot();
                        break;
                    case 27: tecla = getch(10);
                        if(tecla == 91){
                            tecla = getch(10); 
                            
                            maze->getPosRobot( &x,&y,&orientacion);
                            switch(tecla){
                                case 65: // Flecha arriba
                                    if(orientacion==NORTE){
                                        cout << "El robot ya se encuentra orientado hacia el Norte\r" <<endl;
                                    }else{
                                        cout << "Robot orientado al Norte\r" << endl;
                                        maze->orientarRobotNorte();
                                        mapa_modificado = true;
                                    }
                                    break;
                                case 66: // Flecha abajo
                                    if(orientacion==SUR){
                                        cout << "El robot ya se encuentra orientado hacia el Sur\r" <<endl;
                                    }else{
                                       cout << "Robot orientado al Sur\r" << endl;
                                        maze->orientarRobotSur();
                                        mapa_modificado = true; 
                                    }
                                    break;
                                case 67: // Flecha derecha
                                    if(orientacion==ESTE){
                                        cout << "El robot ya se encuentra orientado hacia el Este\r" <<endl;
                                    }else{
                                        cout << "Robot orientado al Este\r" << endl;
                                        maze->orientarRobotEste();
                                        mapa_modificado = true;
                                    }
                                    break;
                                case 68: // Flecha izquierda
                                    if(orientacion==OESTE){
                                        cout << "El robot ya se encuentra orientado hacia el Oeste\r" <<endl;
                                    }else{
                                        cout << "Robot orientado al Oeste\r" << endl;
                                        maze->orientarRobotOeste();
                                        mapa_modificado = true;
                                    }
                                    break;
                                default: 
                                    break;
                            }
                        }
                        break;

                    case 32: // Barra espaciadora

                        maze->getPosRobot( &x,&y,&orientacion);
                        switch(orientacion){
                            case NORTE:
                                    if (maze->esNorteLibre()){
                                        maze->avanzaNorte();
                                        mapa_modificado = true;
                                    }else{
                                        cout << "No existe un camino al Norte \r"<< endl;
                                    }
                                    break;
                            case SUR:
                                    if(maze->esSurLibre()){
                                        maze->avanzaSur();
                                        mapa_modificado = true;
                                    }else{
                                        cout << "No existe un camino al Sur\r"<< endl;
                                    }
                                    break;
                            case ESTE:
                                    if(maze->esEsteLibre()){
                                        maze->avanzaEste();
                                        mapa_modificado = true;
                                    }else{
                                        cout << "No existe un camino al Este \r"<< endl;
                                    }
                                    break;
                            case OESTE:
                                    if(maze->esOesteLibre()){
                                        maze->avanzaOeste();
                                        mapa_modificado = true;
                                    }else{
                                        cout << "No existe un camino al Oeste \r"<< endl;
                                    }
                                    break;
                            default:
                                    break;
                        }
                        break;
                    case 'q': 
                        fin=true;
                        break;
                    default: 
                        break;
                }
                if (mapa_modificado) {
                    maze->imprimirLaberinto();
                    mapa_modificado=false;
                }    
            }
        }while(!fin);
        
	maze->imprimirCaminoRobot();
        
}

/**
 * Espera la lectura de un caracter por teclado durante ms milisegundos
 * @param ms tiempo de espera en milisegundos
 * @return 0 si no lee nada, el caracter leido en otro caso 
 */
int getch(int ms)
{
    int ret;
    struct termios oldt, newt;
    struct pollfd pfds[1];

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    pfds[0].fd = STDIN_FILENO;
    pfds[0].events = POLLIN;
    poll(pfds, 1, ms);
    if (pfds[0].revents & POLLIN) {
        char ch;
        read(STDIN_FILENO, &ch, 1);
        ret = ch;
    } else {
        ret = 0;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ret;
}